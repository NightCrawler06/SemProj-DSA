#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int MAX_CUSTOMERS = 17;

struct Customer {
    string name;
    double loanAmount;
    double interestRate;
    int months;
    bool isPaid;
    string collateralItem;
    double collateralValue;
};

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

void show_menu() {
    cout << "\n+--------------------------------------+\n";
    cout << "|          Welcome to LoanMate         |\n";
    cout << "+--------------------------------------+\n";
    cout << "|  [1] Start a New Loan Application    |\n";
    cout << "|  [2] View Loans Already Paid         |\n";
    cout << "|  [3] View Active (Unpaid) Loans      |\n";
    cout << "|  [4] Mark a Loan as Fully Paid       |\n";
    cout << "|  [5] Exit Program                    |\n";
    cout << "+--------------------------------------+\n";
    cout << "Select an option (1-5): ";

}

void show_summary(const Customer& c) {
    double totalInterest = c.loanAmount * c.interestRate / 100;
    double totalPayment = c.loanAmount + totalInterest;
    double monthlyPayment = totalPayment / c.months;

    cout << "\n+--------------------------------------+\n";
    cout << "|             LOAN SUMMARY             |\n";
    cout << "+--------------------------------------+\n";
    cout << "Customer Name: " << c.name << "\n";
    cout << "Loan Amount: PHP " << fixed << setprecision(2) << c.loanAmount << "\n";
    cout << "Interest Rate: " << c.interestRate << "%\n";
    cout << "Collateral: " << c.collateralItem << " (PHP " << fixed << setprecision(2) << c.collateralValue << ")\n";
    cout << "Repayment Period: " << c.months << " months\n";
    cout << "Monthly Payment: PHP " << fixed << setprecision(2) << monthlyPayment << "\n";
    cout << "Total Interest: PHP " << fixed << setprecision(2) << totalInterest << "\n";
    cout << "Total Payment: PHP " << fixed << setprecision(2) << totalPayment << "\n";
    cout << "+--------------------------------------+\n";

    cout << "+--------------------------------------+\n";
    cout << "| Important Notice:                    |\n";
    cout << "| Missed payments will result in:      |\n";
    cout << "| - Forfeiture of collateral           |\n";
    cout << "| - Remaining loan amount must still   |\n";
    cout << "|   be fully paid                      |\n";
    cout << "+--------------------------------------+\n";
    

    cout << "+--------+----------+----------+-----------+-----------+\n";
    cout << "| Month  | Payment  | Interest | Principal | Remaining |\n";
    cout << "+--------+----------+----------+-----------+-----------+\n";
    
    double remaining = totalPayment;
    for (int i = 1; i <= c.months; i++) {
        double interest = totalInterest / c.months;
        double principal = monthlyPayment - interest;
        remaining -= monthlyPayment;
        if (remaining < 0) remaining = 0;
    
        cout << "| " << setw(6) << i << " | "
             << setw(8) << fixed << setprecision(2) << monthlyPayment << " | "
             << setw(8) << interest << " | "
             << setw(9) << principal << " | "
             << setw(9) << remaining << " |\n";
    
        if (c.months > 12 && i == 6) {
            cout << "|   ... skipped for brevity ...            |\n";
            i = c.months - 6;
        }
    }
    
    cout << "+--------+----------+----------+-----------+-----------+\n";
    
}

