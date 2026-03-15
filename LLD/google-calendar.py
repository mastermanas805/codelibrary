"""
Google Calendar

- Users can create events and send invites to multiple attendees.
- Events are pushed to attendees in a `PENDING` state.
- Users can `ACCEPT` or `DECLINE` the event.
- A notification is scheduled exactly 10 minutes before the event starts. If a user declines, their notification is canceled.
- The system uses a **Priority Queue (Min-Heap)** to efficiently fetch a user's next upcoming event.


Entities - 
1. RSVP (ENUM)
2. Event
    - add_participant
    - update(user, rsvp)
    - send_notification
3. User
   - name
   - send_notification

4. Calendar
   
   - priority_queue for upcoming event
   - []Events
   - []Users

   - add_event
   - tick
   - send_notification (thread)
"""
import threading
import time
from enum import Enum
from queue import PriorityQueue, Empty

class RSVP(Enum):
    PENDING = 0
    ACCEPT = 1
    DECLINE = 2

class User:
    def __init__(self, user_id, name):
        self.id = user_id
        self.name = name

    def send_notification(self, message: str):
        print(f"[Notification to {self.name}]: {message}")

class Event:
    def __init__(self, event_id: int, host: User, name: str, start_at_timestamp: int):
        self.id = event_id
        self.name = name
        self.start_at = start_at_timestamp
        self.attendees = {host.id: host}
        self.rsvp = {host.id: RSVP.ACCEPT}
    
    def add_participants(self, users: list[User]):
        for user in users:
            self.rsvp[user.id] = RSVP.PENDING
            self.attendees[user.id] = user

    def update_rsvp(self, user_id: int, rsvp_status: RSVP):
        if user_id in self.rsvp:
            self.rsvp[user_id] = rsvp_status
            print(f"User {user_id} updated RSVP to {rsvp_status.name}")
        else:
            print("Invalid User ID")
    
    def send_notification(self, message: str):
        for user_id, user in self.attendees.items():
            # Crucial: Only notify if they haven't declined
            if self.rsvp[user_id] != RSVP.DECLINE:
                user.send_notification(f"Event '{self.name}': {message}")

class Calendar:
    def __init__(self):
        self.notif_queue = PriorityQueue()
        self.stop_event = threading.Event()
        self._thread = threading.Thread(target=self.__run_scheduler, daemon=True)
        self._thread.start()
    
    def add_event(self, event: Event):
        # Schedule notification for (StartTime - 10 seconds) for this demo
        # In a real app, this would be 10 * 60 seconds
        notification_time = event.start_at - 10
        self.notif_queue.put((notification_time, event))
        print(f"Event '{event.name}' scheduled. Notifying at timestamp {notification_time}")

    def __run_scheduler(self):
        while not self.stop_event.is_set():
            try:
                # Peek at the priority queue without removing
                # PriorityQueue doesn't have a peek, so we get and put back if not ready
                notif_time, event = self.notif_queue.get(timeout=1)
                
                if time.time() >= notif_time:
                    event.send_notification("Reminder: Starts in 10 mins!")
                else:
                    # Not time yet, put it back and wait
                    self.notif_queue.put((notif_time, event))
                    time.sleep(1)
            except Empty:
                time.sleep(1)

# --- MAIN EXECUTION BLOCK ---
if __name__ == "__main__":
    print("--- Google Calendar LLD Simulation ---")
    cal = Calendar()

    # 1. Create Users
    alice = User(1, "Alice")
    bob = User(2, "Bob")
    charlie = User(3, "Charlie")

    # 2. Create an Event starting 15 seconds from now
    start_time = int(time.time()) + 15
    meeting = Event(101, alice, "LLD Review", start_time)
    meeting.add_participants([bob, charlie])
    
    # 3. Add to Calendar
    cal.add_event(meeting)

    # 4. Simulate Bob declining (He should NOT get the 10-min notification)
    print("\nSimulating Bob declining the invite...")
    meeting.update_rsvp(bob.id, RSVP.DECLINE)

    # 5. Wait for the scheduler to trigger
    print("\nWaiting for the 10-second mark (notification trigger)...")
    time.sleep(12) 
    
    print("\nSimulation Finished.")
    cal.stop_event.set()