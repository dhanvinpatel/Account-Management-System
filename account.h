#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

// Store stock information.
struct StockInformation 
{
    int accountNumber;
    int stockShare;
    double stockPrice;
    double stockTotal;
    string stockAction;
    string stockSymbol;
    string stockCompany;
    string actionHour;
    string actionMinute;
    string actionSecond;
};

/**
 * Custome class Account manages bank account and stock portfolio account.
 */
class Account {

    private:
        bool status;
        int accountNumber;
        double balance;
        string lastName;
        string firstName;

    public:
        Account();

        vector<StockInformation> stockInfo;

        bool getAccountStatus() const;

        void setAccountStatus(bool status);

        int getAccountNumber() const;

        void setAccountNumber(int accountNumber);

        double getBalance() const;

        void setBalance(double balance);

        string getLastName() const;

        void setLastName(string lastName);

        string getFirstName() const;
        
        void setFirstName(string firstName);

        int searchAccountNumber(vector<Account> &accountInfo, int accountNumber);

        string validInput(string inputValue);
};

#endif //ACCOUNT_H