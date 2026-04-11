"""
RequestType
 - UP
 - DOWN
 - DESTINATION


Request
 - requestType: RequestType
 - floor: int


Direction
 - UP
 - DOWN
 - IDLE


Elevator
 - id: int
 - direction: Direction
 - currentFloor: int
 - upRequests: MinHeap<int>
 - downRequests: MaxHeap<int>
 - stops: Set<int>

 + addRequest(floor: int, type: RequestType) -> bool
 + step() -> None
 + _nextStop() -> Optional<int>
 + _processStop(floor: int) -> None


ElevatorAssignStrategy (interface)
 + selectElevator(elevators: List<Elevator>, floor: int, direction: Direction) -> Elevator


NearestElevatorStrategy (implements ElevatorAssignStrategy)
 + selectElevator(...) -> Elevator


ElevatorController
 - elevators: List<Elevator>
 - strategy: ElevatorAssignStrategy

 + requestController(floor: int, direction: Direction) -> bool
 + step() -> None
"""

from enum import Enum
from typing import List, Optional
import heapq
from abc import ABC, abstractmethod


# ---------------- Enums ---------------- #

class Direction(Enum):
    UP = 1
    DOWN = -1
    IDLE = 0


class RequestType(Enum):
    UP = 1          # hall call
    DOWN = 2        # hall call
    DESTINATION = 3 # inside elevator


# ---------------- Request ---------------- #

class Request:
    def __init__(self, request_type: RequestType, floor: int):
        self.request_type: RequestType = request_type
        self.floor: int = floor


# ---------------- Elevator ---------------- #

class Elevator:
    def __init__(self, id: int):
        self.id: int = id
        self.current_floor: int = 0
        self.direction: Direction = Direction.IDLE

        # unified scheduling queues
        self.up_requests: List[int] = []      # min heap
        self.down_requests: List[int] = []    # max heap (store negative)

        self.stops: set[int] = set()

    # ---- Core APIs ---- #

    def addRequest(self, floor: int, req_type: RequestType) -> bool:
        if floor < 0 or floor > 9:
            return False

        if floor in self.stops:
            return False

        # DESTINATION always belongs to this elevator
        self.stops.add(floor)

        if floor > self.current_floor:
            heapq.heappush(self.up_requests, floor)
        elif floor < self.current_floor:
            heapq.heappush(self.down_requests, -floor)
        else:
            print(f"Elevator {self.id}: Already at floor {floor}")
            return True

        # if idle → decide direction
        if self.direction == Direction.IDLE:
            self.direction = Direction.UP if floor > self.current_floor else Direction.DOWN

        return True

    def addDestination(self, floor: int) -> bool:
        return self.addRequest(floor, RequestType.DESTINATION)

    # ---- Internal Helpers ---- #

    def _nextStop(self) -> Optional[int]:
        if self.direction == Direction.UP:
            if self.up_requests:
                return self.up_requests[0]
            elif self.down_requests:
                return -self.down_requests[0]

        elif self.direction == Direction.DOWN:
            if self.down_requests:
                return -self.down_requests[0]
            elif self.up_requests:
                return self.up_requests[0]

        return None

    def _processStop(self, floor: int) -> None:
        print(f"Elevator {self.id} stopping at floor {floor}")

        self.stops.discard(floor)

        if self.direction == Direction.UP:
            if self.up_requests and self.up_requests[0] == floor:
                heapq.heappop(self.up_requests)
        else:
            if self.down_requests and -self.down_requests[0] == floor:
                heapq.heappop(self.down_requests)

        # direction switching
        if self.direction == Direction.UP and not self.up_requests:
            self.direction = Direction.DOWN if self.down_requests else Direction.IDLE

        elif self.direction == Direction.DOWN and not self.down_requests:
            self.direction = Direction.UP if self.up_requests else Direction.IDLE

    # ---- Simulation Step ---- #

    def step(self) -> None:
        if not self.up_requests and not self.down_requests:
            self.direction = Direction.IDLE
            return

        next_stop = self._nextStop()
        if next_stop is None:
            self.direction = Direction.IDLE
            return

        if self.current_floor < next_stop:
            self.current_floor += 1
            self.direction = Direction.UP
        elif self.current_floor > next_stop:
            self.current_floor -= 1
            self.direction = Direction.DOWN

        if self.current_floor == next_stop:
            self._processStop(next_stop)


# ---------------- Strategy ---------------- #

class ElevatorAssignStrategy(ABC):
    @abstractmethod
    def selectElevator(
        self,
        elevators: List[Elevator],
        floor: int,
        direction: Direction
    ) -> Elevator:
        pass


class NearestElevatorStrategy(ElevatorAssignStrategy):
    def selectElevator(
        self,
        elevators: List[Elevator],
        floor: int,
        direction: Direction
    ) -> Elevator:
        best: Optional[Elevator] = None
        min_distance = float('inf')

        for elevator in elevators:
            distance = abs(elevator.current_floor - floor)

            # prefer same direction or idle
            if elevator.direction in [direction, Direction.IDLE]:
                if distance < min_distance:
                    best = elevator
                    min_distance = distance

        return best if best else elevators[0]


# ---------------- Controller ---------------- #

class ElevatorController:
    def __init__(self, num_elevators: int):
        self.elevators: List[Elevator] = [Elevator(i) for i in range(num_elevators)]
        self.strategy: ElevatorAssignStrategy = NearestElevatorStrategy()

    # Hall request (outside elevator)
    def requestController(self, floor: int, direction: Direction) -> bool:
        elevator = self.strategy.selectElevator(self.elevators, floor, direction)

        req_type = RequestType.UP if direction == Direction.UP else RequestType.DOWN
        return elevator.addRequest(floor, req_type)

    # Step simulation
    def step(self) -> None:
        for elevator in self.elevators:
            elevator.step()


# ---------------- Main ---------------- #

def main() -> None:
    controller = ElevatorController(2)

    # -------- Hall Requests -------- #
    controller.requestController(3, Direction.UP)
    controller.requestController(6, Direction.DOWN)

    # simulate time
    for t in range(5):
        print(f"\n--- Step {t} ---")
        controller.step()

    # -------- Passenger enters elevator 0 and presses destination -------- #
    print("\nPassenger inside Elevator 0 presses floor 8")
    controller.elevators[0].addDestination(8)

    # continue simulation
    for t in range(5, 12):
        print(f"\n--- Step {t} ---")
        controller.step()
        for e in controller.elevators:
            print(f"Elevator {e.id}: Floor={e.current_floor}, Direction={e.direction}")


if __name__ == "__main__":
    main()