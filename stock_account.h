#ifndef STOCK_ACCOUNT_H
#define STOCK_ACCOUNT_H

#include "account.h"

/**
 * Custom class StockAccount manages the stock portfolio.
 */
class StockAccount: public Account {

    public:
        StockAccount():Account(){};

        void stockPrice();
        
        void buyStock(vector<Account> &accountInfo);
        
        void sellStock(vector<Account> &accountInfo);
        
        void currentPortfolio(vector<Account> &accountInfo);
        
        void stockTransactionHistory();
        
        void sortStocks(vector<StockInformation> &stockInfo);
        
        int checkStockSymbol(vector<StockInformation> &stockInfo, string stockSymbol);
        
        vector<StockInformation> currentStocksPrice(vector<StockInformation> &stockFileInfo);
};

#endif // STOCK_ACCOUNT_H
