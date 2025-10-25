#include <iostream>
 #include <fstream>
 #include <iomanip>
 #include <string>
 #include <limits>
 #include <vector>
 using namespace std;
 struct Account {
    int acc_no;
    string name;
    double deposit;
    char type;
 };
 class BankSystem {
 private:
    vector<Account> accounts;
    Account* findAccount(int acc_no) {
        for (auto &acc : accounts)
            if (acc.acc_no == acc_no)
                return &acc;
        return nullptr;
    }
 public:
    void createAccount() {
        Account acc;
        cout << "\nEnter account number: ";
        cin >> acc.acc_no;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter account holder name: ";
        getline(cin, acc.name);
        cout << "Enter account type (S/C): ";
        cin >> acc.type;
        cout << "Enter initial deposit: ";
        cin >> acc.deposit;
        accounts.push_back(acc);
        cout << "\nAccount created successfully!\n";
    }
    void depositWithdraw(int acc_no, int option) {
        Account *acc = findAccount(acc_no);
        if (!acc) {
            cout << "\nAccount not found!\n";
            return;
        }
        double amt;
        cout << "Enter amount: ";
        cin >> amt;
        if (option == 1)
            acc->deposit += amt;
        else if (option == 2 && acc->deposit >= amt)
            acc->deposit -= amt;
        else
            cout << "\nInsufficient balance!\n";
        cout << "\nTransaction successful!\n";
    }
    void displayAccount(int acc_no) {
        Account *acc = findAccount(acc_no);
        if (acc) {
            cout << "\nAccount Number: " << acc->acc_no;
            cout << "\nAccount Holder Name: " << acc->name;
            cout << "\nType of Account: " << acc->type;
            cout << "\nBalance Amount: " << acc->deposit << endl;
        } else {
            cout << "\nAccount not found!\n";
        }
    }
    void displayAll() {
        cout << "\n\nACCOUNT HOLDER LIST\n";
        cout << "=========================================\n";
        cout << left << setw(10) << "A/C No" << setw(20) << "Name" << setw(10) << "Type" << setw(10) << "Balance" << endl;
        cout << "-----------------------------------------\n";
        for (const auto &acc : accounts) {
            cout << left << setw(10) << acc.acc_no << setw(20) << acc.name << setw(10)
                 << acc.type << setw(10) << acc.deposit << endl;
        }
    }
    void modifyAccount(int acc_no) {
        Account *acc = findAccount(acc_no);
        if (!acc) {
            cout << "\nAccount not found!\n";
            return;
        }
        cout << "\nModify account holder name: ";
        cin.ignore();
        getline(cin, acc->name);
        cout << "Modify type of account: ";
        cin >> acc->type;
        cout << "Modify balance amount: ";
        cin >> acc->deposit;
        cout << "\nAccount updated successfully!\n";
    }
    void deleteAccount(int acc_no) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->acc_no == acc_no) {
                accounts.erase(it);
                cout << "\nAccount deleted successfully!\n";
                return;
            }
        }
        cout << "\nAccount not found!\n";
    }
 };
 int main() {
    BankSystem bank;
    int choice, acc_no;
    do {
        cout << "\n\n===== BANKING SYSTEM MENU =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Amount";
        cout << "\n3. Withdraw Amount";
        cout << "\n4. Balance Enquiry";
        cout << "\n5. All Account Holder List";
        cout << "\n6. Close An Account";
        cout << "\n7. Modify An Account";
        cout << "\n8. Exit";
        cout << "\nSelect Your Option (1-8): ";
        cin >> choice;
        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2:
                cout << "Enter account number: ";
                cin >> acc_no;
                bank.depositWithdraw(acc_no, 1);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> acc_no;
                bank.depositWithdraw(acc_no, 2);
                break;
            case 4:
                cout << "Enter account number: ";
                cin >> acc_no;
                bank.displayAccount(acc_no);
                break;
            case 5:
                bank.displayAll();
                break;
            case 6:
                cout << "Enter account number: ";
                cin >> acc_no;
                bank.deleteAccount(acc_no);
                break;
            case 7:
                cout << "Enter account number: ";
                cin >> acc_no;
                bank.modifyAccount(acc_no);
                break;
            case 8:
                cout << "\nThank you for using Banking System.\n";
                break;
            default:
                cout << "\nInvalid option! Try again.\n";
        }
    } while (choice != 8);
    return 0;
}