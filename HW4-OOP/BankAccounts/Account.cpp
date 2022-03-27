#include "Account.hpp"

Account::Account(vector<string> array)
{
    vector<Transaction> Withdrawals;
    vector<Transaction> Deposits;
    status = "Active";
    initBalance = netBalance = stoi(array[3]);
    code = array[2];
    title = array[1];
    // cout << array[1] << ' ' << array[2] << ' ' << array[3] << ' ' << endl;
}

string Account::namewithoutdash()
{
    replace((title).begin(), (title).end(), '-', ' ');
    return title;
}

void Account::add_entry(vector<string> array)
{
    Date date1(array[3]);
    if (array[0] == "Withdrawal")
    {
        Transaction with1 = {stoi(array[2]), date1, "Successful"};
        if (with1.Amount >= netBalance)
        {
            // cout << array[2] << endl;
            netBalance -= stoi(array[2]); // Error here
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
        netBalance += stoi(array[2]); // Error Here too
        Deposits.push_back(dep1);
    }
}
