#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;
#include "BankSystem.h"

int Account::nextAccNumber = 0; // Scope resolution

Account::Account(string firstName, string lastName, string accName, string password, float balance)
{
    nextAccNumber++;
    this->accNumber = nextAccNumber;
    this->firstName = firstName;
    this->lastName = lastName;
    this->accName = accName;
    this->password = password;
    this->balance = balance;
}

void Account::Deposit(float amount)
{
    balance += amount;
}

void Account::Withdraw(float amount)
{
    if (balance < amount) {
        cout << "Insufficient balance!" << endl;
        throw InsufficientBalance(); 
    }
    balance -= amount;
}

void Account::setLastAccountNumber(int accNumber)
{
    nextAccNumber = accNumber;
}

int Account::getLastAccountNumber()
{
    return nextAccNumber;
}

ofstream& operator << (ofstream& ofs, Account& acc)
{
    ofs << acc.accNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.accName << endl;
    ofs << acc.password << endl;
    ofs << acc.balance << endl;
    return ofs;
}

ifstream& operator >> (ifstream& ifs, Account& acc)
{
    ifs >> acc.accNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.accName;
    ifs >> acc.password;
    ifs >> acc.balance;
    return ifs;
}

ostream& operator << (ostream& os, Account& acc)    // similart to std::cout
{
    os << "Account number: " << acc.getAccNumber() << endl;
    os << "First Name: " << acc.getFirstName() << endl;
    os << "Last Name: " << acc.getLastName() << endl;
    os << "Balance: " << acc.getBalance() << endl;
    return os;
}

Bank::Bank() {
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if (!infile) 
    {
        cout << "File not found!" << endl;
        return;
    }
    while(!infile.eof())
    { 
        infile >> account;
        accounts.insert(pair<int, Account>(account.getAccNumber(), account));
    }
    Account::setLastAccountNumber(account.getAccNumber());

    infile.close();
}

Account Bank::OpenAccount(string firstName, string lastName, string accName, string password, float balance) {
    
    ofstream outfile;
    Account account(firstName, lastName, accName, password, balance);
    accounts.insert(pair<int, Account>(account.getAccNumber(), account));

    outfile.open("Bank.data", ios::trunc);
    
    map<int, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();

    return account;
}

bool Bank::checkAccDuplicate(string accName) {

    map<int, Account>::iterator itr;
    Account currentAccount;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        currentAccount = itr->second;
        if (currentAccount.getAccName() == accName) return true;
    }
    return false;
}

bool Bank::login(string accName, string password)
{
    map<int, Account>::iterator itr;
    Account currentAccount;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        currentAccount = itr->second;
        if (currentAccount.checkAccNameAndPassword(accName, password) == true) {
            // if matched, record the login account number and return true
            this->loginAccNumber = itr->first;
            return true;
        }
    }

    // if login failed, assign the loginAccNumber as invalid
    this->loginAccNumber = INVALID_LOGINACCNUM;
    return false;
}

// assign balance to argument, return false if not logged in
bool Bank::BalanceCheck(float &balance) {
    if (loginAccNumber == INVALID_LOGINACCNUM ) return false;

    map<int, Account>::iterator itr = accounts.find(loginAccNumber);
    balance = itr->second.getBalance();

    return true;
}

bool Bank::Deposit(float amount) {
    if (loginAccNumber == INVALID_LOGINACCNUM ) return false;

    map<int, Account>::iterator itr = accounts.find(loginAccNumber);
    itr->second.Deposit(amount);

    return true;
}

bool Bank::Withdraw(float amount) {
    if (loginAccNumber == INVALID_LOGINACCNUM ) return false;

    map<int, Account>::iterator itr = accounts.find(loginAccNumber);
    itr->second.Withdraw(amount);

    return true;

}

bool Bank::CloseAccount() {
    if (loginAccNumber == INVALID_LOGINACCNUM ) return false;

    map<int, Account>::iterator itr = accounts.find(loginAccNumber);
    accounts.erase(loginAccNumber);

    return true;
}

bool Bank::GetAccount(Account &account)
{
    if (loginAccNumber == INVALID_LOGINACCNUM ) return false;

    map<int, Account>::iterator itr = accounts.find(loginAccNumber);
    account = itr->second;

    return true;
}

Bank::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);

    map<int, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}