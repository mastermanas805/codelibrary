Wallet Service
 1. Intra Wallet Transactions
 2. View thier balance in Wallet
 3. Download their statement at anytime
 4. Load API that loads money into wallet

 1M active users
 5m transactions per day



Non-Functional Req:
1. Balance, Transaction( consistency >> availablity)
2. 10x 5M transactions
3. Balance < 50ms
   Transaction < 200ms
4. Fault Tolerance durable logs with Strong ACID


Back Env Calc

1. 50M/day = 5*10^6/86400 = 60 QPS
  300QPS for Balance
2. 200B * 50M = 1GB/day
3. 4:1 Read:Write


Core Entities:

1. Wallet
2. Transaction
3. Ledger Entry
4. User

API Design

1. GET /wallet/{id}/balance
2. POST /wallet/transfer
   {
    "sender": "",
    "receiver": "",
    "amount": "",
    "idempotencyKey": ""
   }


1. Wallet 
 1. Wallet ID  BIGINT/UUID PK
 2. user_id ID FK
 3. Balance BIGINT
 4. Version UUID

2. Ledger Entry
 1. entry id BIGINT PK
 2. wallet id BIGINT FK
 3. Transaction ID BIGINT FK
 4. Amount BIGINT 
 5. created at Timestamp

3. Transaction
  1. id BIGINT PK
  2. sender_account_id BIGINT FK
  3. receiver_account_id BIGINT FK
  4. amount BIGINT
  5. UUID 


150 

100 -> from A to B
1. check for the balance of A
2. debit from A
3. credit to B


SELECT balance, version as sender_version from wallet where wallet_id="1234";

BEGIN;

UPDATE wallet SET balance = balance - 100, version=new_uuid where wallet_id='1234' AND balance >= 100 AND version=sender_version;

COMMIT;