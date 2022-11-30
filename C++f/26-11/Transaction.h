#include <iostream>
#include "Fund.h"
class Transaction{
    char type; 
    int primaryAccountId; 
    int primaryFundId; 

    int secondaryAccountId;
    int secondaryFundId; 
    int amount;
    string firstName;
    string lastName;
    string error;

    public: 
        Transaction(char type, int primaryAccountId,int primaryFundId, int amout);
        Transaction(char type, int primaryAccountId,int primaryFundId, int secondaryAccountId,int secondaryFundId, int amount);
        Transaction(char type, int primaryAccountId);
        Transaction(char type, int primaryAccountId, int primaryFundId);
        Transaction(char type, int primaryAccountId, string firstName, string lastName);
};
