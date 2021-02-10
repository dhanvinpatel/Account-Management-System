#include "stock_account.h"

// Store the stock account transaction history.
vector<StockInformation> stockAccountHistory;

/**
 * Randomly select a stock file and retrive information of all the stocks.
 * @param stockFileInfo     will contain information of all the stocks.
 * @return vector           the list of all the stocks in the stock txt file.
 */
vector<StockInformation> StockAccount::currentStocksPrice(vector<StockInformation> &stockFileInfo)
{
    srand(time(NULL));

    // Randomly select a stock file.
    int randomNumber = rand() % 4 + 1;
    string stockFileName = "stock" + to_string(randomNumber) + ".txt";
    string stockFilePath = "C:.\\" + stockFileName;
    
    // Open the stock file.
    ifstream file;
    file.open(stockFilePath);
    string line;

    // Read the stock file.
    while (getline(file, line)) 
    {
        vector<string> tokens;
        string delim = "\t";

        // Read the symbol, company, and price of all the stocks.
        for (int i = 0; i < 3; i++)     // Making 3 tokens.
        {
            if (i == 2)     // Handling newline character.
            {
                line = line.substr(line.rfind(delim) + 1, string::npos);
                tokens.push_back(line);
            }
            tokens.push_back(line.substr(0, line.find(delim)));
            line = line.substr(line.find(delim) + 1, string::npos);
        }

        // Store the symbol, company, and price of all the stocks from the stock file.
        StockInformation currentStock;
        currentStock.stockSymbol = tokens[0];
        currentStock.stockCompany = tokens[1];
        currentStock.stockPrice = stod(tokens[2]);
        stockFileInfo.push_back(currentStock);
    }

    // Close the stock file.
    file.close();

    return (stockFileInfo);
}

/**
 * Display the current price of the stock symbol.
 */
void StockAccount::stockPrice() 
{
    // Retrive information of all the stocks.
    vector<StockInformation> stockFileInfo;
    stockFileInfo = currentStocksPrice(stockFileInfo);

    int stockSymbolIndex;
    string stockSymbol;

    cout << "\nEnter stock symbol for checking price: ";
    cin >> stockSymbol;

    // Check if the stock symbol exist.
    stockSymbolIndex = checkStockSymbol(stockFileInfo, stockSymbol);

    // Display stock details if the stock symbol is found.
    if (stockSymbolIndex != -1 && stockSymbolIndex >= 0)
    {
        // Current time.
        time_t currentTime = time(NULL);
        tm *tmLocal = localtime(&currentTime);

        cout << setw(12) << left << "\nSymbol"  << setw(5) << " "
             << setw(30) << left << "Company" << setw(5) << " " 
             << setw(9) << left << "Price" << setw(5) << " " 
             << setw(8) << left << "Time" << endl;

        cout << setw(11) << left << stockFileInfo[stockSymbolIndex].stockSymbol << setw(5) << " "
             << setw(30) << left << stockFileInfo[stockSymbolIndex].stockCompany << setw(5) << " " 
             << "$" << setw(8) << left << stockFileInfo[stockSymbolIndex].stockPrice << setw(5) << " " 
             << tmLocal->tm_hour << ":" << tmLocal->tm_min << ":" << tmLocal->tm_sec << endl;
    }
    else
    {
        cout << "\n************************" << endl;
        cout << "Stock symbol is invalid." << endl;
        cout << "************************" << endl;
    }
}

/**
 * Purchase a stock.
 * @param accountInfo   contains the account details.
 */
