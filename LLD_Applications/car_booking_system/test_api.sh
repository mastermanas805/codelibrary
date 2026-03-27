#!/bin/bash
set -e

API_URL="http://localhost:9080"
echo "Waiting for API to start..."
sleep 2

SESSION_ID=$RANDOM
BRANCH_NAME="Downtown-$SESSION_ID"
CAR_TYPE="SUV-$SESSION_ID"

echo "1. Adding a new branch '$BRANCH_NAME'"
BRANCH_ID=$(curl -s -X POST $API_URL/branches -H "Content-Type: application/json" -d "{\"name\": \"$BRANCH_NAME\"}" | jq -r '.id')
echo "Branch ID: $BRANCH_ID"

echo "2. Adding cars to '$BRANCH_NAME' branch"
CAR1_ID=$(curl -s -X POST $API_URL/branches/$BRANCH_ID/cars -H "Content-Type: application/json" -d "{\"type\": \"$CAR_TYPE\", \"reg_no\": \"REG-1-$SESSION_ID\"}" | jq -r '.id')
CAR2_ID=$(curl -s -X POST $API_URL/branches/$BRANCH_ID/cars -H "Content-Type: application/json" -d "{\"type\": \"$CAR_TYPE\", \"reg_no\": \"REG-2-$SESSION_ID\"}" | jq -r '.id')
echo "Added Cars: $CAR1_ID, $CAR2_ID"

echo "3. Setting pricing for $CAR_TYPE at '$BRANCH_NAME'"
curl -s -X POST $API_URL/branches/$BRANCH_ID/pricing -H "Content-Type: application/json" -d "{\"car_type\": \"$CAR_TYPE\", \"price_per_day\": 100.0}"

echo "4. Creating a user booking for $CAR_TYPE from Day 1 to Day 5"
BOOKING1=$(curl -s -X POST $API_URL/bookings -H "Content-Type: application/json" -d "{\"user_id\": \"user-1-$SESSION_ID\", \"car_type\": \"$CAR_TYPE\", \"start_day\": 1, \"end_day\": 5}")
echo "Booking 1 Response: $BOOKING1"

echo "5. Creating a concurrent booking for $CAR_TYPE from Day 2 to Day 4"
BOOKING2=$(curl -s -X POST $API_URL/bookings -H "Content-Type: application/json" -d "{\"user_id\": \"user-2-$SESSION_ID\", \"car_type\": \"$CAR_TYPE\", \"start_day\": 2, \"end_day\": 4}")
echo "Booking 2 Response: $BOOKING2"

echo "6. Creating a third booking for $CAR_TYPE from Day 1 to Day 5, should fail if no more cars available"
BOOKING3=$(curl -s -X POST $API_URL/bookings -H "Content-Type: application/json" -d "{\"user_id\": \"user-3-$SESSION_ID\", \"car_type\": \"$CAR_TYPE\", \"start_day\": 1, \"end_day\": 5}")
echo "Booking 3 Response: $BOOKING3"

echo "7. Cancelling Booking 1"
B1_ID=$(echo $BOOKING1 | jq -r '.id')
if [ "$B1_ID" != "null" ]; then
  curl -s -X PUT $API_URL/bookings/$B1_ID/cancel -H "Content-Type: application/json" -d "{\"user_id\": \"user-1-$SESSION_ID\"}"
  echo "Booking 1 Cancelled."
fi

echo "8. Trying Booking 3 again (now it should succeed since Booking 1 is cancelled)"
BOOKING4=$(curl -s -X POST $API_URL/bookings -H "Content-Type: application/json" -d "{\"user_id\": \"user-3-$SESSION_ID\", \"car_type\": \"$CAR_TYPE\", \"start_day\": 1, \"end_day\": 5}")
echo "Booking 4 Response: $BOOKING4"
