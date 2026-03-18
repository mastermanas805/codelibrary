"""

Requirements

    The system should allow users to create accounts and manage their profile information.
    Users should be able to create groups and add other users to the groups.
    Users should be able to add expenses within a group, specifying the amount, description, and participants.
    The system should automatically split the expenses among the participants based on their share.
    Users should be able to view their individual balances with other users and settle up the balances.
    The system should support different split methods, such as equal split, percentage split, and exact amounts.
    Users should be able to view their transaction history and group expenses.
    The system should handle concurrent transactions and ensure data consistency.


Entities
    User
    Group
    Expense
    Split (abstract)
    ├── EqualSplit
    ├── ExactSplit
    └── PercentageSplit

    ExpenseManager
    BalanceSheet
    SplitStrategy (validator)

"""

from __future__ import annotations
from typing import Dict, List, Set, DefaultDict
from collections import defaultdict
import threading
from abc import ABC


# -------------------- USER --------------------
class User:
    def __init__(self, user_id: int, name: str, email: str) -> None:
        self.user_id: int = user_id
        self.name: str = name
        self.email: str = email

    def __repr__(self) -> str:
        return self.name


# -------------------- GROUP --------------------
class Group:
    def __init__(self, group_id: int, name: str) -> None:
        self.group_id: int = group_id
        self.name: str = name
        self.members: Set[User] = set()
        self.expenses: List[Expense] = []

    def add_member(self, user: User) -> None:
        self.members.add(user)


# -------------------- SPLIT CLASSES --------------------
class Split(ABC):
    def __init__(self, user: User) -> None:
        self.user: User = user
        self.amount: float = 0.0


class EqualSplit(Split):
    pass


class ExactSplit(Split):
    def __init__(self, user: User, amount: float) -> None:
        super().__init__(user)
        self.amount: float = amount


class PercentageSplit(Split):
    def __init__(self, user: User, percent: float) -> None:
        super().__init__(user)
        self.percent: float = percent


# -------------------- EXPENSE --------------------
class Expense:
    def __init__(
        self,
        expense_id: int,
        paid_by: User,
        amount: float,
        splits: List[Split],
        description: str = ""
    ) -> None:
        self.expense_id: int = expense_id
        self.paid_by: User = paid_by
        self.amount: float = amount
        self.splits: List[Split] = splits
        self.description: str = description

    def __repr__(self) -> str:
        return f"{self.description} | {self.amount} paid by {self.paid_by}"


# -------------------- VALIDATOR --------------------
class SplitValidator:

    @staticmethod
    def validate_exact(splits: List[ExactSplit], total_amount: float) -> bool:
        return round(sum(split.amount for split in splits), 2) == total_amount

    @staticmethod
    def validate_percentage(splits: List[PercentageSplit]) -> bool:
        return round(sum(split.percent for split in splits), 2) == 100.0


# -------------------- BALANCE SHEET --------------------
class BalanceSheet:
    def __init__(self) -> None:
        self.balances: DefaultDict[User, DefaultDict[User, float]] = \
            defaultdict(lambda: defaultdict(float))
        # balances[A][B] = amount A owes B

    def update_balance(self, paid_by: User, splits: List[Split]) -> None:
        for split in splits:
            if split.user == paid_by:
                continue

            self.balances[split.user][paid_by] += split.amount
            self.balances[paid_by][split.user] -= split.amount

    def get_user_balance(self, user: User) -> Dict[User, float]:
        return self.balances[user]

    def show_all_balances(self) -> None:
        for user, others in self.balances.items():
            for other, amount in others.items():
                if amount > 0:
                    print(f"{user.name} owes {other.name}: {amount}")


