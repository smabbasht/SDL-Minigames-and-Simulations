#include "Account.hpp"

Account::Account(vector<string> array)
{
    vector<Transaction> Withdrawals;
    vector<Transaction> Deposits;
    netBalance  = stoi(array[3]);
    initBalance = stoi(array[3]);
    status = "Active";
    code   = array[2];
    title  = array[1];
    // cout << array[1] << ' ' << array[2] << ' ' << array[3] << ' ' << endl;
}

string Account::namewithoutdash()
{
    replace((title).begin(), (title).end(), '_', ' ');
    return title;
}

void Account::add_entry(vector<string> array)
{
    Date date1(array[3]);
    if (array[0] == "Withdrawal")
    {
        Transaction with1 = {stoi(array[2]), date1, "Successful"};
        if (netBalance >= with1.Amount)
        {
            // cout << array[2] << endl;
            netBalance -= with1.Amount; // Error here
        }
        else
        {
            with1.success = "Denied";
        }
        Withdrawals.push_back(with1);
    }

    else if (array[0] == "Deposit")
    {
        Transaction dep1 = {stoi(array[2]), date1, "Successful"};
        // cout << array[1] << endl;
        netBalance += dep1.Amount; // Error Here too
        Deposits.push_back(dep1);
    }
}
