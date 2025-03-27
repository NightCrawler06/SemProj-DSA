#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;


//Date structure to store date
struct Date {
    int day, month, year;
};


//Customer structure to store customer data
struct Customer {
    string name;
    double loanAmount;
    double interestRate;
    int months;
    bool isPaid;
    Date paymentDate;
    Date nextPaymentDate;
    string collateralItem;
    double collateralValue;
};


//Box lng
void printBox(const string& text) {
    int width = max(40, static_cast<int>(text.length()));
    int padding = (width - text.length()) / 2;

    cout << "\n+" << string(width + 2, '-') << "+";
    cout << "\n| " << string(padding, ' ') << text << string(width - text.length() - padding, ' ') << " |";
    cout << "\n+" << string(width + 2, '-') << "+\n";
}




//simple Menu ui to
void printMenu() {
    cout << "\n+------------------------------------------+";
    cout << "\n|         ChatBot Loan Manager Menu        |";
    cout << "\n+------------------------------------------+";
    cout << "\n|    1. Apply for Loan                     |";
    cout << "\n|    2. View Paid Customers                |";
    cout << "\n|    3. View Unpaid Customers              |";
    cout << "\n|    4. Mark as Paid                       |";
    cout << "\n|    5. Exit                               |";
    cout << "\n+------------------------------------------+";
    cout << "\nWhat would you like to do? ";
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

//Next Payment date logic
Date getNextPaymentDate(Date currentDate) {
    currentDate.month++;
    if (currentDate.month > 12) {
        currentDate.month = 1;
        currentDate.year++;
    }
    currentDate.day = min(currentDate.day, daysInMonth(currentDate.month, currentDate.year));
    return currentDate;
}

Date getCurrentDate() {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    return {localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900};
}

double calculateMonthlyPayment(double loan, double rate, int months) {
    double monthlyRate = rate / 100 / 12;
    double factor = pow(1 + monthlyRate, months);
    return (loan * monthlyRate * factor) / (factor - 1);
}


//save sa txt file
void saveCustomers(const vector<Customer>& customers) {
    ofstream file("customers.txt");
    for (const auto& c : customers) {
        file << c.name << " | " << c.loanAmount << " | " << c.interestRate << " | "
                << c.months << " | " << c.isPaid << " | " << c.paymentDate.day << " "
                << c.paymentDate.month << " | " << c.paymentDate.year << " | "
                << c.nextPaymentDate.day << " | " << c.nextPaymentDate.month << " | "
                << c.nextPaymentDate.year << " | " << c.collateralItem << " | "
                << c.collateralValue << endl;
    }
    printBox("Data saved successfully!");
}

void viewCustomers(const vector<Customer>& customers, bool paidStatus) {
    printBox(paidStatus ? "Paid Customers" : "Unpaid Customers");
    for (const auto& c : customers) {
        if (c.isPaid == paidStatus) {
            cout << "Name: " << c.name << " | Loan Amount: PHP" << c.loanAmount << " | Status: " << (c.isPaid ? "Paid" : "Unpaid") << endl;
        }
    }
}

void markAsPaid(vector<Customer>& customers) {
    string name;
    cout << "Enter customer name to mark as paid: ";
    cin >> name;

    for (auto& c : customers) {
        if (c.name == name) {
            c.isPaid = true;
            printBox("Customer marked as paid.");
            saveCustomers(customers);
            return;
        }
    }
    printBox("Customer not found.");
}

void applyForLoan(vector<Customer>& customers) {
    Customer c;
    cout << "\n+------------------------------------------+";
    cout << "\n|         Hello! Let's get started         |";          
    cout << "\n|        with your loan application.       |";
    cout << "\n+------------------------------------------+";

    cout << "\nWhat is your name?  \n >";
    cin >> c.name;

    cout << "How much loan do you need (PHP)? \n > ";
    cin >> c.loanAmount;
    cout << "For how many months will you repay it? \n > ";
    cin >> c.months;

    cout << "What will you offer as collateral\n(e.g., Car, House, Jewelry)? \n > ";
    cin.ignore();
    getline(cin, c.collateralItem);

    cout << "What is the estimated value of your\ncollateral (PHP)? \n > ";
    cin >> c.collateralValue;

    if (c.collateralValue < c.loanAmount * 0.5) {
        cout << "\n+------------------------------------------+";
        cout << "\n|         Your collateral value is         |";
        cout << "\n|              insufficient.               |";
        cout << "\n|         Loan application denied.         |";
        cout << "\n+------------------------------------------+";
        return;
    }

    c.interestRate = (c.loanAmount > 50000) ? 6.0 : 5.0;
    c.isPaid = false;
    c.paymentDate = getCurrentDate();
    c.nextPaymentDate = getNextPaymentDate(c.paymentDate); 
    double monthlyPayment = calculateMonthlyPayment(c.loanAmount, c.interestRate, c.months);

    cout << "\n+------------------------------------------+";
    cout << "\n|            Congratulations!              |";
    cout << "\n|         Your loan is approved.           |";
    cout << "\n+------------------------------------------+";

    cout << "\nInterest Rate: " << c.interestRate << "%\n";
    cout << "Monthly Payment: PHP" << monthlyPayment << "\n";
    cout << "First Payment Due: " << c.nextPaymentDate.day << "/" << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year << "\n";

    customers.push_back(c);
    saveCustomers(customers);
}

int main() {
    vector<Customer> customers;
    int choice;

    printBox("Welcome to Lending ChatBot!");
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            applyForLoan(customers);
            break;
        case 2:
            viewCustomers(customers, true);
            break; 
        case 3:
            viewCustomers(customers, false);
            break;
        case 4:
            markAsPaid(customers);
            break;
        case 5:
            printBox("Goodbye! Have a great day!");
            break;
        default:
            printBox("Invalid choice. Please try again.");
        }
    } while (choice != 5);

    return 0;
}
