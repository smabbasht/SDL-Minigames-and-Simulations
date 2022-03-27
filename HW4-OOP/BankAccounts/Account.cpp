#include "Account.hpp"

class Account
{
    public:
    string title, code, fname, lname, status;
    int netBalance, initBalance;
    vector<Transaction>  Withdrawals;
    vector<Transaction>     Deposits;

    Account(vector<string> array){
        vector<Transaction>  Withdrawals;
        vector<Transaction>     Deposits;
        status      = 'Active';
        code        = array[2];
        initBalance = netBalance = stoi(array[3]);
        title       = array[1];
    }

    string namewithoutdash(){
        replace((title).begin(), (title).end(), '-', ' ');        
        return title;
    }

    void add_entry(vector<string> array){
        Date date1(array[3]);
        if (array[0] == "Withdrawal")
        {   
            Transaction with1 = {stoi(array[2]), date1, "Succesful"};
            if(with1.Amount >= netBalance){
                netBalance -= stoi(array[1]);
            }
            else{
                with1.success = "Denied";
                }
            Withdrawals.push_back(with1);
        }

        else if(array[0] == "Deposit")
        {
            Transaction dep1 = {stoi(array[2]), date1, "Succesful"};
            netBalance += stoi(array[1]);
            Deposits.push_back(dep1);
        }
        
    }
};