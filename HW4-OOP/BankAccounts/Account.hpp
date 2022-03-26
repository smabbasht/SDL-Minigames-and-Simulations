//#include<fstream>
#include<string.h>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

class Account
{
    public:
    string title, code, fname, lname, status;
    int netBalance, initBalance;
    vector<Withdrawal>  Withdrawals;
    vector<Deposit>     Deposits;

    Account(string array[4]){
        vector<Withdrawal>  Withdrawals;
        vector<Deposit>     Deposits;
        status      = 'Active';
        code        = array[2];
        initBalance = netBalance = stoi(array[3]);
        title       = array[1];
    }

    string namewithoutdash(){
        replace((title).begin(), (title).end(), '-', ' ');        
        return title;
    }

    void add_entry(string array[3]){
        if (array[0] == "Withdrawal")
        {   
            Withdrawal with1;
            with1.Amount = array[2];
            with1Date opdate(array[3]); // Operation Date
            if(with1.Amount >= netBalance){
                with1.success = "Succesful"
                netBalance -= stoi(array[1]);
            }
            else{
                with1.success = "Denied"
                }
            withdrawals.pushabck(with1);
        }

        else if(array[0] == "Deposit")
        {
            Deposit dep1;
            dep1.Amount = array[2];
            dep1.Date opdate(array[3]); // Operation Date
            dep1.success = "Succesful"
            netBalance += stoi(array[1]);
            deposits.pushabck(dep1);
        }
        
    }
};