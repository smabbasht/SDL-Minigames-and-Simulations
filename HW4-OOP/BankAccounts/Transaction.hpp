#include "Date.cpp"

struct Transaction
{
    // The structures serves as the datatype for Withdrawal and Deposit events.
    int Amount;     // Amount Transacted
    Date Date;      // Date of Transaction
    string success; // Applicable for Withdrawals
};
