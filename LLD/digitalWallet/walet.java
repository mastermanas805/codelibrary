import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.ReentrantLock;

enum Currency { USD, INR }
enum Status { PROCESSING, COMPLETED, FAILED }

class Transaction {
    int id;
    int from;
    int to;
    double amount;
    Currency currency;
    Status status;

    public Transaction(int id, int from, int to, double amount, Currency curr) {
        this.id = id; this.from = from; this.to = to; this.amount = amount; this.currency = curr;
    }
}

class Account {
    int id;
    double balance;
    Currency currency;
    List<Transaction> txns = new ArrayList<>();
    final ReentrantLock lock = new ReentrantLock();

    public Account(int id, Currency currency) { this.id = id; this.currency = currency; }
}

public class WalletService {
    private final Map<Integer, Account> accounts = new ConcurrentHashMap<>();
    private final Map<String, Double> rates = new HashMap<>();
    private int txnCounter = 0;

    public void addRate(Currency from, Currency to, double rate) {
        rates.put(from + "-" + to, rate);
    }

    public void sendMoney(int fromId, int toId, double amount) throws Exception {
        Account s = accounts.get(fromId);
        Account r = accounts.get(toId);

        // Ordered Locking
        Account first = s.id < r.id ? s : r;
        Account second = s.id < r.id ? r : s;

        first.lock.lock();
        try {
            second.lock.lock();
            try {
                if (s.balance < amount) throw new Exception("Insufficient Balance");
                
                double rate = rates.getOrDefault(s.currency + "-" + r.currency, 1.0);
                s.balance -= amount;
                r.balance += (amount * rate);
                
                Transaction t = new Transaction(++txnCounter, fromId, toId, amount, s.currency);
                t.status = Status.COMPLETED;
                s.txns.add(t); r.txns.add(t);
                
                System.out.println("Transfer successful from " + fromId + " to " + toId);
            } finally {
                second.lock.unlock();
            }
        } finally {
            first.lock.unlock();
        }
    }

    public static void main(String[] args) throws Exception {
        WalletService ws = new WalletService();
        ws.addRate(Currency.USD, Currency.INR, 83.0);
        
        Account a1 = new Account(1, Currency.USD); a1.balance = 100;
        Account a2 = new Account(2, Currency.INR);
        
        ws.accounts.put(1, a1); ws.accounts.put(2, a2);
        ws.sendMoney(1, 2, 10.0);
    }
}