void apply_loan() {
    if (customerCount >= MAX_CUSTOMERS) {
        cout << "Error: Customer limit reached.\n";
        return;
    }

    Customer c;

    cout << "\n+============================================+\n";
    cout << "|             LOAN APPLICATION               |\n";
    cout << "+============================================+\n";

    cout << "Enter customer name: ";
    getline(cin, c.name);
    if (c.name.empty()) {
        cout << "Error: Customer name cannot be empty.\n";
        return;
    }

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].name == c.name) {
            cout << "Error: A customer with this name already exists.\n";
            return;
        }
    }

    cout << "Enter loan amount (PHP): ";
    cin >> c.loanAmount;
    cin.ignore();
    if (c.loanAmount < 1000 || c.loanAmount > 500000) {
        cout << "Error: Loan amount must be between PHP 1,000 and PHP 500,000.\n";
        return;
    }

    cout << "Enter repayment period (months): ";
    cin >> c.months;
    cin.ignore();
    if (c.months < 3 || c.months > 24) {
        cout << "Error: Repayment period must be between 3 and 24 months.\n";
        return;
    }

    cout << "Enter collateral item: ";
    getline(cin, c.collateralItem);

    cout << "Enter collateral value (PHP): ";
    cin >> c.collateralValue;
    cin.ignore();
    if (c.collateralValue <= c.loanAmount) {
        cout << "Error: Collateral value must be greater than loan amount.\n";
        return;
    }

    c.interestRate = (c.loanAmount > 50000) ? 3.0 : 5.0;
    c.isPaid = false;

    show_summary(c);

    string confirm;
    cout << "Do you accept the loan terms? (Y/N): ";
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        customers[customerCount++] = c;
        cout << "\n+--------------------------------------------+\n";
        cout << "|    Loan application successfully added!    |\n";
        cout << "+--------------------------------------------+\n";
    } else {
        cout << "\n+--------------------------------------------+\n";
        cout << "|         Loan application cancelled.        |\n";
        cout << "+--------------------------------------------+\n";
    }
}



void view_paid_loans() {
    cout << "\n+------------ PAID LOANS ------------+\n";
    bool found = false;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].isPaid) {
            cout << "[" << i + 1 << "] " << customers[i].name
                 << " - PHP " << fixed << setprecision(2) << customers[i].loanAmount << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No paid loans.\n";
    }
    cout << "+--------------------------------------+\n";
}


void view_unpaid_loans() {
    cout << "\n+------------ UNPAID LOANS ------------+\n";
    bool found = false;
    for (int i = 0; i < customerCount; i++) {
        if (!customers[i].isPaid) {
            cout << "[" << i + 1 << "] " << customers[i].name
                 << " - PHP " << fixed << setprecision(2) << customers[i].loanAmount << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No unpaid loans.\n";
    }
    cout << "+--------------------------------------+\n";
}

void mark_loan_paid() {
    cout << "\n+------------ UNPAID LOANS ------------+\n";
    int indexMap[MAX_CUSTOMERS];
    int count = 0;

    for (int i = 0; i < customerCount; i++) {
        if (!customers[i].isPaid) {
            indexMap[count] = i;
            cout << "[" << count + 1 << "] " << customers[i].name
                 << " - PHP " << fixed << setprecision(2) << customers[i].loanAmount << "\n";
            count++;
        }
    }

    if (count == 0) {
        cout << "No unpaid loans.\n";
        cout << "+--------------------------------------+\n";
        return;
    }

    cout << "+--------------------------------------+\n";
    int choice;
    cout << "Enter number to mark as paid (0 to cancel): ";
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Cancelled marking loan as paid.\n";
        return;
    }

    if (choice < 1 || choice > count) {
        cout << "Invalid selection.\n";
        return;
    }

    int actualIndex = indexMap[choice - 1];
    customers[actualIndex].isPaid = true;

    cout << "\n+--------------------------------------+\n";
    cout << "|   Loan marked as paid successfully!  |\n";
    cout << "+--------------------------------------+\n";
}


int main() {
    string choice;
    while (true) {
        show_menu();
        getline(cin, choice);

        switch (stoi(choice)) {
            case 1:
                apply_loan();
                break;
            case 2:
                view_paid_loans();
                break;
            case 3:
                view_unpaid_loans();
                break;
            case 4:
                mark_loan_paid();
                break;
            case 5:
                cout << "Exiting LoanMate.\n";
                break;
            default:
                cout << "Error: Invalid choice.\n";
        }
    }
    return 0;
}
