#include<string>
#include<fstream>
#include<sstream>
#include "Account.cpp"

string outfilename = "results.txt";
string infilename  = "bankinput.txt";
ofstream outfile (outfilename);

vector<string> ExtractLines(string filename)
{
    vector<string> lines;
    string line;

    ifstream input_file(filename);

    while (getline(input_file, line)){
        lines.push_back(line);
    }
    //lines.push_back("last line");

    // for (int i = 0; i < 17; i++)
    // {
    //     cout << lines[i] << " hi\n";
    // } 
 
    return lines;
}

vector<string> ParseLine(string str){
    vector<string> internal; 
    stringstream ss(str); // Turn the string into a stream. 
    string tok; 
    
    while(getline(ss, tok, ' ')) { 
        internal.push_back(tok); 
    } 
    return internal; 
}


void CreateAccount(vector<Account> acc_array, vector<string> inputs, vector<string> codes){
    Account a1(inputs);
    acc_array.push_back(a1);
    codes.push_back(inputs[2]);
}

void setAccountstatuses(vector<Account> acc_vect){
    for(int i=0; i<acc_vect.size(); i++){    
        if (acc_vect[i].netBalance < 5000){
            acc_vect[i].status = "Active";
        }
        else{
            acc_vect[i].status = "Dormant";
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
    vector<Account> Accounts;
    vector<string>  Codes;
    vector<string>  Lines = ExtractLines(infilename);
    vector<string>  inputs;
 //   cout << Lines.size();
    

    for(int i=0; i<Lines.size(); i++){
        inputs = ParseLine(Lines[i]);
        //cout << inputs[0] << " " << inputs[1] << " " << inputs[2] << " " << inputs[3] << " \n";
        
        if (inputs[0] == "Create"){
            int n = Accounts.size();
            CreateAccount(Accounts, inputs, Codes);
            cout << (n+1==Accounts.size());
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
    }

    setAccountstatuses(Accounts);

    for (int i = 0; i < Accounts.size(); i++)
    {
        WriteAccountFile(Accounts[i]);
    }
    return 0;
}