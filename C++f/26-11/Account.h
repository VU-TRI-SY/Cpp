#include <iostream>
#include <vector>
#include "Transaction.h"
using namespace std;
class Account{
    private:
        string firstName_;
        string lastName_;
        int id_;
        int totalBalance_;
        vector<Transaction> transactions; 
        vector<Fund> funds;
    public:
        Account(int id, string firstName, string lastName){
            //this is a pointer that points to current object
            this->id_ = id;
            this->firstName_ = firstName;
            this->lastName_ = lastName;
            totalBalance_ = 0;
            //funds.push_back(Fund(0, "Money Market", 0));
            //funds.push_back(Fund(1, "Prime Money Market"));
            //...

        }
        bool deposit(int amount, int fundId);  
        bool withDraw(int amount, int fundId); 

        void displayHistory(); //display all tracsactions
        void displayHistory(int fundId);  //display all tracsactions with fundId passed
};
