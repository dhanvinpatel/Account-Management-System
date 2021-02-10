#include "menu.h"
#include "account.h"
#include "bank_account.h"
#include "stock_account.h"
#include "account_settings.h"

int main() {
    
    // Store the account information and the stock that are currently owned.
    vector<Account> accountInfo;

    // Object of the AccountSettings class.
    AccountSettings accountSettings;

    // Object of the BankAccount class.
    BankAccount bankAccount;

    // Object of the StockAccount class.
    StockAccount stockAccount;

    int mainMenuInput = 0;

    while(mainMenuInput != 4)
    {
        mainMenu(&mainMenuInput);
        switch (mainMenuInput) 
        {
            // Account settings.
            case 1:
            {
                int settingsMenuInput = 0;
                while (settingsMenuInput != 5)
                {
                    accountSettingsMenu(&settingsMenuInput);
                    switch (settingsMenuInput)
                    {
                        case 1:
                            accountSettings.createAccount(accountInfo);
                            break;
                        case 2:
                            accountSettings.closeAccount(accountInfo);
                            break;
                        case 3:
                            accountSettings.activeDeactive(accountInfo);
                            break;
                        case 4:
                            accountSettings.printAccount(accountInfo);
                            break;
                        case 5:
                            break;
                        default:
                            cout << "\nWrong selection. Try Again!" << endl;
                    }
                }
                
            }
            break;

            // Stock portfolio account.
            case 2:
            {
                int stockMenuInput = 0;
                while (stockMenuInput != 6) 
                {
                    stockAccountMenu(&stockMenuInput);
                    switch (stockMenuInput) 
                    {
                        case 1:
                            stockAccount.stockPrice();
                            break;
                        case 2:
                            stockAccount.buyStock(accountInfo);
                            break;
                        case 3:
                            stockAccount.sellStock(accountInfo);
                            break;
                        case 4:
                            stockAccount.currentPortfolio(accountInfo);
                            break;
                        case 5:
                            stockAccount.stockTransactionHistory();
                            break;
                        case 6:
                            break;
                        default:
                            cout << "\nWrong selection. Try Again!" << endl;
                    }
                }
            }
            break;

            // Bank account.
            case 3:
            {
                int bankMenuInput = 0;
                while (bankMenuInput != 6) 
                {
                    bankAccountMenu(&bankMenuInput);
                    switch (bankMenuInput)
                    {
                        case 1:
                            bankAccount.accountBalance(accountInfo);
                            break;
                        case 2:
                            bankAccount.depositAccount(accountInfo);
                            break;
                        case 3:
                            bankAccount.withdrawAccount(accountInfo);
                            break;
                        case 4:
                            bankAccount.transferAmount(accountInfo);
                            break;
                        case 5:
                            bankAccount.bankTransactionHistory();
                            break;
                        case 6:
                            break;
                        default:
                            cout << "\nWrong selection. Try Again!" << endl;
                    }
                }
            }
            break;

            // Exit.
            case 4:
                cout << "\nExiting the Account Management System.\n" << endl;
                break;
            default:
                cout << "\nWrong selection. Try Again!" << endl;
                break;
        }
    }
    return 0;
}