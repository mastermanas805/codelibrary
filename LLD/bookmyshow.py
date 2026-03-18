"""
Book My Show

Requirements

    The system should allow users to view the list of movies playing in different theaters.
    Users should be able to select a movie, theater, and show timing to book tickets.
    The system should display the seating arrangement of the selected show and allow users to choose seats.
    Users should be able to make payments and confirm their booking.
    The system should handle concurrent bookings and ensure seat availability is updated in real-time.
    The system should support different types of seats (e.g., normal, premium) and pricing.
    The system should allow theater administrators to add, update, and remove movies, shows, and seating arrangements.
    The system should be scalable to handle a large number of concurrent users and bookings.

Entities
    1. Movie
    2. Theater
    3. Ticket
    5. Show
    6. Booking
    7. Seat
    8. Seating Arrangement Strategy (Interface)
    9. MovieBookingService

"""

import threading
import time
from enum import Enum
from typing import List, Optional

# 1. Enums for Types and Status
class SeatType(Enum):
    NORMAL = 1
    PREMIUM = 2

class SeatStatus(Enum):
    AVAILABLE = 1
    LOCKED = 2
    BOOKED = 3

# 2. Physical Entities
class Seat:
    def __init__(self, seat_id: str, seat_type: SeatType, price: float):
        self.seat_id = seat_id
        self.seat_type = seat_type
        self.price = price

class Screen:
    def __init__(self, screen_id: str, seats: List[Seat]):
        self.screen_id = screen_id
        self.seats = seats

class Theater:
    def __init__(self, theater_id: str, name: str, city: str):
        self.theater_id = theater_id
        self.name = name
        self.city = city
        self.screens: List[Screen] = []

# 3. Show and Seat Availability Management
class ShowSeat:
    """Tracks the status of a specific seat for a specific show."""
    def __init__(self, seat: Seat):
        self.seat = seat
        self.status = SeatStatus.AVAILABLE
        self.lock = threading.Lock()

    def reserve(self) -> bool:
        with self.lock:
            if self.status == SeatStatus.AVAILABLE:
                self.status = SeatStatus.BOOKED
                return True
            return False

class Show:
    def __init__(self, show_id: str, movie: 'Movie', screen: Screen, start_time: int):
        self.show_id = show_id
        self.movie = movie
        self.screen = screen
        self.start_time = start_time
        # Map physical seat ID to its status for THIS show
        self.show_seats = {s.seat_id: ShowSeat(s) for s in screen.seats}

class Movie:
    def __init__(self, movie_id: str, title: str, duration: int):
        self.movie_id = movie_id
        self.title = title
        self.duration = duration

# 4. Booking Logic
class Booking:
    def __init__(self, booking_id: str, show: Show, seats: List[ShowSeat], user_id: str):
        self.booking_id = booking_id
        self.show = show
        self.seats = seats
        self.user_id = user_id
        self.total_amount = sum(s.seat.price for s in seats)
        self.is_confirmed = False

class BookingService:
    _instance = None
    _lock = threading.Lock()

    def __new__(cls):
        """Singleton Service"""
        with cls._lock:
            if not cls._instance:
                cls._instance = super(BookingService, cls).__new__(cls)
        return cls._instance

    def book_tickets(self, user_id: str, show: Show, seat_ids: List[str]) -> Optional[Booking]:
        selected_show_seats = []
        
        # Attempt to reserve all seats
        for s_id in seat_ids:
            show_seat = show.show_seats.get(s_id)
            if not show_seat or not show_seat.reserve():
                print(f"Seat {s_id} is already taken or invalid.")
                return None
            selected_show_seats.append(show_seat)

        # Create Booking
        booking_id = f"BKG-{int(time.time())}"
        new_booking = Booking(booking_id, show, selected_show_seats, user_id)
        new_booking.is_confirmed = True
        print(f"Successfully booked {len(seat_ids)} seats for {show.movie.title}")
        return new_booking

# --- Simulation / Main ---
if __name__ == "__main__":
    # Setup: 1 Screen with 2 Seats
    s1 = Seat("A1", SeatType.NORMAL, 150)
    s2 = Seat("A2", SeatType.PREMIUM, 300)
    my_screen = Screen("SCR1", [s1, s2])
    
    # Setup: Movie and Show
    interstellar = Movie("M1", "Interstellar", 180)
    evening_show = Show("SH1", interstellar, my_screen, 1710547200)

    service = BookingService()

    # Threaded Simulation: Two users try to book the same seat (A1)
    def user_action(user_name, seat_list):
        service.book_tickets(user_name, evening_show, seat_list)

    t1 = threading.Thread(target=user_action, args=("Alice", ["A1"]))
    t2 = threading.Thread(target=user_action, args=("Bob", ["A1", "A2"]))

    t1.start()
    t2.start()
    t1.join()
    t2.join()