void StockAccount::buyStock(vector<Account> &accountInfo)
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
                // Retrive information of all the stocks.
                vector<StockInformation> stockFileInfo;
                stockFileInfo = currentStocksPrice(stockFileInfo);

                int stockSymbolIndex;
                string stockSymbol;
                int stockShare;
                string share;
                double buyingPrice;
                string price;

                cout << "\nEnter the purchasing stock symbol: ";
                cin >> stockSymbol;

                // Check if the stock symbol exist.
                stockSymbolIndex = checkStockSymbol(stockFileInfo, stockSymbol);

                if(stockSymbolIndex >= 0)
                {
                    cout << "Enter the amount of share to buy: ";
                    cin >> share;

                    // Validate the stock share.
                    stockShare = stoi(validInput(share));

                    cout << "Enter the price willing to pay for each share: ";
                    cin >> price;

                    // Validate the price paying for stock.
                    buyingPrice = stod(validInput(price));

                    double accountBalance = accountInfo[accountIndex].getBalance();
                    double totalAmount = (stockShare*buyingPrice);
                    
                    // Verify account balance and the price willing to pay for each stock.
                    if(accountBalance < totalAmount || buyingPrice < stockFileInfo[stockSymbolIndex].stockPrice)
                    { 
                        cout << "\n***************************" << endl;
                        cout << "Cannot process transaction." << endl;
                        cout << "***************************" << endl;
                    }
                    else
                    {
                        accountBalance -= totalAmount;

                        // Update the account cash balance.
                        accountInfo[accountIndex].setBalance(accountBalance);

                        // Check if the purchasing stock symbol was already purchased before.
                        int stockIndex = checkStockSymbol(accountInfo[accountIndex].stockInfo, stockSymbol);
                        
                        if (stockIndex == -1)
                        {
                            // Store the purchased stock information in stockInfo.
                            StockInformation newStock;
                            newStock.stockSymbol = stockFileInfo[stockSymbolIndex].stockSymbol;
                            newStock.stockCompany = stockFileInfo[stockSymbolIndex].stockCompany;
                            newStock.stockShare = stockShare;
                            newStock.stockPrice = stockFileInfo[stockSymbolIndex].stockPrice;
                            newStock.stockTotal = newStock.stockShare*newStock.stockPrice;
                            accountInfo[accountIndex].stockInfo.push_back(newStock);
                        }
                        else
                        {
                            // Update the stock information if purchasing stock is present in the stockInfo.
                            accountInfo[accountIndex].stockInfo[stockIndex].stockShare += stockShare;
                            accountInfo[accountIndex].stockInfo[stockIndex].stockPrice = stockFileInfo[stockSymbolIndex].stockPrice; 
                            accountInfo[accountIndex].stockInfo[stockIndex].stockTotal = accountInfo[accountIndex].stockInfo[stockIndex].stockShare 
                                                                                        *accountInfo[accountIndex].stockInfo[stockIndex].stockPrice;
                        }
                        
                        cout << "\nTransaction successful!" << endl;

                        // Sort the stock in ascending order.
                        sortStocks(accountInfo[accountIndex].stockInfo);

                        // Current time.
                        time_t currentTime = time(NULL);
                        tm* tmLocal = localtime(&currentTime);

                        // Store the stock purchasing history in the stockAccountInfo.
                        StockInformation stockHistory;
                        stockHistory.stockAction = "Buy";
                        stockHistory.accountNumber = accountInfo[accountIndex].getAccountNumber();
                        stockHistory.stockSymbol = stockFileInfo[stockSymbolIndex].stockSymbol;
                        stockHistory.stockShare = stockShare;
                        stockHistory.stockPrice = stockFileInfo[stockSymbolIndex].stockPrice;
                        stockHistory.actionHour = to_string(tmLocal->tm_hour);
                        stockHistory.actionMinute = to_string(tmLocal->tm_min);
                        stockHistory.actionSecond = to_string(tmLocal->tm_sec);
                        stockAccountHistory.push_back(stockHistory);
                    }
                }
                else
                { 
                    cout << "\n************************" << endl;
                    cout << "Stock symbol is invalid." << endl;
                    cout << "************************" << endl;
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
 * Sell stock from the currently owned stock.
 * @param accountInfo   contains the account details.
 */
void StockAccount::sellStock(vector<Account> &accountInfo)
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
                // Retrive information of all the stocks.
                vector<StockInformation> stockFileInfo;
                stockFileInfo = currentStocksPrice(stockFileInfo);

                int stockSymbolIndex;
                int stockIndex;
                string stockSymbol;
                int stockShare;
                string share;
                double sellingPrice;
                string price;

                cout << "\nEnter the selling stock symbol: ";
                cin >> stockSymbol;
                
                // Check if the stock symbol exist in the currently owned stocks.
                stockIndex = checkStockSymbol(accountInfo[accountIndex].stockInfo, stockSymbol);

                if(stockIndex >= 0)
                {   
                    cout << "Enter the amount of share to sell: ";
                    cin >> share;

                    // Validate the stock share.
                    stockShare = stoi(validInput(share));

                    cout << "Enter the price willing to sell for each share: ";
                    cin >> price;

                    // Validate the price paying for stock.
                    sellingPrice = stod(validInput(price));

                    // Check if the stock symbol exist.
                    stockSymbolIndex = checkStockSymbol(stockFileInfo, stockSymbol);

                    // Verify the price willing to sell for each stock and the stock share.
                    if(sellingPrice > stockFileInfo[stockSymbolIndex].stockPrice || 
                       stockShare > accountInfo[accountIndex].stockInfo[stockIndex].stockShare)
                    {
                        cout << "\n***************************" << endl;
                        cout << "Cannot process transaction." << endl;
                        cout << "***************************" << endl;
                    }
                    else
                    {
                        double cashBalance = accountInfo[accountIndex].getBalance();
                        cashBalance += (stockShare*sellingPrice);

                        // Update the account balance.
                        accountInfo[accountIndex].setBalance(cashBalance);

                        // Update the currently owned stock information.
                        accountInfo[accountIndex].stockInfo[stockIndex].stockShare -= stockShare;
                        accountInfo[accountIndex].stockInfo[stockIndex].stockPrice = stockFileInfo[stockSymbolIndex].stockPrice;
                        accountInfo[accountIndex].stockInfo[stockIndex].stockTotal = accountInfo[accountIndex].stockInfo[stockIndex].stockShare 
                                                                                    *accountInfo[accountIndex].stockInfo[stockIndex].stockPrice;
                        
                        // Remove the stock from currently owned stocks.
                        if (accountInfo[accountIndex].stockInfo[stockIndex].stockShare == 0)
                        {
                            accountInfo[accountIndex].stockInfo.erase(accountInfo[accountIndex].stockInfo.begin() + stockIndex);
                        }

                        cout << "\nTransaction successful!" << endl;

                        // Current time.
                        time_t currentTime = time(NULL);
                        tm* tmLocal = localtime(&currentTime);

                        // Store the stock selling history in the stockAccountInfo.
                        StockInformation stockHistory;
                        stockHistory.stockAction = "Sell";
                        stockHistory.accountNumber = accountNumber;
                        stockHistory.stockSymbol = stockFileInfo[stockSymbolIndex].stockSymbol;
                        stockHistory.stockShare = stockShare;
                        stockHistory.stockPrice = stockFileInfo[stockSymbolIndex].stockPrice;
                        stockHistory.actionHour = to_string(tmLocal->tm_hour);
                        stockHistory.actionMinute = to_string(tmLocal->tm_min);
                        stockHistory.actionSecond = to_string(tmLocal->tm_sec);
                        stockAccountHistory.push_back(stockHistory);
                    }
                }
                else
                {
                    cout << "\n***************************" << endl;
                    cout << "Stock symbol not purchased." << endl;
                    cout << "***************************" << endl;
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
 * Display the current account balance and the stock portfolio.
 * @param accountInfo   contains the account details.
 */
void StockAccount::currentPortfolio(vector<Account> &accountInfo)
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
                double portfolioValue = 0;
                double cashBalance = accountInfo[accountIndex].getBalance();

                cout << "\nCash Balance = $" << cashBalance << endl;
                
                // Check if the account currently owns any stock.
                if (accountInfo[accountIndex].stockInfo.empty() != 1)
                {
                    cout << endl;
                    cout << setw(10) << left << "Number" << setw(5) << " "
                         << setw(10) << left << "Symbol" << setw(5) << " "
                         << setw(30) << left << "Company" << setw(5) << " " 
                         << setw(8) << left << "Number" << setw(5) << " " 
                         << setw(9) << left << "Price" << setw(5) << " "
                         << setw(9) << left << "Total" << endl;

                    for (unsigned int i = 0; i < accountInfo[accountIndex].stockInfo.size(); i++) 
                    {
                        cout << setw(10) << left << accountNumber << setw(5) << " "
                             << setw(10) << left << accountInfo[accountIndex].stockInfo[i].stockSymbol << setw(5) << " "
                             << setw(30) << left << accountInfo[accountIndex].stockInfo[i].stockCompany << setw(5) << " "
                             << setw(8) << left << accountInfo[accountIndex].stockInfo[i].stockShare << setw(5) << " "
                             << "$" << setw(8) << left << accountInfo[accountIndex].stockInfo[i].stockPrice << setw(5) << " "
                             << "$" << setw(8) << left << accountInfo[accountIndex].stockInfo[i].stockTotal << endl;

                        portfolioValue += accountInfo[accountIndex].stockInfo[i].stockTotal;
                    }
                    portfolioValue += cashBalance;
                }
                cout << "\nPortfolio Value: $" << portfolioValue << endl;
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
 * Display the stock transaction history.
 */
void StockAccount::stockTransactionHistory()
{
    if (stockAccountHistory.empty() != 1)
    {
        // Open the txt file or create one if it does not exist.
        ofstream stockFile;
        stockFile.open("stock_transaction_history.txt", ios::app);

        // Write the stock account history in a txt file.
        stockFile << setw(10) << left << "Number " << setw(5) << " "
                  << setw(8) << left << "Action" << setw(5) << " " 
                  << setw(8) << left << "Symbol" << setw(5) << " " 
                  << setw(8) << left << "Shares" << setw(5) << " "
                  << setw(9) << left << "Price" << setw(5) << " "
                  << setw(8) << left << "Time" << endl;

        for (unsigned int i = 0; i < stockAccountHistory.size(); i++)
        {
            stockFile << setw(10) << left << stockAccountHistory[i].accountNumber << setw(5) << " "
                      << setw(8) << left << stockAccountHistory[i].stockAction << setw(5) << " " 
                      << setw(8) << left<< stockAccountHistory[i].stockSymbol << setw(5) << " "
                      << setw(8) << left << stockAccountHistory[i].stockShare << setw(5) << " "
                      << "$" << setw(8) << left << stockAccountHistory[i].stockPrice << setw(5) << " "
                      << stockAccountHistory[i].actionHour << ":" << stockAccountHistory[i].actionMinute << ":" 
                      << stockAccountHistory[i].actionSecond << endl;
        }
        stockFile << "--------------------------------------"
                     "--------------------------------------" << endl;
        stockFile << "--------------------------------------"
                     "--------------------------------------" << endl;
        
        // Close the txt file.
        stockFile.close();

        // Open the stock transaction history txt file.
        ifstream file;
        file.open("stock_transaction_history.txt");
        string line;

        // Read the stock transaction history from the txt file.
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

/**
 * Sort the stock in ascending order by their stock symbol.
 * @param stockDetails  contains the stocks that are currently owned.
 */
void StockAccount::sortStocks(vector<StockInformation> &stockDetails)
{
    StockInformation temporaryStock;

    // Goes through all the stocks.
    for(unsigned int i = 0; i < stockDetails.size()-1; i++)
    {
        for(unsigned int j = i+1; j < stockDetails.size(); j++)
        {
            if (stockDetails[i].stockSymbol > stockDetails[j].stockSymbol)
            {
                temporaryStock = stockDetails[i];
                stockDetails[i] = stockDetails[j];
                stockDetails[j] = temporaryStock;
            }
        }
    }
}

/**
 * Check if the stock symbol exist.
 * @param stockDetails  contains the details of the stock.
 * @param stockSymbol   is the stock symbol.
 * @return int          the index of the stock symbol if present or -1 if not present.
 */
int StockAccount::checkStockSymbol(vector<StockInformation> &stockDetails, string stockSymbol) 
{
    for (unsigned int i = 0; i < stockDetails.size(); i++)
    {
        if (stockDetails[i].stockSymbol == stockSymbol)
        {
            return i;
        }
    }
    return -1;
}