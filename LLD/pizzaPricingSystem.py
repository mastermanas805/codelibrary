"""
You will have to initialize a new pizza, adding toppings (corn, onion etc) to it 
and calculate final price of pizza.

This is a fairly simple problem. But some interviewers may expect you to implement decorator design pattern. 
In my view that just complicates the solution without adding any benefit.

Your interviewer may add business rules as a follow up like these

    cheese burst cannot be added on small pizza or
    You get 30% discount on corn price when you take more than 2 servings and so on..


    
ENUMS:
    Topping
    PizzaSize

CLASS Pizza:
    size: PizzaSize
    toppings: Map<Topping, quantity>

INTERFACE PricingService:
    get_price(topping, size) -> int
    get_base_price(size) -> int

INTERFACE PricingRule:
    apply(pizza, current_total) -> int

CLASS StandardPricingService(PricingService)

RULES:
    BulkCornDiscountRule(PricingRule)

INTERFACE BillingStrategy:
    calculate_total(pizza) -> int

CLASS StandardBillingStrategy(BillingStrategy):
    pricing_service
    pricing_rules: List<PricingRule>

CLASS BillingCounter:
    billing_strategy
    get_bill(pizza) -> int

"""

from enum import Enum
from typing import Dict, List
from abc import ABC, abstractmethod


# ---------------- ENUMS ----------------
class Topping(Enum):
    CORN = "corn"
    ONION = "onion"


class PizzaSize(Enum):
    SMALL = "small"
    MEDIUM = "medium"
    LARGE = "large"


# ---------------- DOMAIN ----------------
class Pizza:
    def __init__(self, size: PizzaSize):
        self.size = size
        self.toppings: Dict[Topping, int] = {}

    def add_topping(self, topping: Topping, quantity: int = 1):
        self.toppings[topping] = self.toppings.get(topping, 0) + quantity


# ---------------- PRICING SERVICE ----------------
class PricingService(ABC):

    @abstractmethod
    def get_price(self, topping: Topping) -> int:
        pass

    @abstractmethod
    def get_base_price(self, size: PizzaSize) -> int:
        pass


class StandardPricingService(PricingService):
    BASE_PRICE = {
        PizzaSize.SMALL: 100,
        PizzaSize.MEDIUM: 150,
        PizzaSize.LARGE: 200,
    }

    TOPPING_PRICE = {
        Topping.CORN: 30,
        Topping.ONION: 20,
    }

    def get_price(self, topping: Topping) -> int:
        return self.TOPPING_PRICE.get(topping, 0)

    def get_base_price(self, size: PizzaSize) -> int:
        return self.BASE_PRICE[size]


# ---------------- PRICING RULES ----------------
class PricingRule(ABC):

    @abstractmethod
    def apply(self, pizza: Pizza, current_total: int) -> int:
        pass


class BulkCornDiscountRule(PricingRule):
    """
    30% discount on corn if quantity > 2
    """

    def __init__(self, pricing_service: PricingService):
        self.pricing_service = pricing_service

    def apply(self, pizza: Pizza, current_total: int) -> int:
        corn_qty = pizza.toppings.get(Topping.CORN, 0)

        if corn_qty > 2:
            corn_price = self.pricing_service.get_price(Topping.CORN)
            discount = int(corn_price * corn_qty * 0.3)
            return current_total - discount

        return current_total


# ---------------- BILLING STRATEGY ----------------
class BillingStrategy(ABC):

    @abstractmethod
    def calculate_total(self, pizza: Pizza) -> int:
        pass


class StandardBillingStrategy(BillingStrategy):
    def __init__(
        self,
        pricing_service: PricingService,
        pricing_rules: List[PricingRule] = None,
    ):
        self.pricing_service = pricing_service
        self.pricing_rules = pricing_rules or []

    def calculate_total(self, pizza: Pizza) -> int:
        # Base price
        total = self.pricing_service.get_base_price(pizza.size)

        # Toppings price
        for topping, qty in pizza.toppings.items():
            price = self.pricing_service.get_price(topping)
            total += price * qty

        # Apply pricing rules (optional)
        for rule in self.pricing_rules:
            total = rule.apply(pizza, total)

        return total


# ---------------- BILLING COUNTER ----------------
class BillingCounter:
    def __init__(self, billing_strategy: BillingStrategy):
        self.billing_strategy = billing_strategy

    def get_bill(self, pizza: Pizza) -> int:
        return self.billing_strategy.calculate_total(pizza)


# ---------------- USAGE ----------------
if __name__ == "__main__":
    pizza = Pizza(PizzaSize.MEDIUM)
    pizza.add_topping(Topping.CORN, 3)
    pizza.add_topping(Topping.ONION, 1)

    pricing_service = StandardPricingService()

    pricing_rules = [
        BulkCornDiscountRule(pricing_service)
    ]

    strategy = StandardBillingStrategy(
        pricing_service,
        pricing_rules
    )

    counter = BillingCounter(strategy)

    total = counter.get_bill(pizza)
    print("Final Price:", total)