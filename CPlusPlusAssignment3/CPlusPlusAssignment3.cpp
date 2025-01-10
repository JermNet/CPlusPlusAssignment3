#include <iostream>
#include "accountmanager.cpp"
using namespace std;

void start(AccountManager, int, string, string, double);
void login(AccountManager, int, string, string, double);
void createAccount(AccountManager, int, string, string, double);
void printMainMenu(AccountManager, int, string, double);
void printIntroMenu(AccountManager, int, string, string, double);


int main() {
    // Create the account manager
    AccountManager accountManager;
    // Int used to decide what the user wants to do
    int action = 0;
    // Strings for id passwords before they're saved
    string userId, password;
    // Double for amount
    double amount = 0;

    // Call the start function to go through the menus
    start(accountManager, action, userId, password, amount);
    return 0;
}

// Simply adds an extra piece of text prompting the user to enter one of the options and then call the printIntroMenu function
void start(AccountManager accountManager, int action, string userId, string password, double amount) {
    cout << "Please select from from one of the options: " << endl;
    printIntroMenu(accountManager, action, userId, password, amount);
}

// Prints the menu for letting the user login, create an account, and exit. The first two call their respective functions, the third returns to start(),
// which has nothing left to do, so returns to main, which then returns 0, ending the program
void printIntroMenu(AccountManager accountManager, int action, string userId, string password, double amount) {
    while (true) {
        cout << "What would you like to do?" << endl << "[1] Login" << endl << "[2] Create Account" << endl << "[3] Exit" << endl;
        cin >> action;
        if (action == 1) {
            login(accountManager, action, userId, password, amount);
        }
        else if (action == 2) {
            createAccount(accountManager, action, userId, password, amount);
        }
        else if (action == 3) {
            return;
        }
        else {
            cout << "That is not a valid option." << endl;
        }
    }
}

// Asks the user to log in, if the account doesn't exist, text is printed letting the user know, and then ends the function, going back to printIntroMenu()
// If the account does exits, the printMainMenu function is called.
void login(AccountManager accountManager, int action, string userId, string password, double amount) {
    cout << "Please enter your user id: " << endl;
    cin >> userId;
    cout << "Please enter your password: " << endl;
    cin >> password;
    if (accountManager.findAccountByIdAndPassword(userId, password) == nullptr) {
        cout << "That account does not exist, please make an account." << endl;
    }
    else {
        printMainMenu(accountManager, action, userId, amount);
    }
}

// If an account exists, the function exits, and it's back to the printIntroMenu() function.
// If an account doesn't exist, it's created, and then it's back to the printIntroMenu() by calling it to make sure the account exists in the current instance
void createAccount(AccountManager accountManager, int action, string userId, string password, double amount) {
    cout << "Please enter a user id: " << endl;
    cin >> userId;
    cout << "Please enter a password: " << endl;
    cin >> password;
    if (!accountManager.addAccount(userId, password)) {
        cout << "That account already exists, please change your username to a unique one." << endl;
    }
    else {
        cout << "Account added successfully!" << endl;
        printIntroMenu(accountManager, action, userId, password, amount);
    }
}

// Prints the main menu, asking the user what they want to do now that they're logged in
void printMainMenu(AccountManager accountManager, int action, string userId, double amount) {
    cout << "You have been logged in!" << endl;
    while (true) {
        cout << "What would you like to do?" << endl << "[1] Deposit" << endl << "[2] Withdraw" << endl << "[3] Request Balance" << endl << "[4] Logout" << endl;
        cin >> action;
        if (action == 1) {
            cout << "How much to deposit?" << endl;
            cin >> amount;
            accountManager.deposit(userId, amount);
            cout << "Your account has been deposited $" << amount << "!" << endl;
        }
        else if (action == 2) {
            cout << "How much to withdraw?" << endl;
            cin >> amount;
            if (accountManager.withdraw(userId, amount)) {
                cout << "Your account has been withdrawn $" << amount << "!" << endl;
            }
            else {
                cout << "Your account does not have enough money to withdraw $" << amount << "!" << endl;
            }
        }
        else if (action == 3) {
            cout << "You have $" << accountManager.getBalance(userId) << "!" << endl;
        }
        else if (action == 4) {
            cout << "You have been logged out!" << endl;
            break;
        }
        else {
            cout << "That is not a valid option." << endl;
        }
    }
}




