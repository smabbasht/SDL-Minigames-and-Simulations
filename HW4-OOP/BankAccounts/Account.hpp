#include <vector>
#include <algorithm>
#include "Transaction.hpp"

class Account
{
public:
    // Account 
    string title, code, fname, lname, status;
    // netBalance tracks the Available Balance & Initial Deposit is stored in initBalance. 
    int netBalance, initBalance;
    vector<Transaction> Withdrawals; // Keeps the track of Withdrawals for the Account
    vector<Transaction> Deposits;    // Keeps the track of Deposits for the Account

    Account(vector<string> array);   // A constructor which takes a string vector and initialzes all the members with corresponding values.

    string namewithoutdash();        // Produces Name without underscore for write function faciliation

    void add_entry(vector<string> array);
    // This function decides whether the transaction is a Deposit or a Withdrawal and adds it to respective vector
    // Manages all the related functionalities.
};