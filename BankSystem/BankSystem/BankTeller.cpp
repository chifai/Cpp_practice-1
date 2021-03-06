#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;
#include "BankSystem.h"
#include "BankTeller.h"
void BankTeller::executeBankService()
{
    char choiceChar;
    int choiceNum;

    Bank bank;
    Account acc;
    string firstName, lastName, accName, password;
    int accNumber;
    float balance, amount;
    char ans; // confirm to close account

    // home page: quit if user keys in Opt_Quit
    cout << "/// BANKING SYSTEM ///\n";
    do
    {
        cout << "\nSelect one option below: \n";
        cout << "1) Open an account\n";
        cout << "2) Login\n";
        cout << "0) Quit\n\n";
        cout << "Enter your option: \n";
        cin >> choiceChar;
        choiceNum = (int)(choiceChar - '0');
        switch (choiceNum)
        {
        case Opt_OpenAccount: // Open an account
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;

            accName = askNewAccountName(bank);

            cout << "Enter your password: ";
            cin >> password;
            cout << "Enter initial balance: ";
            cin >> balance;
            acc = bank.OpenAccount(firstName, lastName, accName, password, balance);
            cout << "\nAccount is created." << endl;
            cout << acc << endl;
            break;

        case Opt_login:
            cout << "Enter your account name: ";
            cin >> accName;
            cout << "Enter your password: ";
            cin >> password;
            if (bank.login(accName, password) == true)
                runAccountPage(bank);
            else
                cout << "Invalid account or password." << endl;
            break;

        case Opt_Quit:
            break;

        default:
            cout << "\nPlease enter a correct choice! " << endl;
            break;
        }
    } while (choiceNum != Opt_Quit); // repeat the do{} loop as long as the condition is true

    cout << "Bye! See you again." << endl;
}

void BankTeller::respondFlirt()
{
    printf("\nSorry I have a boyfriend\n");
}

string BankTeller::askNewAccountName(const Bank &bank)
{
    string accName;
    bool bDuplicate = false;
    cout << "Enter your account name: ";
    do
    {
        cin >> accName;
        bDuplicate = bank.checkAccDuplicate(accName);   // True: account name duplicated

        if ( bDuplicate == true) {
            cout << "Account name already exists. Enter another name: ";
        }
    } while(bDuplicate == true);

    return accName;
}

void BankTeller::runAccountPage(Bank &bank)
{
    char choiceChar;
    int choiceNum;
    float balance;
    float amount;
    Account acc;
    char ans;
    cout << "...... Login successful." << endl;

    do
    {
        cout << "3) Balance inquiry\n";
        cout << "4) Deposit\n";
        cout << "5) Withdraw\n";
        cout << "6) Close an account\n";
        cout << "0) Quit\n";
        cout << "Enter your option: \n";
        cin >> choiceChar;
        choiceNum = (int)(choiceChar - '0');

        switch (choiceNum)
        {
        case Opt_BalanceInquiry: // Balance inquiry
            bank.BalanceCheck(balance);
            cout << "\n Your balance:" << endl;
            cout << balance << endl;
            break;

        case Opt_Deposit: // Deposit
            cout << "Enter amount of deposit: " << endl;
            cin >> amount;
            bank.Deposit(amount);
            bank.BalanceCheck(balance);
            cout << "\n......Deposit successful" << endl;
            cout << "Your balance:" << endl;
            cout << balance << endl;
            break;

        case Opt_Withdraw: // Withdraw
            cout << "Enter amount of withdrawl: " << endl;
            cin >> amount;
            bank.Withdraw(amount);
            bank.BalanceCheck(balance);
            cout << "\n......Withdraw successful" << endl;
            cout << "\nYour balance:" << endl;
            cout << balance << endl;
            break;

        case Opt_CloseAccount: // Close an account
            cout << "\nYour account details:" << endl;
            bank.GetAccount(acc);
            cout << acc << endl;
            cout << "Are you sure you want to close this account? (Y/N)" << endl;
            cin >> ans;
            if (ans == 'Y' || ans == 'y')
            {
                bank.CloseAccount();
                cout << " --- account deleted ---" << endl;
            }
            else
                cout << " --- cancelled ---" << endl;
            break;
        }
    } while (choiceNum != Opt_Quit);
}