import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    # Ensure responses aren't cached
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Show portfolio of stocks

    user_id = session.get("user_id")

    transactions = db.execute(
        "SELECT * FROM history JOIN users ON history.user_id = users.id WHERE users.id = ?", user_id)

    if not transactions:
        return render_template("index.html")

    total = transactions[0]["cash"]

    for transaction in transactions:
        transaction["total"] = transaction["price"] * transaction["shares"]
        total += transaction["total"]

    return render_template("index.html", transactions=transactions, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Buy shares of stock

    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol_data = lookup(symbol)
        shares = request.form.get("shares")
        user_id = session.get("user_id")

        if not symbol:
            return apology("please insert a symbol")
        elif not symbol_data:
            return apology("invalid symbol")

        if not shares.isnumeric():
            return apology("shares must be a positive integer")

        if not user_id:
            return apology("Forbidden", 403)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[
            0]["cash"]

        total = symbol_data["price"] * int(shares)

        if user_cash < total:
            return apology("insufficient funds")

        db.execute("INSERT INTO history (user_id, symbol, name, shares, price) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol_data["symbol"], symbol_data["name"], shares, symbol_data["price"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_cash - total, user_id)

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # Show history of transactions

    user_id = session.get("user_id")

    transactions = db.execute(
        "SELECT * FROM history WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    # Log user in

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    # Log user out

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # Get stock quote.

    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol_data = lookup(symbol)

        if not symbol:
            return apology("please insert a symbol")
        elif not symbol_data:
            return apology("invalid symbol")

        return render_template("quoted.html", data=symbol_data)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # Register user
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        password2 = request.form.get("confirmation")

        # If username or password is blank or username already exist return apology
        if not username or not password or password != password2:
            return apology("invalid username and/or password", 400)

        hashed_password = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                       username, hashed_password)
        except ValueError:
            return apology("invalid username and/or password", 400)

        id = db.execute("SELECT id FROM users WHERE username = ?", username)

        session["user_id"] = id[0]["id"]

        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # Sell shares of stock

    if request.method == "POST":
        user_id = session.get("user_id")
        symbol = request.form.get("symbol")
        symbol_data = lookup(symbol)
        shares = request.form.get("shares")
        transactions = db.execute(
            "SELECT * FROM history JOIN users ON history.user_id = users.id WHERE users.id = ?", user_id)
        total_shares_per_symbol = {}
        is_symbol_present = False

        # if shares is negative
        if not shares.isnumeric():
            return apology("shares must be a positive number")

        # loop over transactions and check if symbol exists and set relative flag tot true
        for transaction in transactions:
            if symbol in transaction["symbol"]:
                is_symbol_present = True

        # render apology if symbol doesn't esist
        if not is_symbol_present:
            return apology("symbol doesn't exist")

        # loop over transactions
        for transaction in transactions:

            # if the symbol of the current transaction in iteraton is not in total_shares_per_symbol hash map
            # create new key and set it to 0
            if transaction["symbol"] not in total_shares_per_symbol:
                total_shares_per_symbol[transaction["symbol"]] = 0

            # else add to that symbol his total price
            total_shares_per_symbol[transaction["symbol"]
                                    ] += transaction["price"] * int(transaction["shares"])

        # if the total shares of selected symbol are not higher than shares * symbol.price then the user has not enough stocks left, render apology
        if not total_shares_per_symbol[symbol] >= float(shares) * symbol_data["price"]:
            return apology("not enough stocks")

        db.execute("INSERT INTO history (user_id, symbol, name, shares, price) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol_data["symbol"], symbol_data["name"], -abs(int(shares)), symbol_data["price"])

        return redirect("/")

    user_id = session.get("user_id")

    bought_stocks_names = []

    transactions = db.execute(
        "SELECT * FROM history JOIN users ON history.user_id = users.id WHERE users.id = ?", user_id)

    for transaction in transactions:
        symbol = transaction["symbol"]

        if symbol not in bought_stocks_names:
            bought_stocks_names.append(symbol)

    return render_template("sell.html", bought_stocks_names=bought_stocks_names)


@app.route("/change-password", methods=["GET", "POST"])
@login_required
def change_password():
    # Change password

    if request.method == "POST":
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        new_password2 = request.form.get("new_password2")
        user_id = session.get("user_id")

        old_hash = db.execute("SELECT hash FROM users WHERE id = ?", user_id)[
            0]["hash"]

        if new_password != new_password2:
            return apology("passwords do not match")

        if check_password_hash(old_hash, new_password):
            return apology("new password cannot match the current one")

        if not check_password_hash(old_hash, old_password):
            return apology("incorrect password")

        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   generate_password_hash(new_password), user_id)

        return redirect("/login")

    return render_template("change_password.html")
