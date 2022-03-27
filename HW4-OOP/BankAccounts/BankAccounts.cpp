#include <string>
#include <fstream>
#include <sstream>
#include "Account.cpp"

string outfilename = "results.txt";
string infilename = "bankinput.txt";
ofstream outfile(outfilename);

vector<string> ExtractLines(string filename)
{
    vector<string> lines;
    string line;

    ifstream input_file(filename);

    while (getline(input_file, line))
    {
        lines.push_back(line);
    }
    // lines.push_back("last line");

    // for (int i = 0; i < 17; i++)
    // {
    //     cout << lines[i] << " hi\n";
    // }

    return lines;
}

vector<string> ParseLine(string str)
{
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while (getline(ss, tok, ' '))
    {
        internal.push_back(tok);
    }
    return internal;
}

void CreateAccount(vector<Account> &acc_array,
                   vector<string> &inputs,
                   vector<string> &codes)
{
    Account a1(inputs);
    acc_array.push_back(a1);
    codes.push_back(inputs[2]);
    // cout << "Here in Create Account" << endl;
}

void setAccountstatuses(vector<Account> &acc_vect)
{
    for (int acc_vect_dumy = 0; acc_vect_dumy < acc_vect.size(); acc_vect_dumy++)
    {
        if (acc_vect[acc_vect_dumy].netBalance < 5000)
        {
            acc_vect[acc_vect_dumy].status = "Dormant";
        }
        else
        {
            acc_vect[acc_vect_dumy].status = "Active";
        }
    }
}

void WriteAccountFile(Account acc)
{
    string filename = "result.txt";
    fstream file;
    file.open(filename);

    outfile << "Account Title: " << acc.namewithoutdash() << endl
            << "Account Code: " << acc.code << endl
            << "Initial Balance: " << acc.initBalance << endl
            << "Available Balance: " << acc.netBalance << endl
            << "Current Status: " << acc.status << endl;

    outfile << "Deposits:" << endl;
    
    if(acc.Deposits.size()>0)
    {
        for (int acc_deposit_dumy = 0; acc_deposit_dumy < acc.Deposits.size(); acc_deposit_dumy++)
        {
            outfile << acc_deposit_dumy+1 << ". " << acc.Deposits[acc_deposit_dumy].Amount << " on "
                    << acc.Deposits[acc_deposit_dumy].Date.showslash() << endl;
        }
    }
    else
    {
        outfile << "No Deposits for this account" << endl;
    }
    
    outfile << "Withdrawals:" << endl;
    
    if(acc.Withdrawals.size()>0)        
        for (int acc_withdrawal_dumy = 0; acc_withdrawal_dumy < acc.Withdrawals.size(); acc_withdrawal_dumy++)
        {
            outfile << acc_withdrawal_dumy+1 << ". " << acc.Withdrawals[acc_withdrawal_dumy].Amount << " on "
                    << acc.Withdrawals[acc_withdrawal_dumy].Date.showslash() << " "
                    << acc.Withdrawals[acc_withdrawal_dumy].success << endl;
        }
    else
    {
        outfile << "No Withdrawals for this account" << endl;
    }
    
    outfile << endl;
}

int main()
{
    vector<Account> Accounts;
    vector<string> Codes;
    vector<string> Lines = ExtractLines(infilename);
    vector<string> inputs;
    //   cout << Lines.size();

    for (int i = 0; i < Lines.size(); i++)
    {
        inputs = ParseLine(Lines[i]);
        // cout << inputs[0] << " " << inputs[1] << " " << inputs[2] << " " << inputs[3] << " \n";

        if (inputs[0] == "Create")
        {
            // int n = Accounts.size();
            CreateAccount(Accounts, inputs, Codes);
            // cout << (n + 1 == Accounts.size());
        }
        else
        {
            int index;
            for (int finder = 0; finder < Codes.size(); finder++)
            {
                if (inputs[1] == Accounts[finder].code)
                {
                    index = finder;
                    break;
                }
            }
            Accounts[index].add_entry(inputs);
        }
    }

    setAccountstatuses(Accounts);

    for (int i = 0; i < Accounts.size(); i++)
    {
        WriteAccountFile(Accounts[i]);
    }
    return 0;
}