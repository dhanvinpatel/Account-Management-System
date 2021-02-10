#ifndef ACCOUNT_SETTINGS_H
#define ACCOUNT_SETTINGS_H

#include "account.h"

/**
 * Custom class AccountSettings manages the account settings.
 */
class AccountSettings: public Account {
    
    public:
        void createAccount(vector<Account> &accountInfo);

        void closeAccount(vector<Account> &accountInfo);
        
        void activeDeactive(vector<Account> &accountInfo);
        
        void printAccount(vector<Account> &accountInfo);
        
        int randomAccountNumber(vector<Account> &accountInfo);

        void sortAccounts(vector<Account> &accountInfo);
};

#endif // ACCOUNT_SETTINGS_H