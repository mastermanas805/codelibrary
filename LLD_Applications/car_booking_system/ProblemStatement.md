Car Booking System (Single City)
Design and implement a backend system for booking cars within a single city.
The city operates multiple branches, each managing its own fleet of cars.
Domain Overview
Branches
Each branch is uniquely identified by its name
A branch owns a fleet of cars and maintains its own pricing configuration
Cars
• Every car belongs to exactly one branch
• Supported car categories:
SEDAN
SUV
HATCHBACK
• Each car has a unique identifier within its branch
Pricing Rules
Pricing is configured per branch and per car category
Price is defined as price per day
All cars of the same category within a branch share the same price
Pricing may change over time
Booking Rules
• A user requests a car by specifying:
Car category
Time window (startDay, endDay)
- PreBooking
• The system must allocate one available car that satisfies the request
• Among all valid options:
Select the car with the lowest price
If multiple cars have the same price, apply a deterministic tie-breaking rule
• A booking, once confirmed, blocks that car for the given time window
• Overlapping bookings for the same car are not allowed
Expectations
The system should support onboarding new branches, cars, and pricing configurations
Users should be able to request bookings without needing to know which branch or car they are getting
The system must ensure correctness even when multiple booking requests happen close together in time



Entities: 
1. Branch
   - id
   - Name
   - []Cars
   - PricingStrategy
2. Car
   - id
   - type
   - reg_no
3. Booking
   - Car
   - StartDay
   - EndDay
   - Price
   - Status
   - Reason
   - User
4. CarType (ENUM)
5. BookingStatus (ENUM)
5. PricingStrategy (Interface)
6. Allocation Strategy (Interface)
   - allocate
     - Get all cars with given Type that do not satisfy (startDay>=startDay || endday<=EndDay)
     - sort cars by price, id
     - return the min one
7. BookingService
 - []Branches
 - []Booking
 - []User
 - func createBooking(userID, startDay, endDay, carType)
 - while:
   - Allocation_Strategy.allocate() -> (Car, Branch)
   - lock over car (lock:car:carID:day)
   - Atomic
     - check for booking in db
       - filter the bookings startDay>=startDay || endday<=EndDay
     - create a booking object in DB
     - Status = Created
   - GetPayment() -> Error
   - Update Status of Booking
   - release lock for car
 - func cancelBooking(userID, bookingID)
   - call to db to update status
 - func addBranch()
 - func addCar()
 - func createUser()
 - func createBooking()
 - Allocation Strategy

8. User
   - id
   - name