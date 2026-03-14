"""
Elevator Design 

1. The elevator is designed to carry a maximum load of 1000 kg.
2. Gets request from the user to go to a specific floor.
3. The elevator moves up or down based on the user's request.
4. The elevator has a display panel that shows the current floor and the direction of movement.



Entities:
1. Direction (ENUM)
2. Elevator
    - current_floor
    - direction
    - add_request(request)
    - step()


3. Elevator Controller
    - elevators
    - request_queue
    - assign_elevator(request)
    - step()

4. Request
"""

from enum import Enum
from abc import ABC, abstractmethod

class ElevatorInterface(ABC):
    @abstractmethod
    def add_request(self, request):
        pass
    
    @abstractmethod
    def step(self):
        pass

class ElevatorAssignmentInterface(ABC):
    @abstractmethod
    def assign_elevator(self, request):
        pass

class RoundRobinAssignment(ElevatorAssignmentInterface):
    def __init__(self):
        self.counter = 0

    def assign_elevator(self, request, elevators):
        selected_elevator = elevators[self.counter]
        selected_elevator.add_request(request)
        self.counter = (self.counter + 1) % len(elevators)


class NearestElevatorAssignment(ElevatorAssignmentInterface):
    def assign_elevator(self, request, elevators):
        nearest_elevator = min(elevators, key=lambda e: abs(e.current_floor - request.floor))
        nearest_elevator.add_request(request)


class Direction(Enum):
    UP = 1
    DOWN = -1
    IDLE = 0

class Request:
    def __init__(self, floor):
        self.floor = floor

class Elevator(ElevatorInterface):
    def __init__(self):
        self.current_floor = 0
        self.direction = Direction.IDLE
        self.requests = []
    
    def add_request(self, request):
        self.requests.append(request)
        self.__update_direction()

    def step(self):
        if self.direction == Direction.IDLE:
            return
        
        if self.direction == Direction.UP:
            self.current_floor += 1
        elif self.direction == Direction.DOWN:
            self.current_floor -= 1
        
        # Check if we have reached the requested floor
        for request in self.requests:
            if request.floor == self.current_floor:
                self.requests.remove(request)
                break
        
        self.__update_direction()
    
    def __update_direction(self):
        if not self.requests:
            self.direction = Direction.IDLE
            return
        
        if self.direction == Direction.IDLE:
            if self.requests[0].floor > self.current_floor:
                self.direction = Direction.UP
            else:
                self.direction = Direction.DOWN
        elif self.direction == Direction.UP:
            if self.requests[0].floor < self.current_floor:
                self.direction = Direction.DOWN
        elif self.direction == Direction.DOWN:
            if self.requests[0].floor > self.current_floor:
                self.direction = Direction.UP

class ElevatorController(RoundRobinAssignment, ElevatorInterface):

    def __init__ (self, elevators: list[Elevator], assignment_strategy: ElevatorAssignmentInterface):
        self.elevators = elevators
        self.assignment_strategy = assignment_strategy
    
    def step(self):
        for elevator in self.elevators:
            elevator.step()
    
    def add_request(self, request):
        self.assignment_strategy.assign_elevator(request, self.elevators)


if __name__ == "__main__":
    elevator1 = Elevator()
    elevator2 = Elevator()
    elevators =[elevator1, elevator2]
    controller = ElevatorController(elevators, RoundRobinAssignment())

    controller.add_request(Request(5))
    controller.add_request(Request(3))
    controller.add_request(Request(7))

    for _ in range(10):
        controller.step()
        print(f"Elevator 1: Floor {elevator1.current_floor}, Direction {elevator1.direction}")
        print(f"Elevator 2: Floor {elevator2.current_floor}, Direction {elevator2.direction}")


