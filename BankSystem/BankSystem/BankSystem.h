#define INVALID_LOGINACCNUM     -1

class InsufficientBalance {};

class Account {

private:
    int accNumber;
    string firstName;
    string lastName;
    string accName;
    string password;
    float balance;
    static int nextAccNumber;   // counter

public:
    // Constructors
    Account(){}
    Account(string firstName, string lastName, string accName, string password, float balance);

    // Accessors
    int getAccNumber() {
        return accNumber;
    }
    string getFirstName() {
        return firstName;
    }
    string getLastName() {
        return lastName;
    }
    string getAccName() {
        return accName;
    }
    float getBalance() {
        return balance;
    }

    // return true if the accname and password are matched
    bool checkAccNameAndPassword(string accName, string password) {
        if (this->accName.compare(accName) != 0) return false;
        if (this->password.compare(password) != 0) return false;

        return true;
    }

    // Member functions
    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(int accNumber);
    static int getLastAccountNumber();

    // Using Friend Function operator overloading
    friend ofstream& operator << (ofstream& ofs, Account& acc);
    friend ifstream& operator >> (ifstream& ifs, Account& acc);
    friend ostream& operator << (ostream& os, Account& acc);
};

class Bank {
private:
    // account list
    map<int, Account> accounts;

    // this is to store the successfull logged in number, -1: not logged in
    int loginAccNumber;

    // currently logged in account
    Account loginAccount;
public:
    Bank();

    // --- Member functions ---

    // open account
    Account OpenAccount(string firstName, string lastName, string accName, string password, float balance);

    // check if accName already exits when opening an account
    bool checkAccDuplicate(string accName);

    // login account by accName and password, return true if successful
    bool login(string accName, string password);

    // assign balance to argument, return false if not logged in
    bool BalanceCheck(float &balance);

    // deposit amount to account, return false if not logged in
    bool Deposit(float amount);

    // withdraw amount from account, return false if not logged in
    bool Withdraw(float amount);

    // close account, return false if not logged in
    bool CloseAccount();

    // return current account
    bool GetAccount(Account &account);

    ~Bank();    //destructor
};
