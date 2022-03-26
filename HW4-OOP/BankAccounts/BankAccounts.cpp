using namespace std;
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include "Date.hpp"
#include "Account.hpp"
#include "Withdrawal.hpp"
#include "Deposit.hpp"


string* ReadLine(){
    string inputs[4];
    cin >> inputs[0] >> inputs[1] >> inputs[2];
    int amount; cin >> amount;
    inputs[3] = to_string(amount);
    return inputs;
}

void CreateAccount(vector<Account> acc_array, vector<string> inputs, vector<string> codes){
    Account a1(inputs);
    acc_array.pushback(a1);
    codes.pushback(array[2])
}

void setAccountstatuses(vector<Account> acc_vect){
    for(int i=0, i<acc_vect.size())    
        if (acc_vect[i].netBalance<5000){
            acc.vect.status = 'Active'
        }
        else{
            acc.vect.status = 'Dormant'
        }
}


void DisplayAccount(Account acc){
    cout<< "Account Title: "    << acc.namewithoutdash() <<        endl
        << "Account Code: "     << acc.code <<                      endl
        << "Initial Balance: "  << acc.initBalance <<               endl
        << "Available Balance: "<< acc.netBalance <<                endl
        << "Current Status: "   << acc.status <<                    endl;
    
    cout << "Deposits:"          << endl;
    for (int i = 0; i < acc.Deposits.size(); i++)
    {
        cout << i << ". " << acc.Deposits[i].Amount << " on " << acc.Deposits[i].date.showslash() << " " << acc.Deposits[i].success << endl;
    }
    
    cout << "Withdrawals"          << endl;
    for (int i = 0; i < acc.Withdrawals.size(); i++)
    {
        cout << i << ". " << acc.Withdrawals[i].Amount << " on " << acc.Withdrawals[i].date.showslash() << " " << acc.Withdrawals[i].success << endl;
    }
}

int main()
{
    vector<Account> Accounts;
    vector<string>  Codes;
    while(){} // Pending
        string* inputs = ReadLine;
        if (inputs[0] == "Create"){
            CreateAccount(Accounts, inputs);
        }
        else{
            int index = 0;
            for(int i=0, i<Codes.size(), i++){
                if (Codes[i] == inputs[1]){
                    index = i; 
                    break;
                }
            Accounts[i].add_entry[inputs];
            }
        }

    setAccountstatuses(Accounts);

    for (int i = 0; i < Accounts.size(); i++)
    {
        DisplayAccount(Accounts[i]);
    }
    return 0;
}