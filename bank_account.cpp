#include "bank_account.h"

// Store the bank account transaction history.
vector<BankAcccountInformation> bankAccountHistory;

// Object of the StockAccount class.
StockAccount newStockAccount;

/**
 * Display the current account balance and the stock portfolio.
 * @param accountInfo   contains the account details.
 */
void BankAccount::accountBalance(vector<Account> &accountInfo)
{
    newStockAccount.currentPortfolio(accountInfo);
}

/**
 * Deposit money to the account.
 * @param accountInfo   contains the account details.
 */
void BankAccount::depositAccount(vector<Account> &accountInfo)
{
    // Check if an account exist.
    if (accountInfo.empty() != 1)
    {
        int accountIndex;
        int accountNumber;
        string accountId;

        cout << "\nEnter the account number: ";
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
                double depositAmount;
                string deposit;

                cout << "Enter amount to be deposit: ";
                cin >> deposit;

                // Validate the deposit amount.
                depositAmount = stod(validInput(deposit));

                cout << "\nDeposit $" << depositAmount << " to account number " 
                     << accountInfo[accountIndex].getAccountNumber() << endl;

                // Update the account balance.
                accountInfo[accountIndex].setBalance(accountInfo[accountIndex].getBalance() + depositAmount);

                // Current time.
                time_t currentTime = time(NULL);
                tm *tmLocal = localtime(&currentTime);

                // Store the deposit history in bank account history.
                BankAcccountInformation depositHistory;
                depositHistory.accountAction = "Deposit";
                depositHistory.accountNumber = accountNumber;
                depositHistory.accountAmount = depositAmount;
                depositHistory.accountBalance = accountInfo[accountIndex].getBalance();
                depositHistory.actionHour = to_string(tmLocal->tm_hour);
                depositHistory.actionMinute = to_string(tmLocal->tm_min);
                depositHistory.actionSecond = to_string(tmLocal->tm_sec);
                depositHistory.actionDay = to_string(tmLocal->tm_mday);
                depositHistory.actionMonth = to_string(tmLocal->tm_mon);
                depositHistory.actionYear = to_string(tmLocal->tm_year + 1900);
                bankAccountHistory.push_back(depositHistory);
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
 * Withdraw money from the account.
 * @param accountInfo   contains the account details.
 */
void BankAccount::withdrawAccount(vector<Account> &accountInfo)
{
    // Check if an account exist.
    if (accountInfo.empty() != 1)
    {
        int accountIndex;
        int accountNumber;
        string accountId;

        cout << "\nEnter the account number: ";
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
                double withdrawAmount;
                string withdraw;

                // Check if account balance is greater than 0.0.
                if (accountInfo[accountIndex].getBalance() > 0)
                {
                    cout << "Enter amount to be withdrawn: ";
                    cin >> withdraw;

                    // Validate the withdraw amount.
                    withdrawAmount = stod(validInput(withdraw));

                    while (accountInfo[accountIndex].getBalance() > 0)
                    {
                        // Check if withdraw amount is less than or equal to account balance.
                        if (withdrawAmount > 0 && withdrawAmount <= accountInfo[accountIndex].getBalance())
                        { break; }
                        else
                        { 
                            cout << "\nAmount is not valid." << endl;
                            cout << "Enter a valid amount: ";
                            cin >> withdraw;
                            
                            // Validate user input for transfer amount.
                            withdrawAmount = stod(validInput(withdraw)); 
                        }
                    }

                    cout << "\nWithdraw $" << withdrawAmount << " from account number " 
                         << accountInfo[accountIndex].getAccountNumber() << endl;

                    // Update the account cash balance.
                    accountInfo[accountIndex].setBalance(accountInfo[accountIndex].getBalance() - withdrawAmount);

                    // Current time.
                    time_t currentTime = time(NULL);
                    tm *tmLocal = localtime(&currentTime);

                    // Store the withdraw history in bank account history.
                    BankAcccountInformation withdrawHistory;
                    withdrawHistory.accountAction = "Withdraw";
                    withdrawHistory.accountNumber = accountNumber;
                    withdrawHistory.accountAmount = withdrawAmount;
                    withdrawHistory.accountBalance = accountInfo[accountIndex].getBalance();
                    withdrawHistory.actionHour = to_string(tmLocal->tm_hour);
                    withdrawHistory.actionMinute = to_string(tmLocal->tm_min);
                    withdrawHistory.actionSecond = to_string(tmLocal->tm_sec);
                    withdrawHistory.actionDay = to_string(tmLocal->tm_mday);
                    withdrawHistory.actionMonth = to_string(tmLocal->tm_mon);
                    withdrawHistory.actionYear = to_string(tmLocal->tm_year + 1900);
                    bankAccountHistory.push_back(withdrawHistory);
                }
                else
                {
                    cout << "\n***********************" << endl;
                    cout << "Account has no balance." << endl;
                    cout << "***********************" << endl;
                }
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
 * Transfer money from one account to another account.
 * @param accountInfo   contains the account details.
 */
void BankAccount::transferAmount(vector<Account> &accountInfo)
{
    // Check if an account exist.
    if (accountInfo.empty() != 1)
    {
        int accountOneIndex;
        int accountTwoIndex;
        int accountNumberOne;
        int accountNumberTwo;
        string numberOne;
        string numberTwo;
        double transferAmount;
        string amount;
        
        cout << "\nEnter account number for the sender: ";
        cin >> numberOne;
        
        // Validate senders account number.
        accountNumberOne = stoi(validInput(numberOne));

        // Search the senders account number.
        accountOneIndex = searchAccountNumber(accountInfo, accountNumberOne);

        // Check if the senders account number exist.
        if (accountInfo[accountOneIndex].getAccountNumber() == accountNumberOne)
        {
            bool senderStatus = true;

            // Check if the senders account is active/deactive.
            if (accountInfo[accountOneIndex].getAccountStatus() == 0)
            {
                senderStatus = false;
                cout << "\n-----------------------------------------------------" << endl;
                cout << "Process cannot be done!"
                        "\nSenders account is not active. Activate this account." << endl;
                cout << "-----------------------------------------------------" << endl;
            }
            else
            {
                cout << "Enter account number for the receiver: ";
                cin >> numberTwo;
                
                // Validate receivers account number.
                accountNumberTwo = stoi(validInput(numberTwo));

                // Search the receivers account number.
                accountTwoIndex = searchAccountNumber(accountInfo, accountNumberTwo);

                // Check if the receivers account number exist.
                if (accountInfo[accountTwoIndex].getAccountNumber() == accountNumberTwo && 
                    accountInfo[accountTwoIndex].getAccountNumber() != accountNumberOne)
                {
                    bool receiverStatus = true;
                    
                    // Check if the receivers account is active/deactive.
                    if (accountInfo[accountTwoIndex].getAccountStatus() == 0)
                    {
                        receiverStatus = false;
                        cout << "\n-------------------------------------------------------" << endl;
                        cout << "Process cannot be done!"
                                "\nReceivers account is not active. Activate this account." << endl;
                        cout << "-------------------------------------------------------" << endl;
                    }

                    // Transfer the amount.
                    if (senderStatus && receiverStatus)
                    {   
                        // Check if account balance is greater than 0.0.
                        if (accountInfo[accountOneIndex].getBalance() > 0)
                        {
                            cout << "Enter amount to be transferred: ";
                            cin >> amount;

                            // Validate transfer amount.
                            transferAmount = stod(validInput(amount));

                            while (accountInfo[accountOneIndex].getBalance() > 0)
                            {
                                // Check if transfer amount is less than or equal to account balance.
                                if (transferAmount > 0 && transferAmount <= accountInfo[accountOneIndex].getBalance())
                                { break; }
                                else
                                { 
                                    cout << "\nAmount is not valid." << endl;
                                    cout << "Enter a valid amount: ";
                                    cin >> amount;
                                    
                                    // Validate user input for transfer amount.
                                    transferAmount = stod(validInput(amount)); 
                                }
                            }
                                                    
                            cout << "\nTransfered $" << transferAmount << " from account number " 
                                << accountInfo[accountOneIndex].getAccountNumber() << " to account number "
                                << accountInfo[accountTwoIndex].getAccountNumber() << endl;

                            // Update the sender and receiver account balance.
                            accountInfo[accountOneIndex].setBalance(accountInfo[accountOneIndex].getBalance() - transferAmount);
                            accountInfo[accountTwoIndex].setBalance(accountInfo[accountTwoIndex].getBalance() + transferAmount);

                            // Current time.
                            time_t currentTime = time(NULL);
                            tm *tmLocal = localtime(&currentTime);

                            // Store the transfer history in bank account history.
                            BankAcccountInformation transferHistory;
                            transferHistory.accountAction = "Transfer";
                            transferHistory.accountNumber = accountNumberOne;
                            transferHistory.accountAmount = transferAmount;
                            transferHistory.accountBalance = accountInfo[accountOneIndex].getBalance();
                            transferHistory.actionHour = to_string(tmLocal->tm_hour);
                            transferHistory.actionMinute = to_string(tmLocal->tm_min);
                            transferHistory.actionSecond = to_string(tmLocal->tm_sec);
                            transferHistory.actionDay = to_string(tmLocal->tm_mday);
                            transferHistory.actionMonth = to_string(tmLocal->tm_mon);
                            transferHistory.actionYear = to_string(tmLocal->tm_year + 1900);
                            bankAccountHistory.push_back(transferHistory);

                            // Store the receive history in bank account history.
                            BankAcccountInformation receiveHistory;
                            receiveHistory.accountAction = "Receive";
                            receiveHistory.accountNumber = accountNumberTwo;
                            receiveHistory.accountAmount = transferAmount;
                            receiveHistory.accountBalance = accountInfo[accountTwoIndex].getBalance();
                            receiveHistory.actionHour = to_string(tmLocal->tm_hour);
                            receiveHistory.actionMinute = to_string(tmLocal->tm_min);
                            receiveHistory.actionSecond = to_string(tmLocal->tm_sec);
                            receiveHistory.actionDay = to_string(tmLocal->tm_mday);
                            receiveHistory.actionMonth = to_string(tmLocal->tm_mon);
                            receiveHistory.actionYear = to_string(tmLocal->tm_year + 1900);
                            bankAccountHistory.push_back(receiveHistory);
                        }
                        else
                        { 
                            cout << "\n***********************" << endl;
                            cout << "Account has no balance." << endl;
                            cout << "***********************" << endl;
                        }
                    }
                }
                else
                { 
                    cout << "\n=================================" << endl;
                    cout << "Receivers account does not exist." << endl;
                    cout << "=================================" << endl;

                }
            }
        }
        else
        { 
            cout << "\n===============================" << endl;
            cout << "Senders account does not exist." << endl;
            cout << "===============================" << endl;

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
 * Display and save the bank account transaction history in a txt file.
 */
void BankAccount::bankTransactionHistory()
{
    // Check if bank account history exist.
   if (bankAccountHistory.empty() != 1) 
   {
       // Open the txt file or create one if it does not exist.
        ofstream bankFile;
        bankFile.open("bank_transaction_history.txt", ios::app);

        // Write the bank account history in a txt file.
        bankFile << setw(15) << left << "Account Number " << setw(5) << " "
                 << setw(10) << left << "Action" << setw(5) << " "
                 << setw(13) << left << "Amount" << setw(5) << " " 
                 << setw(13) << left << "Balance" << setw(5) << " "
                 << setw(10) << left << "Date" << setw(5) << " "
                 << setw(8) << left << "Time" << endl;

        for (unsigned int i = 0; i < bankAccountHistory.size(); i++)
        {
            bankFile << setw(15) << left << bankAccountHistory[i].accountNumber << setw(5) << " "
                        << setw(10) << left << bankAccountHistory[i].accountAction << setw(5) << " "
                        << "$" << setw(12) << left << bankAccountHistory[i].accountAmount << setw(5) << " "
                        << "$" << setw(12) << left << bankAccountHistory[i].accountBalance << setw(5) << " "
                        << bankAccountHistory[i].actionMonth << "/" 
                        << bankAccountHistory[i].actionDay << "/" 
                        << bankAccountHistory[i].actionYear << setw(7) << " "
                        << bankAccountHistory[i].actionHour << ":" 
                        << bankAccountHistory[i].actionMinute << ":" 
                        << bankAccountHistory[i].actionSecond << endl;   
        }
        bankFile << "-----------------------------------------------"
                    "-----------------------------------------------" << endl;
        bankFile << "-----------------------------------------------"
                    "-----------------------------------------------" << endl;

        // Close the txt file.
        bankFile.close();

        // Open the bank transaction history txt file.
        ifstream file;
        file.open("bank_transaction_history.txt");
        string line;

        // Read the bank transaction history from the txt file.
        while (getline(file, line))
        { cout << line << endl; }

        // Close the txt file.
        file.close();
   }
   else
   {
       cout << "\n**********************************" << endl;
       cout << "No transaction has been performed." << endl;
       cout << "**********************************" << endl;
   }
}