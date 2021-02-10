# **Account Management System**

Simple banking and stock system which allows a banker to manage different bank accounts using the C++ class features. A banker can perform various actions on an account by navigating to either ***Account Settings***, ***Stock Account***, or ***Bank Account***.

<img width="300" alt="main" src="https://user-images.githubusercontent.com/78669309/107450238-e6299400-6b12-11eb-8251-e2726c3111e6.PNG">

- ***Account Settings***
    
    The account settings handles the different settings associated with an account. In the account settings a banker can perform various actions such as creating a new account, closing an account, activating or deactivating an account, and printing an account details.
    
    <img width="300" alt="settings" src="https://user-images.githubusercontent.com/78669309/107450290-fe99ae80-6b12-11eb-8966-5062aad7847b.PNG">

- ***Stock Account***

    The stock account manages the stock portfolio of an account. In the stock account a banker can perform various actions such as displaying the current price for a stock symbol, purchasing a stock, selling a stock, displaying the current portfolio, and displaying the transactions history of all the accounts while saving it in *stock_transaction_history.txt* file. The stock information is retrieved from the *stock1.txt*, *stock2.txt*, *stock3.txt*, and *stock4.txt* files for all the transactions. When a transaction is initiated, a stock file is randomly selected to give a current price of the stock symbol.

    <img width="300" alt="stock" src="https://user-images.githubusercontent.com/78669309/107450313-06f1e980-6b13-11eb-8f6f-9558e69d68d1.PNG">

- ***Bank Account***

    The bank account manages the bank account. A banker can perform different actions in the bank account such as displaying current portfolio of an account, depositing money to an account, withdrawing money from an account, transferring money from one account to another, and displaying the transactions history of all the accounts while saving it in *bank_transaction_history.txt* file.

    <img width="300" alt="bank" src="https://user-images.githubusercontent.com/78669309/107450336-107b5180-6b13-11eb-85c6-164163cd405a.PNG">

## **Usage**
To get a copy of the project and get it running on your local machine either download or clone the repository.

### **Installation**

**Windows (Windows PowerShell)**

Install C++ compiler in Windows. In *terminal* locate to the location where the program is installed and execute the command in the terminal to run the program.

```bash
if ($?) { g++ main.cpp menu.cpp account_settings.cpp account.cpp bank_account.cpp stock_account.cpp -o account_system } ; if ($?) { .\account_system }
```

**Linux**

Install C++ compiler through the terminal.

```bash
sudo apt-get install g++
```
Locate to the location where the program is installed and execute the command in the terminal to run the program.
```bash
make
./account_system
```

### **Clean Build Files**

**Windows (Windows PowerShell)**

Remove the program build files by locating the location of the program in the **terminal** and executing the command.

```bash
rm .\account_system.exe
```

**Linux**

Locate to the location of the program in the **terminal** and execute the command to remove the program build files.
```bash
make clean
```
