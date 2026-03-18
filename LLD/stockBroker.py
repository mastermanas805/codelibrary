"""

Requirements

    The online stock brokerage system should allow users to create and manage their trading accounts.
    Users should be able to buy and sell stocks, as well as view their portfolio and transaction history.
    The system should provide real-time stock quotes and market data to users.
    The system should handle order placement, execution, and settlement processes.
    The system should enforce various business rules and validations, such as checking account balances and stock availability.
    The system should handle concurrent user requests and ensure data consistency and integrity.
    The system should be scalable and able to handle a large number of users and transactions.
    The system should be secure and protect sensitive user information.

Key Components

    User → Account → Portfolio

    Stock → Market Data

    Order (Abstract) → Buy/Sell Orders

    StockBroker (Singleton) → Core engine

    Exceptions → Business rules

"""

from __future__ import annotations
from typing import Dict, List, Optional
from abc import ABC, abstractmethod
from enum import Enum
import threading
import uuid


# ---------------- ENUM ---------------- #

class OrderStatus(Enum):
    PENDING = "PENDING"
    EXECUTED = "EXECUTED"
    REJECTED = "REJECTED"


# ---------------- EXCEPTIONS ---------------- #

class InsufficientFundsException(Exception):
    pass


class InsufficientStockException(Exception):
    pass


# ---------------- USER ---------------- #

class User:
    def __init__(self, name: str, email: str):
        self.user_id: str = str(uuid.uuid4())
        self.name: str = name
        self.email: str = email


# ---------------- ACCOUNT ---------------- #

class Account:
    def __init__(self, user: User):
        self.account_id: str = str(uuid.uuid4())
        self.user: User = user
        self.balance: float = 0.0
        self.lock = threading.Lock()
        self.portfolio = Portfolio()

    def deposit(self, amount: float) -> None:
        with self.lock:
            self.balance += amount

    def withdraw(self, amount: float) -> None:
        with self.lock:
            if self.balance < amount:
                raise InsufficientFundsException("Insufficient funds")
            self.balance -= amount


# ---------------- STOCK ---------------- #

class Stock:
    def __init__(self, symbol: str, name: str, price: float):
        self.symbol: str = symbol
        self.name: str = name
        self.price: float = price
        self.lock = threading.Lock()

    def update_price(self, new_price: float) -> None:
        with self.lock:
            self.price = new_price


# ---------------- PORTFOLIO ---------------- #

class Portfolio:
    def __init__(self):
        self.holdings: Dict[str, int] = {}  # symbol -> quantity
        self.lock = threading.Lock()

    def add_stock(self, symbol: str, quantity: int) -> None:
        with self.lock:
            self.holdings[symbol] = self.holdings.get(symbol, 0) + quantity

    def remove_stock(self, symbol: str, quantity: int) -> None:
        with self.lock:
            if self.holdings.get(symbol, 0) < quantity:
                raise InsufficientStockException("Not enough stock")
            self.holdings[symbol] -= quantity
            if self.holdings[symbol] == 0:
                del self.holdings[symbol]


# ---------------- ORDER ---------------- #

class Order(ABC):
    def __init__(
        self,
        account: Account,
        stock: Stock,
        quantity: int,
        price: float
    ):
        self.order_id: str = str(uuid.uuid4())
        self.account: Account = account
        self.stock: Stock = stock
        self.quantity: int = quantity
        self.price: float = price
        self.status: OrderStatus = OrderStatus.PENDING

    @abstractmethod
    def execute(self) -> None:
        pass


# ---------------- BUY ORDER ---------------- #

class BuyOrder(Order):
    def execute(self) -> None:
        total_cost = self.quantity * self.price

        try:
            self.account.withdraw(total_cost)
            self.account.portfolio.add_stock(self.stock.symbol, self.quantity)
            self.status = OrderStatus.EXECUTED
        except InsufficientFundsException:
            self.status = OrderStatus.REJECTED


# ---------------- SELL ORDER ---------------- #

class SellOrder(Order):
    def execute(self) -> None:
        try:
            self.account.portfolio.remove_stock(self.stock.symbol, self.quantity)
            total_gain = self.quantity * self.price
            self.account.deposit(total_gain)
            self.status = OrderStatus.EXECUTED
        except InsufficientStockException:
            self.status = OrderStatus.REJECTED


# ---------------- STOCK BROKER (Singleton) ---------------- #

class StockBroker:
    _instance: Optional[StockBroker] = None
    _lock = threading.Lock()

    def __init__(self):
        self.accounts: Dict[str, Account] = {}
        self.stocks: Dict[str, Stock] = {}
        self.orders: List[Order] = []
        self.order_lock = threading.Lock()

    @classmethod
    def get_instance(cls) -> StockBroker:
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = cls()
        return cls._instance

    def create_account(self, user: User) -> Account:
        account = Account(user)
        self.accounts[account.account_id] = account
        return account

    def add_stock(self, stock: Stock) -> None:
        self.stocks[stock.symbol] = stock

    def place_order(self, order: Order) -> None:
        with self.order_lock:
            self.orders.append(order)

        self.process_order(order)

    def process_order(self, order: Order) -> None:
        order.execute()

    def get_stock_price(self, symbol: str) -> float:
        return self.stocks[symbol].price


# ---------------- SYSTEM ENTRY ---------------- #

class StockBrokerageSystem:
    @staticmethod
    def run_demo():
        broker = StockBroker.get_instance()

        # Create user and account
        user = User("Manas", "manas@example.com")
        account = broker.create_account(user)

        # Deposit money
        account.deposit(10000)

        # Add stock
        stock = Stock("AAPL", "Apple Inc.", 150)
        broker.add_stock(stock)

        # Buy order
        buy_order = BuyOrder(account, stock, 10, 150)
        broker.place_order(buy_order)

        print("Buy Order Status:", buy_order.status)

        # Sell order
        sell_order = SellOrder(account, stock, 5, 155)
        broker.place_order(sell_order)

        print("Sell Order Status:", sell_order.status)

        # Portfolio
        print("Portfolio:", account.portfolio.holdings)

        # Balance
        print("Balance:", account.balance)


if __name__ == "__main__":
    StockBrokerageSystem.run_demo()