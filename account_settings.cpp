#include "account_settings.h"

/**
 * Create a new account.
 * @param accountInfo   contains the account details.
 */
void AccountSettings::createAccount(vector<Account> &accountInfo)
{
    int accountNumber;
    string lastName;
    string firstName;
    double accountBalance;
    string balance;

    // Assign a 4 digit random number to account number.
    accountNumber = randomAccountNumber(accountInfo);
    cout << "\nCreating bank account number " << accountNumber << endl;

    cout << "\nEnter first name: ";
    cin >> firstName;

    cout << "Enter last name: ";
    cin >> lastName;

    cout << "Enter starting balance: ";
    cin >> balance;

    // Validate account balance.
    accountBalance = stod(validInput(balance));

    // Store account details.
    Account newAccountDetails;
    newAccountDetails.setAccountStatus(true);
    newAccountDetails.setAccountNumber(accountNumber);
    newAccountDetails.setBalance(accountBalance);
    newAccountDetails.setLastName(lastName);
    newAccountDetails.setFirstName(firstName);
    accountInfo.push_back(newAccountDetails);

    cout << "\nAccount number " << accountNumber << " has been activated!" << endl;

    // Sort the accounts using account number in ascending order. 
    sortAccounts(accountInfo);
}

/**
 * Close the account.
 * @param accountInfo   contains the account details.
 */ 
