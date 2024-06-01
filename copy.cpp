#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Client {
public:
    struct Account {
        string name;
        string accountNumber;
        string pin;
        double amount;
    };

    vector<Account> accounts;

    int displayChoice() {
        int choice;
        cout << "Enter 1 to create account" << endl;
        cout << "Enter 2 to check balance" << endl;
        cout << "Enter 3 to deposit balance" << endl;
        cout << "Enter 4 to withdraw balance" << endl;
        cout << "Enter 5 to exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    Account inputAccountDetails(bool requireAmount = false) {
        Account account;
        cin.ignore();
        cout << "Enter your name: ";
        getline(cin, account.name);
        cout << "Enter your account number: ";
        getline(cin, account.accountNumber);
        cout << "Enter your pin: ";
        getline(cin, account.pin);
        if (requireAmount) {
            cout << "Enter opening balance amount: ";
            cin >> account.amount;
        }
        return account;
    }

    bool findAccount(const string& name, const string& accountNumber, const string& pin, Account& account) {
        for (const auto& acc : accounts) {
            if (acc.name == name && acc.accountNumber == accountNumber && acc.pin == pin) {
                account = acc;
                return true;
            }
        }
        return false;
    }

    void createAccount() {
        Account newAccount = inputAccountDetails(true);
        accounts.push_back(newAccount);
        saveToFile();
        cout << "Account created successfully" << endl;
    }

    void displayBalance() {
        Account account = inputAccountDetails();
        Account foundAccount;
        if (findAccount(account.name, account.accountNumber, account.pin, foundAccount)) {
            cout << "      Name        |    Account number     |      Balance      " << endl
                 << "--------------------------------------------------------------------\n";
            cout << "    " << foundAccount.name << "            " << foundAccount.accountNumber
                 << "              " << foundAccount.amount << endl;
            cout << "--------------------------------------------------------------------" << endl << endl;
        } else {
            cout << "Account not found" << endl;
        }
    }

    void deposit() {
        Account account = inputAccountDetails();
        Account foundAccount;
        if (findAccount(account.name, account.accountNumber, account.pin, foundAccount)) {
            double depositAmount;
            cout << "Enter amount to deposit: ";
            cin >> depositAmount;
            foundAccount.amount += depositAmount;
            updateAccount(foundAccount);
            cout << "Amount deposited successfully" << endl;
        } else {
            cout << "Account not found" << endl;
        }
    }

    void withdraw() {
        Account account = inputAccountDetails();
        Account foundAccount;
        if (findAccount(account.name, account.accountNumber, account.pin, foundAccount)) {
            double withdrawAmount;
            cout << "Enter amount to withdraw: ";
            cin >> withdrawAmount;
            if (foundAccount.amount >= withdrawAmount) {
                foundAccount.amount -= withdrawAmount;
                updateAccount(foundAccount);
                cout << "Amount withdrawn successfully, thank you!" << endl;
            } else {
                cout << "Insufficient balance" << endl;
            }
        } else {
            cout << "Account not found" << endl;
        }
    }

    void openFile() {
        ifstream file("client.txt");
        if (!file.is_open()) {
            cout << "File not found" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Account account;
            ss >> account.name >> account.accountNumber >> account.pin >> account.amount;
            accounts.push_back(account);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("client.txt", ios::out);
        if (!file.is_open()) {
            cout << "Unable to open file" << endl;
            return;
        }

        for (const auto& account : accounts) {
            file << account.name << " " << account.accountNumber << " " << account.pin << " " << account.amount << endl;
        }
        file.close();
    }

private:
    void updateAccount(const Account& updatedAccount) {
        for (auto& account : accounts) {
            if (account.accountNumber == updatedAccount.accountNumber) {
                account = updatedAccount;
                break;
            }
        }
        saveToFile();
    }
};

int main() {
    Client client;
    client.openFile();

    int choice;
    do {
        choice = client.displayChoice();
        switch (choice) {
            case 1:
                client.createAccount();
                break;
            case 2:
                client.displayBalance();
                break;
            case 3:
                client.deposit();
                break;
            case 4:
                client.withdraw();
                break;
            case 5:
                cout <<endl << "    ---------------------    "<< endl << "Exiting program..." << endl;
                break;
            default:
                cout <<endl << "    ---------------------    "<< endl << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
