#include<string>
#include<fstream>
#include "Account.hpp"

vector<string> ReadLine(){
    vector<string> inputs;
    cin >> inputs[0] >> inputs[1] >> inputs[2];
    int amount; cin >> amount;
    inputs[3] = to_string(amount);
    return inputs;
}

void CreateAccount(vector<Account> acc_array, vector<string> inputs, vector<string> codes){
    Account a1(inputs);
    acc_array.push_back(a1);
    codes.push_back(inputs[2]);
}

void setAccountstatuses(vector<Account> acc_vect){
    for(int i=0; i<acc_vect.size(); i++){    
        if (acc_vect[i].netBalance < 5000){
            acc_vect[i].status = 'Active';
        }
        else{
            acc_vect[i].status = 'Dormant';
        }
    }
}


void WriteAccountFile(Account acc, string filename){
    

    outfile << "Account Title: "    << acc.namewithoutdash() <<         endl
        << "Account Code: "     << acc.code <<                      endl
        << "Initial Balance: "  << acc.initBalance <<               endl
        << "Available Balance: "<< acc.netBalance <<                endl
        << "Current Status: "   << acc.status <<                    endl;
    
    outfile  << "Deposits:"          << endl;
    for (int i = 0; i < acc.Deposits.size(); i++)
    {
        outfile  << i << ". " << acc.Deposits[i].Amount << " on " << acc.Deposits[i].Date.showslash() << " " << acc.Deposits[i].success << endl;
    }
    
    outfile  << "Withdrawals"          << endl;
    for (int i = 0; i < acc.Withdrawals.size(); i++)
    {
        outfile  << i << ". " << acc.Withdrawals[i].Amount << " on " << acc.Withdrawals[i].Date.showslash() << " " << acc.Withdrawals[i].success << endl;
    }
}

int main()
{
    string write_string;
    string filename = "bankinput.txt";
    vector<Account> Accounts;
    vector<string>  Codes;
    //while(){} // Pending
    vector<string> inputs = ReadLine();
    if (inputs[0] == "Create"){
        CreateAccount(Accounts, inputs, Codes);
    }
    else{
        int index = 0;
        for(int i=0; i<Codes.size(); i++){
            if (Codes[i] == inputs[1]){
                index = i; 
                break;
            }
        Accounts[i].add_entry(inputs);
        }
    }

    setAccountstatuses(Accounts);

    for (int i = 0; i < Accounts.size(); i++)
    {
        WriteAccountFile(Accounts[i], filename);
    }
    return 0;
}