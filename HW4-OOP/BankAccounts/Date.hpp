#include<iostream>
using namespace std;

class Date
{
    int year, month, day;
    public:
    Date(string date);

    void show();

    string showslash();
};