# -------------------- EXPENSE MANAGER --------------------
class ExpenseManager:
    def __init__(self) -> None:
        self.users: Dict[int, User] = {}
        self.groups: Dict[int, Group] = {}
        self.balance_sheet: BalanceSheet = BalanceSheet()
        self.lock: threading.Lock = threading.Lock()
        self.expense_id_counter: int = 0

    # -------- USER --------
    def add_user(self, user: User) -> None:
        self.users[user.user_id] = user

    # -------- GROUP --------
    def create_group(self, group: Group) -> None:
        self.groups[group.group_id] = group

    def add_user_to_group(self, group_id: int, user: User) -> None:
        self.groups[group_id].add_member(user)

    # -------- EXPENSE --------
    def add_expense(
        self,
        group_id: int,
        paid_by: User,
        amount: float,
        splits: List[Split],
        split_type: str,
        description: str = ""
    ) -> None:

        with self.lock:
            self.expense_id_counter += 1

            if split_type == "EQUAL":
                self._handle_equal_split(amount, splits)

            elif split_type == "EXACT":
                if not SplitValidator.validate_exact(splits, amount):  # type: ignore
                    raise ValueError("Invalid exact split")

            elif split_type == "PERCENT":
                if not SplitValidator.validate_percentage(splits):  # type: ignore
                    raise ValueError("Invalid percentage split")
                self._handle_percentage_split(amount, splits)

            expense = Expense(
                self.expense_id_counter,
                paid_by,
                amount,
                splits,
                description
            )

            self.groups[group_id].expenses.append(expense)
            self.balance_sheet.update_balance(paid_by, splits)

    def _handle_equal_split(self, amount: float, splits: List[Split]) -> None:
        share: float = round(amount / len(splits), 2)
        for split in splits:
            split.amount = share

    def _handle_percentage_split(self, amount: float, splits: List[Split]) -> None:
        for split in splits:
            percent_split: PercentageSplit = split  # type casting
            split.amount = round(amount * percent_split.percent / 100, 2)

    # -------- BALANCES --------
    def show_balances(self) -> None:
        self.balance_sheet.show_all_balances()

    def show_user_balance(self, user: User) -> None:
        balances = self.balance_sheet.get_user_balance(user)
        for other, amount in balances.items():
            if amount > 0:
                print(f"{user.name} owes {other.name}: {amount}")
            elif amount < 0:
                print(f"{other.name} owes {user.name}: {-amount}")

    # -------- SETTLE --------
    def settle_up(self, user1: User, user2: User, amount: float) -> None:
        with self.lock:
            self.balance_sheet.balances[user1][user2] -= amount
            self.balance_sheet.balances[user2][user1] += amount

    # -------- HISTORY --------
    def get_group_expenses(self, group_id: int) -> List[Expense]:
        return self.groups[group_id].expenses

    def get_user_expenses(self, user: User) -> List[Expense]:
        result: List[Expense] = []
        for group in self.groups.values():
            for expense in group.expenses:
                if any(split.user == user for split in expense.splits):
                    result.append(expense)
        return result


# -------------------- DRIVER CODE --------------------
if __name__ == "__main__":
    manager = ExpenseManager()

    u1 = User(1, "Alice", "a@mail.com")
    u2 = User(2, "Bob", "b@mail.com")
    u3 = User(3, "Charlie", "c@mail.com")

    manager.add_user(u1)
    manager.add_user(u2)
    manager.add_user(u3)

    g1 = Group(1, "Trip")
    manager.create_group(g1)

    manager.add_user_to_group(1, u1)
    manager.add_user_to_group(1, u2)
    manager.add_user_to_group(1, u3)

    splits = [EqualSplit(u1), EqualSplit(u2), EqualSplit(u3)]
    manager.add_expense(1, u1, 300.0, splits, "EQUAL", "Dinner")

    splits = [
        ExactSplit(u1, 100.0),
        ExactSplit(u2, 150.0),
        ExactSplit(u3, 50.0)
    ]
    manager.add_expense(1, u2, 300.0, splits, "EXACT", "Taxi")

    splits = [
        PercentageSplit(u1, 50.0),
        PercentageSplit(u2, 30.0),
        PercentageSplit(u3, 20.0)
    ]
    manager.add_expense(1, u3, 200.0, splits, "PERCENT", "Hotel")

    print("\n--- All Balances ---")
    manager.show_balances()

    print("\n--- Alice Balance ---")
    manager.show_user_balance(u1)

    print("\n--- Group Expenses ---")
    for exp in manager.get_group_expenses(1):
        print(exp)