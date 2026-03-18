import threading
import time
from enum import Enum
from typing import List

# --- Enums ---
class SeatStatus(Enum):
    AVAILABLE = 1
    LOCKED = 2  # Temporary hold during payment
    BOOKED = 3

class BusType(Enum):
    AC_SLEEPER = 1
    NON_AC_SEATER = 2

# --- Core Entities ---
class Seat:
    def __init__(self, seat_no: str, is_sleeper: bool):
        self.seat_no = seat_no
        self.is_sleeper = is_sleeper

class Bus:
    def __init__(self, bus_id: str, operator_name: str, bus_type: BusType, seats: List[Seat]):
        self.bus_id = bus_id
        self.operator_name = operator_name
        self.bus_type = bus_type
        self.seats = seats

class TripSeat:
    """Manages the status of a physical seat for a specific trip instance."""
    def __init__(self, seat: Seat):
        self.seat = seat
        self.status = SeatStatus.AVAILABLE
        self.lock = threading.Lock()
        self.lock_expiry = 0

    def hold_seat(self, duration=300): # Default 5 mins hold
        with self.lock:
            if self.status == SeatStatus.AVAILABLE:
                self.status = SeatStatus.LOCKED
                self.lock_expiry = time.time() + duration
                return True
            # Check if an existing lock has expired
            if self.status == SeatStatus.LOCKED and time.time() > self.lock_expiry:
                self.lock_expiry = time.time() + duration
                return True
            return False

    def confirm_booking(self):
        with self.lock:
            if self.status == SeatStatus.LOCKED:
                self.status = SeatStatus.BOOKED
                return True
            return False

class Trip:
    def __init__(self, trip_id: str, bus: Bus, source: str, dest: str, departure: float):
        self.trip_id = trip_id
        self.bus = bus
        self.source = source
        self.dest = dest
        self.departure = departure
        # Initialize trip-specific seat statuses
        self.trip_seats = {s.seat_no: TripSeat(s) for s in bus.seats}

# --- Service Layer ---
class BookingCoordinator:
    def __init__(self):
        self.bookings = {}
        self.global_lock = threading.Lock()

    def process_booking(self, user_id: str, trip: Trip, seat_nos: List[str]):
        # 1. Attempt to hold all requested seats
        held_seats = []
        for s_no in seat_nos:
            t_seat = trip.trip_seats.get(s_no)
            if t_seat and t_seat.hold_seat():
                held_seats.append(t_seat)
            else:
                print(f"Failed to hold seat {s_no}")
                return None

        # 2. Simulate Payment Process
        print(f"Seats {seat_nos} locked for User {user_id}. Awaiting payment...")
        time.sleep(1) # Simulated network latency
        
        # 3. Confirm all held seats
        for h_seat in held_seats:
            h_seat.confirm_booking()
        
        booking_id = f"RES-{int(time.time())}-{user_id}"
        self.bookings[booking_id] = {"user": user_id, "seats": seat_nos}
        print(f"Booking {booking_id} Confirmed!")
        return booking_id

# --- Main Execution ---
if __name__ == "__main__":
    # Setup Bus and Layout
    seats = [Seat("1A", True), Seat("1B", True), Seat("2A", False), Seat("2B", False)]
    my_bus = Bus("KA-01-1234", "Intercity Travels", BusType.AC_SLEEPER, seats)
    
    # Create a specific Trip
    tonight_trip = Trip("T101", my_bus, "Bangalore", "Goa", time.time() + 36000)

    coordinator = BookingCoordinator()

    # Simulation: Concurrent booking attempt for the same seat
    t1 = threading.Thread(target=coordinator.process_booking, args=("User_Alice", tonight_trip, ["1A", "1B"]))
    t2 = threading.Thread(target=coordinator.process_booking, args=("User_Bob", tonight_trip, ["1A"]))

    t1.start()
    t2.start()
    t1.join()
    t2.join()