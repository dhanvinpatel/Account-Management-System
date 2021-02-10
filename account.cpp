#include "account.h"

Account::Account(){}

/**
 * Set the account activation status.
 * @param status    is the account activation status.
 */
void Account::setAccountStatus(bool status)
{
    this->status = status;
}

/**
 * Get the account activation status.
 * @return bool     the account status.
 */
bool Account::getAccountStatus() const
{
    return status;
}

/**
 * Set the account number.
 * @param accountNumber     is the account number.
 */
void Account::setAccountNumber(int accountNumber)
{
    this->accountNumber = accountNumber;
}

/**
 * Get the account number.
 * @return int      the account number.
 */
int Account::getAccountNumber() const
{
    return accountNumber;
}

/**
 * Set the account balance.
 * @param balance       is the account balance.
 */
void Account::setBalance(double balance)
{
    this->balance = balance;
}

/**
 * Get the account balance.
 * @return double       the account balance.
 */
double Account::getBalance() const
{
    return balance;
}

/**
 * Set the account last name.
 * @param lastName      is the account last name.
 */
void Account::setLastName(string lastName)
{
    this->lastName = lastName;
}

/**
 * Get the account last name.
 * @return string       the account last name.
 */
string Account::getLastName() const
{
    return lastName;
}

/**
 * Set the account first name.
 * @param firstName     is the account first name.
 */
void Account::setFirstName(string firstName)
{
    this->firstName = firstName;
}

/**
 * Get the account first name.
 * @return string       the account first name.
 */
string Account::getFirstName() const
{
    return firstName;
}

/**
 * Search the account number.
 * @param accountInfo   contains the details of the account.
 * @param accoutNumber  is the account number of the account.
 * @return int          the index of the account if present or -1 if not present.
 */
int Account::searchAccountNumber(vector<Account> &accountInfo, int accountNumber)
{
    int start = 0;
    int end = accountInfo.size() - 1;
    while (start <= end)
    {
        int mid = (start + end)/2;
        
        if (accountInfo[mid].getAccountNumber() == accountNumber)
        { 
            return mid;
        }
        else if (accountInfo[mid].getAccountNumber() < accountNumber)
        { 
            start = mid + 1; 
        }
        else
        { 
            end = mid - 1;
        }
    }
    return -1;
}

/**
 * Validate a number.
 * @param inputValue    is the number.
 * @return string       the validated number.
 */
string Account::validInput(string inputValue) 
{
    string correctInput;
    
    // Check for string and negative numbers.
    if (inputValue[0] == '-')
    {
        cout << "\nInvalid input!" << endl;
        cout << "Enter a positive number: ";
        cin >> inputValue;
        correctInput = validInput(inputValue);
    }
    else
    {
        int j = 0;
        int check = 0;
        string numbers = ".0123456789";

        while (inputValue[j] != 0)
        {
            for (int i = 0; i < numbers.length(); i++)
            {
                if (inputValue[j] == numbers[i])
                {
                    check++;
                    break;
                }
            }
            j++;
        }

        if (j == check)
        { correctInput = inputValue; }
        else
        {
            cout << "\nInvalid input!" << endl;
            cout << "Enter a valid number: ";
            cin >> inputValue;
            correctInput = validInput(inputValue);
        }
    }
    return correctInput;
}