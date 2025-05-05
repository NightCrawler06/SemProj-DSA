#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <algorithm> 

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



string to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void show_help() {
    cout << "\nSure! Here are the commands you can use:\n";
    cout << "  new         - Start a new loan application\n";
    cout << "  view paid   - Show all loans that are fully paid\n";
    cout << "  view active - Show loans that are still active\n";
    cout << "  mark paid   - Mark a specific loan as paid\n";
    cout << "  help        - Show this help message again\n";
    cout << "  exit        - Exit the chatbot\n";
}


void show_summary(const Customer& c) {
    double totalInterest = c.loanAmount * c.interestRate / 100;
    double totalPayment = c.loanAmount + totalInterest;
    double monthlyPayment = totalPayment / c.months;

    cout << "\nHere's your loan summary:\n";
    cout << "--------------------------------------------\n";
    cout << "Customer Name     : " << c.name << "\n";
    cout << "Loan Amount       : PHP " << fixed << setprecision(2) << c.loanAmount << "\n";
    cout << "Interest Rate     : " << c.interestRate << "%\n";
    cout << "Collateral        : " << c.collateralItem << " (PHP " << c.collateralValue << ")\n";
    cout << "Repayment Period  : " << c.months << " months\n";
    cout << "Monthly Payment   : PHP " << monthlyPayment << "\n";
    cout << "Total Interest    : PHP " << totalInterest << "\n";
    cout << "Total Payment     : PHP " << totalPayment << "\n";
    cout << "--------------------------------------------\n";

    cout << "Here's how your payment breakdown looks:\n";
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
             << setw(8) << monthlyPayment << " | "
             << setw(8) << interest << " | "
             << setw(9) << principal << " | "
             << setw(9) << remaining << " |\n";

        if (c.months > 12 && i == 6) {
            cout << "|   ... skipping middle months for clarity ...       |\n";
            i = c.months - 6;
        }
    }
    cout << "+--------+----------+----------+-----------+-----------+\n";
}


void apply_loan() {
    if (customerCount >= MAX_CUSTOMERS) {
        cout << "Sorry, we've reached our limit of customers for now.\n";
        return;
    }

    Customer c;
    cout << "\nGreat! Let's start your loan application.\n";
    cout << "What's your full name? ";
    getline(cin, c.name);

    if (c.name.empty()) {
        cout << "Oops! Name cannot be empty.\n";
        return;
    }

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].name == c.name) {
            cout << "Sorry, a customer with this name already exists.\n";
            return;
        }
    }

    cout << "Enter your desired loan amount (PHP): ";
    cin >> c.loanAmount;
    cin.ignore();
    if (c.loanAmount < 1000 || c.loanAmount > 500000) {
        cout << "Hmm... the loan should be between PHP 1,000 and PHP 500,000.\n";
        return;
    }

    cout << "For how many months do you want to pay? ";
    cin >> c.months;
    cin.ignore();
    if (c.months < 3 || c.months > 24) {
        cout << "Sorry! Repayment must be between 3 and 24 months.\n";
        return;
    }

    cout << "Please describe your collateral item: ";
    getline(cin, c.collateralItem);

    cout << "What's the value of your collateral (PHP)? ";
    cin >> c.collateralValue;
    cin.ignore();
    if (c.collateralValue <= c.loanAmount) {
        cout << "Collateral must be worth more than your loan.\n";
        return;
    }

    c.interestRate = (c.loanAmount > 50000) ? 3.0 : 5.0;
    c.isPaid = false;

    show_summary(c);

    cout << "Do you accept these loan terms? (Y/N): ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        customers[customerCount++] = c;
        cout << "Awesome! Your loan has been added successfully.\n";
    } else {
        cout << "No problem. Loan application has been canceled.\n";
    }
}

void view_paid_loans() {
    cout << "\nHere are the paid loans:\n";
    bool found = false;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].isPaid) {
            cout << "- " << customers[i].name << ": PHP " << fixed << setprecision(2) << customers[i].loanAmount << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Hmm... Looks like no loans have been paid yet.\n";
    }
}

void view_unpaid_loans() {
    cout << "\nHere are the active (unpaid) loans:\n";
    bool found = false;
    for (int i = 0; i < customerCount; i++) {
        if (!customers[i].isPaid) {
            cout << "- " << customers[i].name << ": PHP " << fixed << setprecision(2) << customers[i].loanAmount << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "All loans are paid. Great job!\n";
    }
}

void mark_loan_paid() {
    cout << "\nLet's mark a loan as paid.\n";
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
        cout << "Oops! There are no active loans to mark as paid.\n";
        return;
    }

    cout << "Which one would you like to mark as paid? (Enter number, 0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Got it, no changes made.\n";
        return;
    }

    if (choice < 1 || choice > count) {
        cout << "That's not a valid option.\n";
        return;
    }

    customers[indexMap[choice - 1]].isPaid = true;
    cout << "Perfect! Loan has been marked as paid.\n";
}

int main() {
    string command;
    cout << "Hello! I'm LoanMate — your friendly loan assistant.\n";
    cout << "Type 'help' to see what I can do!\n";

    while (true) {
        cout << "\nWhat would you like to do? > ";
        getline(cin, command);


        string cmd = to_lower(command);

        if (cmd.find("new") != string::npos) {
            apply_loan();
        } else if (cmd.find("paid") != string::npos && cmd.find("mark") == string::npos) {
            view_paid_loans();
        } else if (cmd.find("active") != string::npos || cmd.find("unpaid") != string::npos) {
            view_unpaid_loans();
        } else if (cmd.find("mark") != string::npos) {
            mark_loan_paid();
        } else if (cmd.find("help") != string::npos) {
            show_help();
        } else if (cmd.find("exit") != string::npos || cmd.find("quit") != string::npos) {
            cout << "Goodbye! Thanks for using LoanMate.\n";
            break;
        } else {
            cout << "Hmm... I didn't catch that. Try something like 'new', 'paid', or 'help'.\n";
        }
    }


    return 0;
}
