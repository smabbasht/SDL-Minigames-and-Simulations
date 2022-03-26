//#include<fstream>
#include<string.h>
#include<iostream>
using namespace std;

class Date
{
    int year, month, day;
    public:
    Date(string date){
        // Making Character array for applying strtok function
        char date_array[date.length()];
	    for (int i = 0; i < sizeof(date_array); i++) {
		    date_array[i] = date[i];
        // Getting Date & Month and setting Year to 21 as default
        char* day     = strtok (date_array,"-");
        char* month   = strtok (NULL, "-");
        year    = 21;
    }

    void show(){
        cout << day << "-" << month << "-" << year;
    }

    void showwithslash(){
        cout << day << "/" << month << "/" << year;
    }
};
