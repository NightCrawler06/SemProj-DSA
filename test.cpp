#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Customer {
    string name;
    double amount;
    bool isLoanPaid;
};

vector<Customer> records;

void insertLoan() {
    Customer customer;
    cout << "Enter Customer Name: ";
    getline(cin, customer.name);

    cout << "Enter Loan Amount: ";
    cin >> customer.amount;
    cin.ignore(); // clear newline

    customer.isLoanPaid = false;

    records.push_back(customer);
    cout << "Loan added successfully.\n";
}

void deleteLoan() {
    string name;
    cout << "Enter Customer Name to Delete: ";
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < records.size(); i++) {
        if (records[i].name == name) {
            // Shift all elements to the left
            for (int j = i; j < records.size() - 1; j++) {
                records[j] = records[j + 1];
            }
            records.pop_back(); // remove last element
            found = true;
            cout << "Loan deleted.\n";
            break;
        }
    }

    if (!found) {
        cout << "Customer not found.\n";
    }
}

void searchLoan() {
    string name;
    cout << "Enter Customer Name to Search: ";
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < records.size(); i++) {
        if (records[i].name == name) {
            cout << "Customer: " << records[i].name << "\n";
            cout << "Loan Amount: " << records[i].amount << "\n";
            cout << "Status: " << (records[i].isLoanPaid ? "Paid" : "Unpaid") << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer not found.\n";
    }
}

void showAllLoans() {
    if (records.size() == 0) {
        cout << "No loans available.\n";
        return;
    }

    for (int i = 0; i < records.size(); i++) {
        cout << "Customer: " << records[i].name
             << " | Amount: " << records[i].amount
             << " | Status: " << (records[i].isLoanPaid ? "Paid" : "Unpaid") << "\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- Loan Menu ---\n";
        cout << "1. Insert Loan\n";
        cout << "2. Delete Loan\n";
        cout << "3. Search Loan\n";
        cout << "4. Show All Loans\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline after number

        if (choice == 1) {
            insertLoan();
        } else if (choice == 2) {
            deleteLoan();
        } else if (choice == 3) {
            searchLoan();
        } else if (choice == 4) {
            showAllLoans();
        } else if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
