#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

void slowPrint(const string& text, int delay = 20) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void printPrompt() {
    cout << "\n[LoanBot]> ";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool isValidName(const string& name) {
    return !name.empty() && 
            all_of(name.begin(), name.end(), [](char c) {
                return isalnum(c) || c == ' ' || c == '_' || c == '-';
            });
}



void printErrorMessage(const string& message) {
    printPrompt();
    slowPrint(message);
    this_thread::sleep_for(chrono::milliseconds(2000)); 
}

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
    clearScreen();
    cout << "\n===========================================";
    cout << "\n         ChatBot Loan Manager Menu         ";
    cout << "\n===========================================";
    printPrompt();
    slowPrint("Available commands:");
    cout << "\n\n1. loan     - Apply for a new loan";
    cout << "\n2. paid     - View paid customers";
    cout << "\n3. unpaid   - View unpaid customers";
    cout << "\n4. mark     - Mark loan as paid";
    cout << "\n5. exit     - Exit program";
    cout << "\n===========================================\n";
    printPrompt();
    slowPrint("Enter command (1-5): ");
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
        file << c.name << "|" << c.loanAmount << "|" << c.interestRate << "|"
                << c.months << "|" << c.isPaid << "|" << c.paymentDate.day << "|"
                << c.paymentDate.month << "|" << c.paymentDate.year << "|"
                << c.nextPaymentDate.day << "|" << c.nextPaymentDate.month << "|"
                << c.nextPaymentDate.year << "|" << c.collateralItem << "|"
                << c.collateralValue << endl;
    }
    printPrompt();
    slowPrint("Data saved successfully.");
}

void viewCustomers(const vector<Customer>& customers, bool paidStatus) {
    printPrompt();
    slowPrint("Retrieving customer data...\n");
    
    cout << "\n----------------------------------------";
    cout << "\nSTATUS: " << (paidStatus ? "PAID" : "UNPAID") << " LOANS";
    cout << "\n----------------------------------------\n";
    
    bool found = false;
    for (const auto& c : customers) {
        if (c.isPaid == paidStatus) {
            cout << "\nCustomer Name: " << c.name;
            cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << c.loanAmount;
            cout << "\nNext Payment: " << c.nextPaymentDate.day << "/"
                    << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
            cout << "\n----------------------------------------";
            found = true;
        }
    }
    
    if (!found) {
        printPrompt();
        slowPrint("No matching records found.");
    }
}

void markAsPaid(vector<Customer>& customers) {
    if (customers.empty()) {
        printPrompt();
        slowPrint("Error: No customers in the system.");
        return;
    }

    clearScreen();
    cout << "\n+--------------------------------+";
    cout << "\n|        UNPAID LOANS LIST       |";
    cout << "\n+--------------------------------+";
    
    bool hasUnpaidLoans = false;
    int counter = 1;
    
    for (const auto& c : customers) {
        if (!c.isPaid) {
            cout << "\n\n" << counter << ". Name    : " << c.name;
            cout << "\n   Amount  : PHP " << fixed << setprecision(2) << c.loanAmount;
            cout << "\n   Due Date: " << setfill('0') << setw(2) << c.nextPaymentDate.day << "/"
                 << setfill('0') << setw(2) << c.nextPaymentDate.month << "/"
                 << c.nextPaymentDate.year;
            hasUnpaidLoans = true;
            counter++;
        }
    }
    cout << "\n+--------------------------------+\n";

    if (!hasUnpaidLoans) {
        printPrompt();
        slowPrint("No unpaid loans found in the system.");
        return;
    }

    string name;
    while (true) {
        printPrompt();
        slowPrint("Enter name to mark as paid (or 'cancel'): ");
        getline(cin, name);
        
        if (name == "cancel") {
            printPrompt();
            slowPrint("Operation cancelled.");
            return;
        }
        
        if (!isValidName(name)) {
            printErrorMessage("Error: Invalid name format.");
            continue;
        }
        break;
    }

    auto it = find_if(customers.begin(), customers.end(),
        [&name](const Customer& c) { return c.name == name; });
        
    if (it != customers.end()) {
        if (it->isPaid) {
            printPrompt();
            slowPrint("Error: This loan is already marked as paid.");
            return;
        }
        
        // Show loan details before confirmation
        cout << "\n----------------------------------------";
        cout << "\nLOAN DETAILS";
        cout << "\n----------------------------------------";
        cout << "\nCustomer Name: " << it->name;
        cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << it->loanAmount;
        cout << "\nInterest Rate: " << it->interestRate << "%";
        cout << "\nCollateral: " << it->collateralItem;
        cout << "\nNext Payment Date: " << it->nextPaymentDate.day << "/"
             << it->nextPaymentDate.month << "/" << it->nextPaymentDate.year;
        cout << "\n----------------------------------------\n";

        printPrompt();
        slowPrint("Are you sure you want to mark this loan as paid? (y/n): ");
        string confirm;
        getline(cin, confirm);
        
        if (confirm == "y" || confirm == "Y") {
            it->isPaid = true;
            printPrompt();
            slowPrint("Loan status updated successfully.");
            saveCustomers(customers);
        } else {
            printPrompt();
            slowPrint("Operation cancelled.");
        }
    } else {
        printPrompt();
        slowPrint("Error: Customer not found.");
    }
}

// Helper validation functions
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


double getValidAmount(const string& prompt) {
    double amount;
    while (true) {
        printPrompt();
        slowPrint(prompt);
        
        if (!(cin >> amount)) {
            printErrorMessage("Error: Please enter a valid number.");
            clearInputBuffer();
            continue;
        }
        
        if (amount <= 0) {
            printErrorMessage("Error: Amount must be greater than 0.");
            continue;
        }
        
        break;
    }
    clearInputBuffer();
    return amount;
}

