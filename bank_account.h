#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include "account.h"
#include "stock_account.h"

// Store bank account information.
struct BankAcccountInformation
{
    int accountNumber;
    double accountAmount;
    double accountBalance;
    string accountAction;
    string actionHour;
    string actionMinute;
    string actionSecond;
    string actionMonth;
    string actionDay;
    string actionYear;
};

/**
 * Custom class BankAccount manages the bank account.
 */
class BankAccount: public Account {

    public:
        BankAccount():Account(){};
        
        void accountBalance(vector<Account> &accountInfo);
        
        void depositAccount(vector<Account> &accountInfo);
        
        void withdrawAccount(vector<Account> &accountInfo);
        
        void transferAmount(vector<Account> &accounInfo);
        
        void bankTransactionHistory();
};

#endif // BANK_ACCOUNT_H
