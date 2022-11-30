#include <iostream>
class Fund{
    string name; //id = 0 -> name = "money market"
    int id; //0->7
    int balance;
    public:
        Fund(int id, string name, int balance); // creat fund with id, name and balance(= 0 or != 0)
        Fund(int id, string name); //balance = 0
};