int getValidInteger(const string& prompt, int min, int max) {
    int value;
    while (true) {
        printPrompt();
        slowPrint(prompt);
        
        if (!(cin >> value)) {
            printErrorMessage("Error: Please enter a valid number.");
            clearInputBuffer();
            continue;
        }
        
        if (value < min || value > max) {
            printErrorMessage("Error: Value must be between " + to_string(min) + " and " + to_string(max) + ".");
            continue;
        }
        
        break;
    }
    clearInputBuffer();
    return value;
}

void applyForLoan(vector<Customer>& customers) {
    Customer c;
    clearScreen();
    cout << "\n===========================================";
    cout << "\n           LOAN APPLICATION FORM          ";
    cout << "\n===========================================\n";

    // Name validation
    while (true) {
        printPrompt();
        slowPrint("Enter customer name: ");
        getline(cin, c.name);
        
        if (!isValidName(c.name)) {
            printErrorMessage("Error: Name must contain only letters, numbers, spaces, underscores, or hyphens.");
            continue;
        }
        
        // Check for duplicate names
        if (any_of(customers.begin(), customers.end(), 
            [&c](const Customer& customer) { return customer.name == c.name; })) {
            printErrorMessage("Error: A customer with this name already exists.");
            continue;
        }
        
        break;
    }
    
    // Loan amount validation
    while (true) {
        c.loanAmount = getValidAmount("Enter loan amount (PHP): ");
        
        if (c.loanAmount < 1000) {
            printErrorMessage("Error: Minimum loan amount is PHP 1,000.");
            continue;
        }
        
        if (c.loanAmount > 1000000) {
            printErrorMessage("Error: Maximum loan amount is PHP 1,000,000.");
            continue;
        }
        
        break;
    }
    
    // Repayment period validation
    c.months = getValidInteger("Enter repayment period (months): ", 3, 60);
    
    // Collateral type validation
    while (true) {
        printPrompt();
        slowPrint("Enter collateral description: ");
        getline(cin, c.collateralItem);
        
        if (c.collateralItem.empty()) {
            printPrompt();
            slowPrint("Error: Collateral description cannot be empty.");
            continue;
        }
        
        if (c.collateralItem.length() < 3) {
            printPrompt();
            slowPrint("Error: Please provide a more detailed description (at least 3 characters).");
            continue;
        }
        
        // Basic sanitization
        if (all_of(c.collateralItem.begin(), c.collateralItem.end(), ::isspace)) {
            printPrompt();
            slowPrint("Error: Description cannot be only whitespace.");
            continue;
        }
        
        break;
    }
    
    // Collateral value validation
    while (true) {
        c.collateralValue = getValidAmount("Enter collateral value (PHP): ");
        
        double minRequired = c.loanAmount * 0.5;
        if (c.collateralValue < minRequired) {
            printPrompt();
            slowPrint("Error: Insufficient collateral value.");
            printPrompt();
            slowPrint("Minimum required: PHP " + to_string(static_cast<int>(minRequired)));
            continue;
        }
        
        break;
    }

    // Calculate loan terms
    c.interestRate = (c.loanAmount > 50000) ? 6.0 : 5.0;
    c.isPaid = false;
    c.paymentDate = getCurrentDate();
    c.nextPaymentDate = getNextPaymentDate(c.paymentDate);
    double monthlyPayment = calculateMonthlyPayment(c.loanAmount, c.interestRate, c.months);

    // Display loan summary
    cout << "\n===========================================";
    cout << "\n           LOAN APPROVAL NOTICE           ";
    cout << "\n===========================================";
    cout << "\nCustomer Name: " << c.name;
    cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << c.loanAmount;
    cout << "\nInterest Rate: " << c.interestRate << "%";
    cout << "\nMonthly Payment: PHP " << monthlyPayment;
    cout << "\nRepayment Period: " << c.months << " months";
    cout << "\nCollateral: " << c.collateralItem;
    cout << "\nCollateral Value: PHP " << fixed << setprecision(2) << c.collateralValue;
    cout << "\nFirst Payment Due: " << c.nextPaymentDate.day << "/"
         << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
    cout << "\n===========================================\n";

    // Confirmation prompt
    printPrompt();
    slowPrint("Do you want to proceed with the loan application? (y/n): ");
    string confirm;
    getline(cin, confirm);
    transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
    
    if (confirm == "y" || confirm == "yes") {
        customers.push_back(c);
        saveCustomers(customers);
        printPrompt();
        slowPrint("Loan application successful!");
    } else {
        printPrompt();
        slowPrint("Loan application cancelled.");
    }
}

int main() {
    vector<Customer> customers;
    string choice;
    
    clearScreen();
    printPrompt();
    slowPrint("Initializing Loan Management System...\n");
    this_thread::sleep_for(chrono::milliseconds(1000));

    do {
        printMenu();
        getline(cin, choice);

        if (choice.length() != 1 || !isdigit(choice[0])) {
            printPrompt();
            slowPrint("Error: Please enter a number between 1 and 5.");
            continue;
        }

        int choiceNum = choice[0] - '0';
        
        switch (choiceNum) {
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
                printPrompt();
                slowPrint("Shutting down system...");
                break;
            default:
                printPrompt();
                slowPrint("Error: Invalid command. Please enter a number between 1 and 5.");
        }
        
        if (choiceNum != 5) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    } while (choice != "5");

    return 0;
}
