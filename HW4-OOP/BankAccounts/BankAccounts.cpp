#include<string>
#include<fstream>
#include "Account.hpp"

string filename = "bankinput.txt";
ofstream outfile (filename);

vector<string> ExtractLines(string filename)
{
    vector<string> lines;
    string line;

    ifstream input_file(filename);

    while (getline(input_file, line)){
        lines.push_back(line);
    }
    lines.push_back("last line");
    return lines;
}

vector<string> ParseLine(string str){
    vector<string> inputs;
    
    string word = "";
    int i = 0;
    for (auto x : str) 
    {
        if (x == ' ')
        {
            inputs[i] = word;
            word = "";
            i++;
        }
        else {
            word = word + x;
        }
    }

    inputs[i] = word;
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


void WriteAccountFile(Account acc){
    // fstream file;
    // file.open(filename);

    outfile << "Account Title: "    << acc.namewithoutdash() <<     endl
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
    string infilename = "bankinput.txt";
    string outfilename = "results.txt";
    ofstream outfile (outfilename);
    
    vector<Account> Accounts;
    vector<string>  Codes;
    vector<string>  Lines = ExtractLines(infilename);
    vector<string> inputs;

    for(int i=0; i<Accounts.size(); i++)    
        inputs = ParseLine(Lines[i]);
        if (inputs[0] == "Create"){
            CreateAccount(Accounts, inputs, Codes);
        }
        else{
            int index;
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
        WriteAccountFile(Accounts[i]);
    }
    return 0;
}