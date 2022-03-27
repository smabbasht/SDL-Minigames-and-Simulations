#include <string.h>
#include <iostream>
using namespace std;
#include "Date.hpp"
#include <sstream>

Date::Date(string date)
{

    vector<string> dateparse;
    stringstream ss(date); // Turn the string into a stream.
    string tok;

    while (getline(ss, tok, '-'))
    {
        dateparse.push_back(tok);
    }
    day   = dateparse[0];
    year  = "21";
    month = "";
    for(int monthtrimmer=0; monthtrimmer<3; monthtrimmer++)
    {
        month += tolower(dateparse[1][monthtrimmer]); 
    }
    
    vector<string> Months;
    Months = {"jan", "feb", "mar", "apr", "may", "jun"
              "jul", "aug", "sep", "oct", "nov", "dec"};
    for (int monthNum = 0; monthNum < Months.size(); monthNum++)
    {
        if(Months[monthNum]==month)
        {
            if (monthNum<10){
                month = "0"+to_string(monthNum+1);
            }
            else{
                month = to_string(monthNum+1);
            }
            break;
        }
    }
    
}

void Date::show()
{
    cout << day << '-' << month << '-' << year;
}

string Date::showslash()
{
    string text = day + '/' + month + '/' + year;
    return text;
}
