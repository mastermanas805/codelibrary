import threading
import time
from enum import Enum
from typing import Dict, List, Optional

class Currency(Enum):
    USD = "USD"
    INR = "INR"

class TransactionStatus(Enum):
    PROCESSING = "PROCESSING"
    COMPLETED = "COMPLETED"
    FAILED = "FAILED"

class User:
    def __init__(self, user_id: int, name: str):
        self.id = user_id
        self.name = name

class Transaction:
    def __init__(self, txn_id: int, from_id: int, to_id: int, amount: float, currency: Currency):
        self.id = txn_id
        self.from_id = from_id
        self.to_id = to_id
        self.amount = amount
        self.currency = currency
        self.status = TransactionStatus.PROCESSING
        self.timestamp = time.time()

class Account:
    def __init__(self, acc_id: int, user: User, currency: Currency):
        self.id = acc_id
        self.user = user
        self.balance = 0.0
        self.currency = currency
        self.transactions: List[Transaction] = []
        self.lock = threading.Lock()

class WalletService:
    def __init__(self):
        self.accounts: Dict[int, Account] = {}
        self.rates: Dict[str, float] = {}
        self.txn_counter = 0
        self.counter_lock = threading.Lock()

    def add_account(self, account: Account):
        self.accounts[account.id] = account

    def add_rate(self, base: Currency, target: Currency, rate: float):
        self.rates[f"{base.value}-{target.value}"] = rate

    def convert(self, amount: float, from_curr: Currency, to_curr: Currency) -> float:
        if from_curr == to_curr: return amount
        key = f"{from_curr.value}-{to_curr.value}"
        if key in self.rates: return amount * self.rates[key]
        reverse_key = f"{to_curr.value}-{from_curr.value}"
        if reverse_key in self.rates: return amount / self.rates[reverse_key]
        raise ValueError("Rate not found")

    def send_money(self, sender_id: int, receiver_id: int, amount: float):
        s = self.accounts.get(sender_id)
        r = self.accounts.get(receiver_id)
        if not s or not r: raise Exception("Account not found")

        # Ordered Locking to prevent deadlock
        first, second = (s, r) if s.id < r.id else (r, s)
        
        with first.lock:
            with second.lock:
                if s.balance < amount:
                    raise Exception("Insufficient funds")
                
                converted = self.convert(amount, s.currency, r.currency)
                s.balance -= amount
                r.balance += converted
                
                with self.counter_lock:
                    self.txn_counter += 1
                    txn = Transaction(self.txn_counter, sender_id, receiver_id, amount, s.currency)
                    txn.status = TransactionStatus.COMPLETED
                    s.transactions.append(txn)
                    r.transactions.append(txn)
                print(f"Transferred {amount} {s.currency.value} to {receiver_id}")

# Usage Example
ws = WalletService()
ws.add_rate(Currency.USD, Currency.INR, 80.0)
a1 = Account(1, User(1, "Alice"), Currency.USD)
a2 = Account(2, User(2, "Bob"), Currency.INR)
a1.balance = 100.0
ws.add_account(a1); ws.add_account(a2)
ws.send_money(1, 2, 50.0)