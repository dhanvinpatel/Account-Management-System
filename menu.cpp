#include "menu.h"

Account account;

/**
 * Display the Account Management System main menu options.
 * @param mainMenuChoice    is the address of the mainMenuInput.
 */
void mainMenu(int *mainMenuChoice)
{
    int select;
    string option;
    cout << "\nWelcome to the Account Management System." << endl;
    cout << "\nPlease select an account or access settings." << endl;
    cout << "\t1. Account Settings\n"
         << "\t2. Stock Account\n"
         << "\t3. Bank Account\n"
         << "\t4. Exit" << endl;
    cout << "Selection: ";
    cin >> option;
    
    // Validate the main menu selection.
    select = stoi(account.validInput(option));

    *mainMenuChoice = select;
}

/**
 * Display the account settings menu options.
 * @param settingsMenuChoice    is the address of the settingsMenuInput.
 */
void accountSettingsMenu(int *settingsMenuChoice) 
{
    int select;
    string option;

    cout << "\nAccount Settings" << endl;
    cout << "\nPlease select an option." << endl;
    cout << "\t1. Create new account\n"
         << "\t2. Close an account\n"
         << "\t3. Activate/Deactivate an account\n"
         << "\t4. Print an account\n"
         << "\t5. Return to main menu" << endl;
    cout << "Selection: ";
    cin >> option;

    // Validate the account settings selection.
    select = stoi(account.validInput(option));

    *settingsMenuChoice = select;
}


/**
 * Display the stock account menu options.
 * @param stockMenuChoice   is the address of the stockMenuInput.
 */
void stockAccountMenu(int *stockMenuChoice)
{
    int select;
    string option;

    cout << "\nStock Account" << endl;
    cout << "\nPlease select an option." << endl;
    cout << "\t1. Display current price for a stock symbol\n"
         << "\t2. Buy stock\n"
         << "\t3. Sell stock\n"
         << "\t4. Display current portfolio\n"
         << "\t5. Display transactions history\n"
         << "\t6. Return to main menu" << endl;
    cout << "Selection: ";
    cin >> option;
    
    // Validate the stock menu selection.
    select = stoi(account.validInput(option));

    *stockMenuChoice = select;
}

/**
 * Display the bank account menu options.
 * @param bankMenuChoice    is the address of the bankMenuInput.
 */
void bankAccountMenu(int *bankMenuChoice)
{
    int select;
    string option;

    cout << "\nBank Account" << endl;
    cout << "\nPlease select an option." << endl;
    cout << "\t1. Display current portfolio\n"
         << "\t2. Deposit to account\n"
         << "\t3. Withdraw from account\n"
         << "\t4. Transfer money\n"
         << "\t5. Display transactions history\n"
         << "\t6. Return to main menu" << endl;
    cout << "Selection: ";
    cin >> option;
    
    // Validate the bank menu selection.
    select = stoi(account.validInput(option));

    *bankMenuChoice = select;
}