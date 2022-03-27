#include <iostream>
using namespace std;

class Date
{
    // The class serves as datatype for storing date and performing related operations
    // including instantiation from string
    string year, month, day;

    public:
    Date(string date);

    void show();

    string showslash();
};
