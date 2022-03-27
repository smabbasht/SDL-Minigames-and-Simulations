#include<vector>
#include<algorithm>
#include "Transaction.hpp"

class Account
{
    public:
    string title, code, fname, lname, status;
    int netBalance, initBalance;
    vector<Transaction>  Withdrawals;
    vector<Transaction>     Deposits;

    Account(vector<string> array);

    string namewithoutdash();

    void add_entry(vector<string> array);
};