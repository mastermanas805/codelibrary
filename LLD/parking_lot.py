from enum import Enum
from abc import ABC, abstractmethod
from typing import Optional
import threading
import time

# 1. Added Truck to fulfill requirements and fixed typo
class VehicleSize(Enum):
    TWO_WHEELER = 1
    FOUR_WHEELER = 2
    TRUCK = 3

class Vehicle:
    def __init__(self, vehicleSize: VehicleSize, license_plate: str):
        self.vehicleSize = vehicleSize
        self.license_plate = license_plate

class ParkingSpot:
    def __init__(self, id: int, vehicleSize: VehicleSize):
        self.id = id
        self.vehicleSize = vehicleSize
        self.__occupied = False 

    def isOccupied(self) -> bool:
        return self.__occupied
    
    def park_vehicle(self):
        self.__occupied = True
        
    def unpark_vehicle(self):
        self.__occupied = False

class ParkingFloor:
    def __init__(self, floor: int, spots: list[ParkingSpot]):
        self.floor = floor
        self.spots = spots

class Ticket:
    def __init__(self, id: int, spot: ParkingSpot, createdAt: float):
        self.id = id
        self.spot = spot
        self.createdAt = createdAt

class Request:
    def __init__(self, vehicle: Vehicle):
        self.vehicle = vehicle

class FindSpotStrategy(ABC):
    @abstractmethod
    def findSpot(self, request: Request, floors: list[ParkingFloor]) -> Optional[ParkingSpot]:
        pass

class DefaultFindSpotStrategy(FindSpotStrategy):
    def findSpot(self, request: Request, floors: list[ParkingFloor]) -> Optional[ParkingSpot]:
        for floor in floors:
            for spot in floor.spots:
                if not spot.isOccupied() and spot.vehicleSize == request.vehicle.vehicleSize:
                    return spot
        return None

class ParkingLotSystem:
    def __init__(self, floors: list[ParkingFloor], strategy: FindSpotStrategy):
        self.floors = floors
        self.strategy = strategy
        self.tickets: dict[int, Ticket] = {}
        self.tkt_counter = 0
        self.lock = threading.Lock()

    def park_vehicle(self, request: Request) -> Optional[Ticket]:
        # Lock to ensure concurrent requests don't get the same spot
        with self.lock:
            spot = self.strategy.findSpot(request=request, floors=self.floors)
            if not spot:
                print("No Parking Spot Available")
                return None
            
            spot.park_vehicle()
            ticket = Ticket(self.tkt_counter, spot, time.time())
            self.tickets[self.tkt_counter] = ticket
            self.tkt_counter += 1
            return ticket
    
    def unpark_vehicle(self, ticket: Ticket):
        with self.lock:
            if ticket.id not in self.tickets:
                print("Invalid Ticket")
                return
            
            ticket.spot.unpark_vehicle()
            del self.tickets[ticket.id]
            print(f"Vehicle unparked successfully from spot {ticket.spot.id}")