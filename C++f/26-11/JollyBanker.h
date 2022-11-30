// -> creat BSTree -> lưu accounts
// -> creat Queue -> lưu các transactions xếp hàng đợi xử lý
// -> viết logic để xử lý transaction
#include <iostream>
#include <queue>
#include "Account.h"
#include "Fund.h"
#include "Transaction.h"
#include "BinarySearchTree.h"

class JollyBanker{
    private:
        queue<Transaction> transactionList;
	    BSTree accountList;
        // vector<Transaction> failTransactions; ?????? store fail transactions that cannot store in account 
    public:
        JollyBanker();
	    ~JollyBanker(); // not use Dynamic allocate -> can remove destructor
        bool loadTransactions();// read all transactions from text file, return true if load succesfully, otherwise return false
        void handleTransactions(); // dequeue(delete a transaction from Queue) -> handle -> load to history transactions of accounts related
        void Display(); //display all accounts after transactions handled
};