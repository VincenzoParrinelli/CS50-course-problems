-- Query all interviews
SELECT * FROM interviews;

-- Query for duck mentions in interview transcript
SELECT * FROM interviews
WHERE transcript
LIKE '%duck%';

-- Query for duck mentions in crime_scene_reports
-- Theft hour: 10:15am
-- location: the Humphrey Street bakery.
-- Interviews witnesses: three witnesses who were present at the time each of their interview transcripts mentions the bakery.
SELECT * FROM crime_scene_reports
WHERE description
LIKE '%duck%';

-- Query for bakery mentions in interviews transcript
SELECT * FROM interviews
WHERE transcript
LIKE '%bakery%';

-- Query for atm transactions on the same day of theft, withdrawals only and Leggett Street
SELECT * FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';

-- Query for phone calls less than a minute on the same day of theft
SELECT * FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

-- Query for parking lot exits early in the morning
SELECT * FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND activity = 'exit'
AND hour < 14;


-- Query for flights on the same day
SELECT * FROM flights
WHERE year = 2021
AND month = 7
AND day = 28
AND hour < 14;

-- Query for airports data based on flights
-- !!!: Fiftyfille origin airport id = 8
-- !!!: Destination city = Dallas
SELECT * FROM airports
JOIN flights ON airports.id = flights.origin_airport_id;


-- Query for passengers with airport id = 8
SELECT * FROM passengers
WHERE flight_id = 8;

-- Query for passengers data in flight 8
SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight = 8
);

