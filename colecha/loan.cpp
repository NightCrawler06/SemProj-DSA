

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

struct Date {
    int day, month, year;
};

struct Loan {
    string name;
    double amount;
    double rateOfInterest;
    int months;
    bool alreadyPaid;
    Date dateOfPayment;
    string collateral;
    double valueOfCollateral;
};

vector<Loan> loans;

Date getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return {ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900};
}

string formatDate(Date d) {
    stringstream ss;
    ss << setw(2) << setfill('0') << d.day << "/"
       << setw(2) << setfill('0') << d.month << "/"
       << d.year;
    return ss.str();
}

void loadLoans() {
    ifstream file("loans.txt");
    string line;
    while (getline(file, line)) {
        Loan loan;
        stringstream ss(line);
        string paid, date;

        getline(ss, loan.name, '|');
        ss >> loan.amount;
        ss.ignore();
        ss >> loan.rateOfInterest;
        ss.ignore();
        ss >> loan.months;
        ss.ignore();
        getline(ss, paid, '|');
        getline(ss, date, '|');
        getline(ss, loan.collateral, '|');
        ss >> loan.valueOfCollateral;

        loan.alreadyPaid = (paid == "1");

        sscanf(date.c_str(), "%d/%d/%d", &loan.dateOfPayment.day, &loan.dateOfPayment.month, &loan.dateOfPayment.year);

        loans.push_back(loan);
    }
    file.close();
}

void applyLoan() {
    Loan loan;
    cout << "\n[Apply for a New Loan]\n";
    cout << "Name: ";
    getline(cin, loan.name);

    cout << "Loan Amount (PHP): ";
    cin >> loan.amount;
    cout << "Interest Rate (% per annum): ";
    cin >> loan.rateOfInterest;
    cout << "Payment Duration (months): ";
    cin >> loan.months;
    cin.ignore();

    cout << "Collateral Description: ";
    getline(cin, loan.collateral);
    cout << "Collateral Value (PHP): ";
    cin >> loan.valueOfCollateral;
    cin.ignore();

    loan.dateOfPayment = getCurrentDate();
    loan.alreadyPaid = false;

    // Calculations
    double totalInterest = (loan.amount * loan.rateOfInterest * loan.months) / (12 * 100);
    double totalPayable = loan.amount + totalInterest;
    double monthlyPayment = totalPayable / loan.months;

    Date dueDate = loan.dateOfPayment;
    dueDate.month += loan.months;
    while (dueDate.month > 12) {
        dueDate.month -= 12;
        dueDate.year++;
    }

    loans.push_back(loan);
    cout << "\n================ Loan Details =================\n";
    cout << "Borrower Name     : " << loan.name << "\n\n";
    cout << "Loan Amount       : PHP " << fixed << setprecision(2) << loan.amount << "\n";
    cout << "Interest Rate     : " << loan.rateOfInterest << "% per annum\n";
    cout << "Payment Duration  : " << loan.months << " months\n";
    cout << "Monthly Payment   : PHP " << monthlyPayment << "\n";
    cout << "Total to Pay      : PHP " << totalPayable << "\n";
    cout << "Start Date        : " << formatDate(loan.dateOfPayment) << "\n";
    cout << "Due Date          : " << formatDate(dueDate) << "\n";
    cout << "Collateral        : " << loan.collateral << " (Value: PHP " << loan.valueOfCollateral << ")\n";
    cout << "------------------------------------------------\n";
    cout << "Penalty if unpaid on time:\n";
    cout << "  > Collateral becomes lender's property\n";
    cout << "  > Consumer still required to pay remaining balance\n";
    cout << "=====================================================\n";
}


void listLoans(bool paid) {
    cout << "\n[" << (paid ? "Paid" : "Unpaid") << " Loans]\n";
    int count = 0;
    for (const Loan &l : loans) {
        if (l.alreadyPaid == paid) {
            count++;
            cout << count << ". " << l.name << " | PHP " << fixed << setprecision(2) << l.amount
                 << " | " << formatDate(l.dateOfPayment) << " | " << l.collateral << "\n";
        }
    }
    if (count == 0) {
        cout << "No " << (paid ? "paid" : "unpaid") << " loans found.\n";
    }
}

void markAsPaid() {
    string name;
    cout << "\n[Mark Loan as Paid]\n";
    cout << "Enter customer name: ";
    getline(cin, name);

    for (Loan &l : loans) {
        if (l.name == name && !l.alreadyPaid) {
            l.alreadyPaid = true;
            cout << "Marked as paid successfully.\n";
            return;
        }
    }
    cout << "No unpaid loan found under that name.\n";
}

void showMenu() {
    cout << "\n========== Loan Manager ==========\n";
    cout << "1. Apply for loan\n";
    cout << "2. View paid loans\n";
    cout << "3. View unpaid loans\n";
    cout << "4. Mark loan as paid\n";
    cout << "5. Exit\n";
    cout << "==================================\n";
    cout << "Choose an option (1-5): ";
}

int main() {
    loadLoans();
    string choice;

    while (true) {
        showMenu();
        getline(cin, choice);

        if (choice == "1") applyLoan();
        else if (choice == "2") listLoans(true);
        else if (choice == "3") listLoans(false);
        else if (choice == "4") markAsPaid();
        else if (choice == "5") {
            cout << "Exiting... Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }

    return 0;
}

