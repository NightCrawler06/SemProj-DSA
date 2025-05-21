#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

struct Customer {
    string name;
    double amount;
    bool isLoanPaid;
    string collateralDescription;
    double collateralValue;
};

vector<Customer> records;
queue<Customer> pendingApplications;

string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void insertLoan() {
    Customer customer;
    cout << "Enter Customer Name: ";
    getline(cin, customer.name);

    cout << "Enter Loan Amount (PHP): ";
    cin >> customer.amount;
    cin.ignore();

    cout << "Enter Collateral Description: ";
    getline(cin, customer.collateralDescription);

    cout << "Enter Collateral Estimated Value (PHP): ";
    cin >> customer.collateralValue;
    cin.ignore();

    if (customer.collateralValue <= customer.amount) {
        cout << "Error: Collateral value must be greater than the loan amount.\n";
        return;
    }

    customer.isLoanPaid = false;
    pendingApplications.push(customer);
    cout << "Application submitted for review.\n";
}

void reviewLoans() {
    if (pendingApplications.empty()) {
        cout << "No applications pending review.\n";
        return;
    }

    while (!pendingApplications.empty()) {
        Customer customer = pendingApplications.front();
        pendingApplications.pop();

        cout << "\n--- Review Application ---\n";
        cout << "Customer: " << customer.name << "\n";
        cout << "Loan Amount: PHP " << customer.amount << "\n";
        cout << "Collateral: " << customer.collateralDescription
     << " (PHP " << fixed << setprecision(2) << customer.collateralValue << ")\n";

        cout << "Approve loan? (Y/N): ";
        string input;
        getline(cin, input);

        if (input == "Y" || input == "y") {
            records.push_back(customer);
            cout << "Loan approved and added to records.\n";
        } else {
            cout << "Loan rejected.\n";
        }
    }
}

void markLoanAsPaid() {
    string name;
    cout << "Enter Customer Name to mark as paid: ";
    getline(cin, name);

    for (Customer& c : records) {
        if (c.name == name && !c.isLoanPaid) {
            c.isLoanPaid = true;
            cout << "Loan marked as paid.\n";
            return;
        }
    }

    cout << "Loan not found or already paid.\n";
}

void searchLoan() {
    string name;
    cout << "Enter Customer Name to Search: ";
    getline(cin, name);

    for (const Customer& c : records) {
        if (c.name == name) {
            cout << "Customer: " << c.name << "\n";
            cout << "Loan Amount: PHP " << c.amount << "\n";
            cout << "Collateral: " << c.collateralDescription 
                 << " (PHP " << c.collateralValue << ")\n";
            cout << "Status: " << (c.isLoanPaid ? "Paid" : "Unpaid") << "\n";
            return;
        }
    }

    cout << "Customer not found.\n";
}

void showAllLoans() {
    if (records.empty()) {
        cout << "No Loans Available.\n";
        return;
    }

    for (const Customer& c : records) {
        cout << "Customer: " << c.name
             << " | Amount: PHP " << c.amount
             << " | Collateral: " << c.collateralDescription
             << " (PHP " << c.collateralValue << ")"
             << " | Status: " << (c.isLoanPaid ? "Paid" : "Unpaid") << "\n";
    }
}

void showUnpaidLoans() {
    bool found = false;
    for (const Customer& c : records) {
        if (!c.isLoanPaid) {
            cout << "Customer: " << c.name
                 << " | Amount: PHP " << c.amount
                 << " | Collateral: " << c.collateralDescription << "\n";
            found = true;
        }
    }
    if (!found) cout << "No unpaid loans.\n";
}

void showPaidLoans() {
    bool found = false;
    for (const Customer& c : records) {
        if (c.isLoanPaid) {
            cout << "Customer: " << c.name
                 << " | Amount: PHP " << c.amount
                 << " | Collateral: " << c.collateralDescription << "\n";
            found = true;
        }
    }
    if (!found) cout << "No paid loans yet.\n";
}

void showHelp() {
    cout << "\nAvailable commands:\n";
    cout << "  apply         - Submit a new loan application\n";
    cout << "  review        - Review pending loan applications\n";
    cout << "  paid          - Show paid loans\n";
    cout << "  unpaid        - Show unpaid loans\n";
    cout << "  mark paid     - Mark a loan as paid\n";
    cout << "  search        - Search for a customer\n";
    cout << "  show all      - Show all loans\n";
    cout << "  help          - Show this help menu\n";
    cout << "  exit          - Exit the program\n\n";
}

int main() {
    cout << "Welcome to LoanMate Lite! Type 'help' for a list of commands.\n";
    string input;

    while (true) {
        cout << "\n[LoanMate]> ";
        getline(cin, input);
        string command = toLower(input);

        if (command.find("apply") != string::npos || command.find("borrow") != string::npos) {
            insertLoan();
        } else if (command.find("review") != string::npos) {
            reviewLoans();
        } else if (command.find("unpaid") != string::npos) {
            showUnpaidLoans();
        } else if (command.find("paid") != string::npos && command.find("mark") == string::npos) {
            showPaidLoans();
        } else if (command.find("mark") != string::npos && command.find("paid") != string::npos) {
            markLoanAsPaid();
        } else if (command.find("search") != string::npos) {
            searchLoan();
        } else if (command.find("show all") != string::npos) {
            showAllLoans();
        } else if (command.find("help") != string::npos) {
            showHelp();
        } else if (command.find("exit") != string::npos || command.find("quit") != string::npos) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Unrecognized command. Type 'help' to see valid options.\n";
        }
    }

    return 0;
}
