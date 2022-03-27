#include <string>
#include <fstream>
#include <sstream>
#include "Account.cpp"

string outfilename = "bankoutput.txt";
string infilename  = "bankinput.txt";
ofstream outfile(outfilename);

vector<string> ExtractLines(string filename)
{
    // This function extracts all the lines from Input File, each line is then parsed to input array
    vector<string> lines;
    string line;

    ifstream input_file(filename);

    while (getline(input_file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

vector<string> ParseLine(string str)
{
    // This function is applied on a line of input file and it parses the line to 4 fields which are then used
    // for Account object instantiation and Withdrawal & Deposit functionalities.
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
                   vector<string> &inputs)
{   // This function creates an object of class Account and adds it to Accounts vector 
    // using the input array parsed beforehand. 

    Account a1(inputs);
    acc_array.push_back(a1);
}

void setAccountstatuses(vector<Account> &acc_vect)
{   // Sets the Account status to Active or Dormant based on their Balance if >= 5000 or not
    for (int acc_vect_dummy = 0; acc_vect_dummy < acc_vect.size(); acc_vect_dummy++)
    {
        if (acc_vect[acc_vect_dummy].netBalance < 5000)
        {
            acc_vect[acc_vect_dummy].status = "Dormant";
        }
        else
        {
            acc_vect[acc_vect_dummy].status = "Active";
        }
    }
}

void WriteAccountFile(Account acc)
{   
    // Performs Write Operation the output file
    string filename = "bankoutput.txt";
    fstream file;
    file.open(filename);

    outfile << "Account Title: " << acc.namewithoutdash() << endl
            << "Account Code: " << acc.code << endl
            << "Initial Balance: " << acc.initBalance << endl
            << "Available Balance: " << acc.netBalance << endl
            << "Current Status: " << acc.status << endl;

    outfile << "Deposits:" << endl;
    // I am assuming that if an Account has no Deposits then I should write the related text written below
    if(acc.Deposits.size()>0)
    {
        for (int acc_deposit_dummy = 0; acc_deposit_dummy < acc.Deposits.size(); acc_deposit_dummy++)
        {
            outfile << acc_deposit_dummy+1 << ". " << acc.Deposits[acc_deposit_dummy].Amount << " on "
                    << acc.Deposits[acc_deposit_dummy].Date.showslash() << endl;
        }
    }
    else
    {
        outfile << "No Deposits for this Account" << endl;
    }
    
    outfile << "Withdrawals:" << endl;
    // I am assuming that if an Account has no Withdrawals then I should write the related text written below
    if(acc.Withdrawals.size()>0)        
        for (int acc_withdrawal_dummy = 0; acc_withdrawal_dummy < acc.Withdrawals.size(); acc_withdrawal_dummy++)
        {   
            outfile << acc_withdrawal_dummy+1 << ". " << acc.Withdrawals[acc_withdrawal_dummy].Amount << " on "
                    << acc.Withdrawals[acc_withdrawal_dummy].Date.showslash() << " "
                    << acc.Withdrawals[acc_withdrawal_dummy].success << endl;
        }
    else
    {
        outfile << "No Withdrawals for this Account" << endl;
    }
    
    outfile << endl;
}

int main()
{
    vector<Account> Accounts; // Accounts vector to keep track of Accounts
    vector<string>  Lines = ExtractLines(infilename); // Extracts Lines from input file and stores in the vector Lines
    vector<string>  inputs; // vector in which the parsed line will be stored

    for (int i = 0; i < Lines.size(); i++)
    {
        inputs = ParseLine(Lines[i]);

        if (inputs[0] == "Create")
        {
            CreateAccount(Accounts, inputs);
        }
        else
        {
            // Finding which index of Accounts vector is related to the query
            int index;
            for (int finder = 0; finder < Accounts.size(); finder++)
            {
                if (inputs[1] == Accounts[finder].code)
                {
                    index = finder;
                    break;
                }
            }
            // Adds the transaction to corresponding vector
            Accounts[index].add_entry(inputs);
        }
    }

    setAccountstatuses(Accounts);
    // Sets the Account statuses for all elements in Accounts vector

    for (int i = 0; i < Accounts.size(); i++)
    {
        // Writing the Output file for each Account
        WriteAccountFile(Accounts[i]);
    }
    return 0;
}