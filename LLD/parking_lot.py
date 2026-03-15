import threading
import time
from enum import Enum
from abc import ABC, abstractmethod
from typing import Optional

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
        self.exitAt = int

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
        with self.lock:
            spot = self.strategy.findSpot(request=request, floors=self.floors)
            if not spot:
                print(f"No Parking Spot Available for {request.vehicle.license_plate}")
                return None
            
            spot.park_vehicle()
            ticket = Ticket(self.tkt_counter, spot, time.time())
            self.tickets[self.tkt_counter] = ticket
            self.tkt_counter += 1
            print(f"Vehicle {request.vehicle.license_plate} parked at Spot {spot.id}")
            return ticket
    
    def unpark_vehicle(self, ticket: Ticket):
        with self.lock:
            if ticket.id not in self.tickets:
                print("Invalid Ticket")
                return
            
            ticket.spot.unpark_vehicle()
            del self.tickets[ticket.id]
            # Fee calculation happens here in the workflow
            ticket.exitAt = time.time()
            self._calculate_fee(ticket)
            print(f"Vehicle unparked successfully from spot {ticket.spot.id}")

    def _calculate_fee(self, ticket: Ticket):
        # Time Ticker Logic: 1 second of real time = 1 hour of parking time
        duration_seconds = ticket.exitAt - ticket.createdAt
        simulated_hours = max(1, int(duration_seconds * 10)) # Multiplier for demo
        
        rate = {
            VehicleSize.TWO_WHEELER: 10,
            VehicleSize.FOUR_WHEELER: 20,
            VehicleSize.TRUCK: 50
        }[ticket.spot.vehicleSize]
        
        total_fee = simulated_hours * rate
        print(f"--- Receipt | Ticket ID: {ticket.id} | Duration: {simulated_hours} hrs | Total Fee: ${total_fee} ---")

# --- MAIN EXECUTION BLOCK ---

if __name__ == "__main__":
    # 1. Setup Spots and Floors
    spots_f1 = [ParkingSpot(101, VehicleSize.TWO_WHEELER), ParkingSpot(102, VehicleSize.FOUR_WHEELER)]
    spots_f2 = [ParkingSpot(201, VehicleSize.TRUCK)]
    
    floor1 = ParkingFloor(1, spots_f1)
    floor2 = ParkingFloor(2, spots_f2)
    
    # 2. Initialize System
    strategy = DefaultFindSpotStrategy()
    parking_system = ParkingLotSystem([floor1, floor2], strategy)
    
    # 3. Simulate Parking
    v1 = Vehicle(VehicleSize.FOUR_WHEELER, "ABC-123")
    v2 = Vehicle(VehicleSize.TRUCK, "TRK-999")
    
    tkt1 = parking_system.park_vehicle(Request(v1))
    tkt2 = parking_system.park_vehicle(Request(v2))
    
    print("\n... Vehicles are parked. Simulating time passage ...\n")
    time.sleep(2) # Wait 2 seconds
    
    # 4. Simulate Unparking
    if tkt1:
        parking_system.unpark_vehicle(tkt1)
    if tkt2:
        parking_system.unpark_vehicle(tkt2)