void AccountSettings::closeAccount(vector<Account> &accountInfo)
{
    // Check if an account exist.
    if (accountInfo.empty() != 1)
    {
        int accountIndex;
        int accountNumber;
        string accountId;

        cout << "\nEnter the account number to close: ";
        cin >> accountId;

        // Validate the account number.
        accountNumber = stoi(validInput(accountId));

        // Search the account number.
        accountIndex = searchAccountNumber(accountInfo, accountNumber);

        // Check if the account number exist.
        if (accountInfo[accountIndex].getAccountNumber() == accountNumber)
        {
            // Check if the account is active/deactive.
            if (accountInfo[accountIndex].getAccountStatus() == 0)
            {
                cout << "\n---------------------------------------------" << endl;
                cout << "Process cannot be done!"
                        "\nAccount is not active. Activate this account." << endl;
                cout << "---------------------------------------------" << endl;
            }
            else
            { 
                accountInfo.erase(accountInfo.begin() + accountIndex);
                cout << "\nAccount " << accountInfo[accountIndex].getAccountNumber()
                     << " has been closed!" << endl;
            }
        }
        else
        {   
            cout << "\n===========================" << endl;
            cout << "The account does not exist." << endl;
            cout << "===========================" << endl;
        }
    }
    else
    { 
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Cannot perform the action. Create an account first." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
}

/**
 * Activate or deactivate the account.
 * @param accountInfo   contains the account details.
 */ 
void AccountSettings::activeDeactive(vector<Account> &accountInfo)
{
    // Check if an account exist.
    if (accountInfo.empty() != 1)
    {
        int accountIndex;
        int accountNumber;
        bool accountStatus;
        string accountId;

        cout << "\nEnter the account number to activate or deactivate: ";
        cin >> accountId;

        // Validate the account number.
        accountNumber = stoi(validInput(accountId));

        // Search the account number.
        accountIndex = searchAccountNumber(accountInfo, accountNumber);

        // Check if the account number exist.
        if (accountInfo[accountIndex].getAccountNumber() == accountNumber)
        {
            cout << "Enter 1 to activate or 0 to deactivate: ";
            cin >> accountStatus;

            // Check the account status along with the requested status.
            if (accountInfo[accountIndex].getAccountStatus() == 1 && accountStatus == 1)
            {
                cout << "\nAccount " << accountInfo[accountIndex].getAccountNumber()
                     << " is already active." << endl;
            }
            else if (accountInfo[accountIndex].getAccountStatus() == 0 && accountStatus == 0)
            {
                cout << "\nAccount " << accountInfo[accountIndex].getAccountNumber()
                     << " is already deactive." << endl;
            }
            else if (accountInfo[accountIndex].getAccountStatus() == 1 && accountStatus == 0)
            {
                accountInfo[accountIndex].setAccountStatus(accountStatus);
                cout << "\nAccount " << accountInfo[accountIndex].getAccountNumber()
                     << " has been deactivated!" << endl;
            }
            else
            {
                accountInfo[accountIndex].setAccountStatus(accountStatus);
                cout << "\nAccount " << accountInfo[accountIndex].getAccountNumber()
                     << " has been activated!" << endl;   
            }
        }
        else
        { 
            cout << "\n===========================" << endl;
            cout << "The account does not exist." << endl;
            cout << "===========================" << endl; 
        }
    }
    else
    {   
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Cannot perform the action. Create an account first." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
}

/**
 * Print the details of the account.
 * @param accountInfo   contains the account details.
 */ 
void AccountSettings::printAccount(vector<Account> &accountInfo)
{
    // Check if an account exist.
    if (accountInfo.empty() != 1)
    {
        int accountIndex;
        int accountNumber;
        string accountId;

        cout << "\nEnter the account number to print: ";
        cin >> accountId;

        // Validate the account number.
        accountNumber = stoi(validInput(accountId));

        // Search the account number.
        accountIndex = searchAccountNumber(accountInfo, accountNumber);
        
        // Check if the account exist.
        if (accountInfo[accountIndex].getAccountNumber() == accountNumber)
        {
            string accountStatus;

            if (accountInfo[accountIndex].getAccountStatus() == 0)
            { accountStatus = "Deactive"; }
            else
            { accountStatus = "Active"; }
            
            cout << "\n=================================================================================" << endl;
            cout << "Account Details" << endl;
            cout << "=================================================================================" << endl;

            cout << setw(10) << left << "Number" << setw(5) << " "
                 << setw(15) << left << "Last Name" << setw(5) << " "
                 << setw(15) << left << "First Name" << setw(5) << " "
                 << setw(13) << left << "Balance" << setw(5) << " " 
                 << setw(8)  << left << "Status" << endl;

            cout << setw(10) << left << accountInfo[accountIndex].getAccountNumber() << setw(5) << " "
                 << setw(15) << left << accountInfo[accountIndex].getLastName() << setw(5) << " "
                 << setw(15) << left << accountInfo[accountIndex].getFirstName() << setw(5) << " "
                 << "$" << setw(12) << left << accountInfo[accountIndex].getBalance() << setw(5) << " "
                 << setw(8) << left << accountStatus << endl;
        }
        else
        { 
            cout << "\n===========================" << endl;
            cout << "The account does not exist." << endl;
            cout << "===========================" << endl;
        }
    }
    else
    { 
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Cannot perform the action. Create an account first." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
}

/**
 * Generate a 4 digit random number between 1000 and 9999.
 * Verify if the number has already been created.
 * @param accountInfo   contains the account details.
 * @return int          a 4 digit random number.
 */
int AccountSettings::randomAccountNumber(vector<Account> &accountInfo)
{   
    int newAccountNumber;
    int accountIndex;

    srand(time(NULL));

    // Generate a random number.
    int randomNumber = 1000 + rand() % 9000;
    
    // Search for the account number.
    accountIndex = searchAccountNumber(accountInfo, randomNumber);   

    // Assign the random number or generate new random number.
    if (accountIndex != -1) 
    { newAccountNumber = randomAccountNumber(accountInfo); } 
    else 
    { newAccountNumber = randomNumber; }
    
    return newAccountNumber;
}

/**
 * Sort the accounts by account number in ascending order.
 * @param accountInfo   contains the account details.
 */ 
void AccountSettings::sortAccounts(vector<Account> &accountInfo)
{
    Account temporaryAccount;
    
    // Goes through all the accounts.
    for (unsigned int i = 0; i < accountInfo.size()-1; i++)
    {
        for (unsigned int j = i+1; j < accountInfo.size(); j++)
        {
            // Compare the current account number with the next account number.
            if (accountInfo[i].getAccountNumber() > accountInfo[j].getAccountNumber())
            {
                temporaryAccount = accountInfo[i];
                accountInfo[i] = accountInfo[j];
                accountInfo[j] = temporaryAccount;
            }
        }
    }
}