#include "BankSystem.h"

class BankTeller {
public:
    // execute SOP when being asked for bank service
    void executeBankService();

    // response when someone flirts the teller
    void respondFlirt();

private:
    enum EBankServiceOption {
        Opt_OpenAccount = 1,
        Opt_login,
        Opt_BalanceInquiry,
        Opt_Deposit,
        Opt_Withdraw,
        Opt_CloseAccount,
        Opt_Quit
    };
};

void BankTeller::executeBankService()
{
    char choiceChar;
    int choiceNum;

    Bank bank;
    Account acc;
    string firstName, lastName, accName, password;
    int accNumber;
    float balance, amount;
    char ans; // Case 5 confirmation
    
    cout << "/// BANKING SYSTEM ///\n";
    do {
        cout << "\nSelect one option below: \n";
        cout << "1) Open an account\n";
        cout << "2) Login\n";
        cout << "3) Balance inquiry\n";
        cout << "4) Deposit\n";
        cout << "5) Withdraw\n";
        cout << "6) Close an account\n";
        cout << "7) Quit\n\n";
        cout << "Enter your option: \n";
        cin >> choiceChar;
        choiceNum = (int) (choiceChar - '0');
        switch(choiceNum)
        {
        case Opt_OpenAccount:     // Open an account
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter your account name: ";
            cin >> accName;
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
                cout << "Login successful." << endl;
            else
                cout << "Invalid account or password." << endl;
            break;

        case Opt_BalanceInquiry:     // Balance inquiry
            bank.BalanceCheck(balance);
            cout << "\n Your balance:" << endl;
            cout << balance << endl;
            break;

        case Opt_Deposit:     // Deposit
            cout << "Enter amount of deposit: " << endl;
            cin >> amount;
            bank.Deposit(amount);
            bank.BalanceCheck(balance);
            cout << "\n Deposit successful" << endl;
            cout << "Your balance:" << endl;
            cout << balance << endl;
            break;

        case Opt_Withdraw:     // Withdraw
            cout << "Enter amount of withdrawl: " << endl;
            cin >> amount;
            bank.Withdraw(amount);
            bank.BalanceCheck(balance);
            cout << "\n Withdraw successful" << endl;
            cout << "\nYour balance:" << endl;
            cout << balance << endl;
            break;

        case Opt_CloseAccount:     // Close an account
            cout << "\nYour account details:" << endl;
            bank.GetAccount(acc);
            cout << acc << endl;
            cout << "Are you sure you want to close this account? (Y/N)" << endl;
            cin >> ans;
            if (ans == 'Y' || ans == 'y') {
                bank.CloseAccount();
                cout << " --- account deleted ---" << endl;
            }
            else
                cout << " --- cancelled ---" << endl;
            break;

        case Opt_Quit:
            break;

        default:
            cout << "\nPlease enter a correct choice! " << endl;
            break;
        }
    }
    while (choiceNum != Opt_Quit);    // repeat the do{} loop as long as the condition is true

    cout << "Bye! See you again." << endl;
}

void BankTeller::respondFlirt()
{
    printf( "\nSorry I have a boyfriend\n" );
}