#include <string.h>
#include <iostream>
using namespace std;
#include "Date.hpp"
#include <sstream>

Date::Date(string date)
{
    vector<string> dateparse;   // A vector in which day and month will be stored
    stringstream ss(date);      // Turning the string into a stream as required in getline.
    string tok;                 // getline function requirement

    while (getline(ss, tok, '-'))
    {
        dateparse.push_back(tok);
    }
    day   = dateparse[0];
    year  = "21";  // Default Year
    month = "";
    // Trimming the Month text to length = 3 to cater fullnames and halfnames e.g Apr & April
    // Lowering the case to tackle Capitalization in some cases e.g May & may
    for(int monthtrimmer=0; monthtrimmer<3; monthtrimmer++)
    {
        month += tolower(dateparse[1][monthtrimmer]); 
    }
    // Converting Month in Words to Month in Number
    vector<string> Months;
    Months = {"jan", "feb", "mar", "apr", "may", "jun", 
              "jul", "aug", "sep", "oct", "nov", "dec"};
    for (int monthNum = 0; monthNum < Months.size(); monthNum++)
    {
        if(Months[monthNum]==month)
        {
            // Ensuring the Month Num to have two digits. e.g converting 3 to 03
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
{   // Extra
    cout << day << '-' << month << '-' << year;
}

string Date::showslash()
{
    // A Display function with slash as the delimiter, Returns the string to be displayed for write-function faciliation.
    string text = day + '/' + month + '/' + year;
    return text;
}
