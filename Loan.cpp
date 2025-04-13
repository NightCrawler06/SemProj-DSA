#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Date {
    int day, month, year;
};

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

// Global variables
vector<Customer> customers;

// Utility functions
void print_slow(string text, int delay = 20) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void print_bot_message() {
    cout << "\n[LoanBot]> ";
}

void clear_screen() {
    system("cls");
}

bool check_name(string name) {
    if (name.empty()) return false;
    
    for (char c : name) {
        if (!isalnum(c) && c != ' ' && c != '_' && c != '-')
            return false;
    }
    return true;
}

void show_error(string message) {
    print_bot_message();
    print_slow(message);
    this_thread::sleep_for(chrono::milliseconds(1500));
}

// Date functions
bool is_leap_year(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int get_days_in_month(int month, int year) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) return 29;
    return days[month];
}

Date get_current_date() {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    return {localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900};
}

Date get_next_payment_date(Date current) {
    Date next = {current.day, current.month + 1, current.year};
    
    if (next.month > 12) {
        next.month = 1;
        next.year++;
    }
    
    int max_days = get_days_in_month(next.month, next.year);
    if (next.day > max_days) next.day = max_days;
    
    return next;
}

// File operations
void save_customers() {
    ofstream file("customers.txt");
    
    for (const Customer& c : customers) {
        file << c.name << "|" << c.loanAmount << "|" << c.interestRate << "|"
             << c.months << "|" << c.isPaid << "|" << c.paymentDate.day << "|"
             << c.paymentDate.month << "|" << c.paymentDate.year << "|"
             << c.nextPaymentDate.day << "|" << c.nextPaymentDate.month << "|"
             << c.nextPaymentDate.year << "|" << c.collateralItem << "|"
             << c.collateralValue << endl;
    }
    
    file.close();
    print_bot_message();
    print_slow("Data saved successfully.");
}

void load_customers() {
    ifstream file("customers.txt");
    string line;
    
    customers.clear();
    
    while (getline(file, line)) {
        Customer c;
        string token;
        size_t pos = 0;
        int field = 0;
        
        while ((pos = line.find("|")) != string::npos) {
            token = line.substr(0, pos);
            
            switch (field) {
                case 0: c.name = token; break;
                case 1: c.loanAmount = stod(token); break;
                case 2: c.interestRate = stod(token); break;
                case 3: c.months = stoi(token); break;
                case 4: c.isPaid = (token == "1"); break;
                case 5: c.paymentDate.day = stoi(token); break;
                case 6: c.paymentDate.month = stoi(token); break;
                case 7: c.paymentDate.year = stoi(token); break;
                case 8: c.nextPaymentDate.day = stoi(token); break;
                case 9: c.nextPaymentDate.month = stoi(token); break;
                case 10: c.nextPaymentDate.year = stoi(token); break;
                case 11: c.collateralItem = token; break;
            }
            
            line.erase(0, pos + 1);
            field++;
        }
        
        c.collateralValue = stod(line);
        customers.push_back(c);
    }
    
    file.close();
}

// Input handling
void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double get_valid_amount(string prompt) {
    double amount;
    while (true) {
        print_bot_message();
        print_slow(prompt);
        
        cin >> amount;
        
        if (cin.fail() || amount <= 0) {
            show_error("Error: Please enter a valid positive number.");
            clear_input();
            continue;
        }
        
        break;
    }
    clear_input();
    return amount;
}

int get_valid_integer(string prompt, int min, int max) {
    int value;
    while (true) {
        print_bot_message();
        print_slow(prompt);
        
        cin >> value;
        
        if (cin.fail() || value < min || value > max) {
            show_error("Error: Please enter a number between " + to_string(min) + " and " + to_string(max) + ".");
            clear_input();
            continue;
        }
        
        break;
    }
    clear_input();
    return value;
}

// Main functions
void show_menu() {
    clear_screen();
    cout << "\n========================================";
    cout << "\n       ChatBot Loan Manager Menu       ";
    cout << "\n========================================";
    print_bot_message();
    print_slow("Available commands:");
    cout << "\n\n1. loan     - Apply for a new loan";
    cout << "\n2. paid     - View paid customers";
    cout << "\n3. unpaid   - View unpaid customers";
    cout << "\n4. mark     - Mark loan as paid";
    cout << "\n5. exit     - Exit program";
    cout << "\n========================================\n";
    print_bot_message();
    print_slow("Enter command (1-5): ");
}

bool mark_loan_as_paid(string name) {
    auto it = find_if(customers.begin(), customers.end(), 
                    [&name](const Customer& c) { return c.name == name; });
    
    if (it != customers.end()) {
        if (it->isPaid) {
            print_bot_message();
            print_slow("Error: This loan is already marked as paid.");
            return false;
        }
        
        // Show loan details
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

        print_bot_message();
        print_slow("Are you sure you want to mark this loan as paid? (Y/n): ");
        string confirm;
        getline(cin, confirm);
        
        if (confirm.empty() || confirm == "y" || confirm == "Y") {
            it->isPaid = true;
            print_bot_message();
            print_slow("Loan status updated successfully.");
            save_customers();
            return true;
        } else {
            print_bot_message();
            print_slow("Operation cancelled.");
            return false;
        }
    } else {
        print_bot_message();
        print_slow("Error: Customer not found.");
        return false;
    }
}

void mark_paid_menu() {
    if (customers.empty()) {
        print_bot_message();
        print_slow("Error: No customers in the system.");
        return;
    }

    clear_screen();
    cout << "\n+--------------------------------+";
    cout << "\n|        UNPAID LOANS LIST       |";
    cout << "\n+--------------------------------+";
    
    bool has_unpaid = false;
    int counter = 1;
    
    for (const Customer& c : customers) {
        if (!c.isPaid) {
            cout << "\n\n" << counter << ". Name    : " << c.name;
            cout << "\n   Amount  : PHP " << fixed << setprecision(2) << c.loanAmount;
            
            cout << "\n   Due Date: ";
            if (c.nextPaymentDate.day < 10) cout << "0";
            cout << c.nextPaymentDate.day << "/";
            if (c.nextPaymentDate.month < 10) cout << "0";
            cout << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
            
            has_unpaid = true;
            counter++;
        }
    }
    cout << "\n+--------------------------------+\n";

    if (!has_unpaid) {
        print_bot_message();
        print_slow("No unpaid loans found in the system.");
        return;
    }

    string name;
    while (true) {
        print_bot_message();
        print_slow("Enter name to mark as paid (or 'cancel'): ");
        getline(cin, name);
        
        if (name == "cancel") {
            print_bot_message();
            print_slow("Operation cancelled.");
            return;
        }
        
        if (!check_name(name)) {
            show_error("Error: Invalid name format.");
            continue;
        }
        break;
    }

    mark_loan_as_paid(name);
}

void viewCustomers(bool paid_status) {
    print_bot_message();
    print_slow("Retrieving customer data...\n");
    
    cout << "\n----------------------------------------";
    cout << "\nSTATUS: " << (paid_status ? "PAID LOANS" : "UNPAID LOANS");
    cout << "\n----------------------------------------\n";
    
    vector<int> valid_indices;
    
    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].isPaid == paid_status) {
            cout << "\n[" << valid_indices.size() + 1 << "] Customer Name: " << customers[i].name;
            cout << "\n    Loan Amount: PHP " << fixed << setprecision(2) << customers[i].loanAmount;
            cout << "\n    Next Payment: " << customers[i].nextPaymentDate.day << "/"
                 << customers[i].nextPaymentDate.month << "/" << customers[i].nextPaymentDate.year;
            cout << "\n----------------------------------------";
            valid_indices.push_back(i);
        }
    }
    
    if (valid_indices.empty()) {
        print_bot_message();
        print_slow("No matching records found.");
        return;
    }
    
    if (!paid_status) {
        cout << "\n\n[M] Mark a loan as paid";
    }
    cout << "\n[R] Return to menu";
    
    while (true) {
        print_bot_message();
        if (!paid_status) {
            print_slow("Enter option (M/R or loan number): ");
        } else {
            print_slow("Enter option (R or loan number for details): ");
        }
                
        string option;
        getline(cin, option);
        
        transform(option.begin(), option.end(), option.begin(), ::toupper);
        
        if (option == "R") {
            break;
        } else if (!paid_status && option == "M") {
            print_bot_message();
            print_slow("Enter customer name to mark as paid: ");
            string name;
            getline(cin, name);
            
            if (mark_loan_as_paid(name)) {
                viewCustomers(paid_status);
                return;
            }
        } else {
            try {
                int index = stoi(option) - 1;
                if (index >= 0 && index < valid_indices.size()) {
                    int customer_index = valid_indices[index];
                    Customer c = customers[customer_index];
                    
                    cout << "\n----------------------------------------";
                    cout << "\nDETAILED LOAN INFORMATION";
                    cout << "\n----------------------------------------";
                    cout << "\nCustomer Name: " << c.name;
                    cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << c.loanAmount;
                    cout << "\nInterest Rate: " << c.interestRate << "%";
                    cout << "\nRepayment Period: " << c.months << " months";
                    cout << "\nCollateral Item: " << c.collateralItem;
                    cout << "\nCollateral Value: PHP " << fixed << setprecision(2) << c.collateralValue;
                    cout << "\nPayment Status: " << (c.isPaid ? "PAID" : "UNPAID");
                    cout << "\nNext Payment Date: " << c.nextPaymentDate.day << "/"
                         << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
                    cout << "\n----------------------------------------\n";
                    
                    if (!paid_status) {
                        print_bot_message();
                        print_slow("Mark this loan as paid? (Y/n): ");
                        string confirm;
                        getline(cin, confirm);
                        
                        if (confirm.empty() || confirm == "y" || confirm == "Y") {
                            if (mark_loan_as_paid(c.name)) {
                                viewCustomers(paid_status);
                                return;
                            }
                        }
                    } else {
                        print_bot_message();
                        print_slow("Press Enter to continue...");
                        cin.get();
                    }
                    
                    break;
                } else {
                    print_bot_message();
                    print_slow("Error: Invalid selection. Please try again.");
                }
            } catch (...) {
                print_bot_message();
                print_slow("Error: Invalid input. Please try again.");
            }
        }
    }
}

void applyForLoan() {
    Customer new_customer;
    clear_screen();
    cout << "\n==========================================";
    cout << "\n         LOAN APPLICATION FORM          ";
    cout << "\n==========================================\n";

    // Name validation
    while (true) {
        print_bot_message();
        print_slow("Enter customer name: ");
        getline(cin, new_customer.name);
        
        if (!check_name(new_customer.name)) {
            show_error("Error: Invalid name format.");
            continue;
        }
        
        if (any_of(customers.begin(), customers.end(), 
                  [&](const Customer& c) { return c.name == new_customer.name; })) {
            show_error("Error: A customer with this name already exists.");
            continue;
        }
        
        break;
    }
    
    // Loan amount validation
    while (true) {
        new_customer.loanAmount = get_valid_amount("Enter loan amount (PHP): ");
        
        if (new_customer.loanAmount < 1000 || new_customer.loanAmount > 1000000) {
            show_error("Error: Loan amount must be between PHP 1,000 and PHP 1,000,000.");
            continue;
        }
        
        break;
    }
    
    // Repayment period validation
    new_customer.months = get_valid_integer("Enter repayment period (months): ", 3, 60);
    
    // Collateral validation
    while (true) {
        print_bot_message();
        print_slow("Enter collateral description: ");
        getline(cin, new_customer.collateralItem);
        
        if (new_customer.collateralItem.length() < 3 || 
            all_of(new_customer.collateralItem.begin(), new_customer.collateralItem.end(), ::isspace)) {
            show_error("Error: Please provide a valid description (at least 3 characters).");
            continue;
        }
        
        break;
    }
    
    // Collateral value validation
    while (true) {
        new_customer.collateralValue = get_valid_amount("Enter collateral value (PHP): ");
        
        double min_required = new_customer.loanAmount * 0.5;
        if (new_customer.collateralValue < min_required) {
            print_bot_message();
            print_slow("Error: Insufficient collateral value.");
            print_bot_message();
            print_slow("Minimum required: PHP " + to_string(static_cast<int>(min_required)));
            continue;
        }
        
        break;
    }

    // Calculate loan terms
    new_customer.interestRate = (new_customer.loanAmount > 50000) ? 3.0 : 5.0;
    new_customer.isPaid = false;
    new_customer.paymentDate = get_current_date();
    new_customer.nextPaymentDate = get_next_payment_date(new_customer.paymentDate);

    // Calculate payments
    double totalInterest = new_customer.loanAmount * new_customer.interestRate / 100;
    double totalPayment = new_customer.loanAmount + totalInterest;
    double monthlyPayment = totalPayment / new_customer.months;
    
    // Display loan summary
    cout << "\n==========================================";
    cout << "\n           LOAN APPROVAL NOTICE           ";
    cout << "\n==========================================";
    cout << "\nCustomer Name: " << new_customer.name;
    cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << new_customer.loanAmount;
    cout << "\nInterest Rate: " << new_customer.interestRate << "% (One-Time Interest)";
    cout << "\nCollateral: " << new_customer.collateralItem;
    cout << "\nCollateral Value: PHP " << fixed << setprecision(2) << new_customer.collateralValue;
    cout << "\n==========================================";

    cout << "\n==========================================";
    cout << "\n           PAYMENT TERMS                  ";
    cout << "\n==========================================";
    cout << "\nMonthly Payment: PHP " << fixed << setprecision(2) << monthlyPayment;
    cout << "\nRepayment Period: " << new_customer.months << " months";
    cout << "\nTotal Interest: PHP " << fixed << setprecision(2) << totalInterest;
    cout << "\nTotal Payment: PHP " << fixed << setprecision(2) << totalPayment;
    
    // Payment schedule
    cout << "\n  Month   Payment Amount    Interest    Principal    Remaining Balance";
    cout << "\n  -----   -------------    --------    ---------    ----------------";

    double remainingBalance = totalPayment;
    for (int i = 1; i <= new_customer.months; i++) {
        double interestPayment = totalInterest / new_customer.months;
        double principalPayment = monthlyPayment - interestPayment;
        
        remainingBalance -= monthlyPayment;
        if (remainingBalance < 0) remainingBalance = 0;
        
        cout << "\n  " << setw(5) << i << "   ";
        cout << "PHP " << setw(10) << fixed << setprecision(2) << monthlyPayment << "    ";
        cout << "PHP " << setw(6) << fixed << setprecision(2) << interestPayment << "    ";
        cout << "PHP " << setw(7) << fixed << setprecision(2) << principalPayment << "    ";
        cout << "PHP " << setw(14) << fixed << setprecision(2) << remainingBalance;
        
        if (new_customer.months > 12 && i == 6) {
            cout << "\n  ...      ...             ...         ...         ...";
            i = new_customer.months - 6;
        }
    }

    cout << "\n----------------------------------------";
    cout << "\nTotal Payment: PHP " << fixed << setprecision(2) << totalPayment;
    cout << "\nTotal Interest: PHP " << fixed << setprecision(2) << totalInterest;
    cout << "\nTotal Principal: PHP " << fixed << setprecision(2) << new_customer.loanAmount;
    cout << "\n==========================================";
    
    // Confirmation
    print_bot_message();
    print_slow("Do you accept the loan terms? (Y/n): ");
    string confirm;
    getline(cin, confirm);
    
    transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
    
    if (confirm.empty() || confirm == "y" || confirm == "yes") {
        customers.push_back(new_customer);
        save_customers();
        print_bot_message();
        print_slow("Loan application successful!");
    } else {
        print_bot_message();
        print_slow("Loan application cancelled.");
    }
}

int main() {
    clear_screen();
    print_bot_message();
    print_slow("Initializing Loan Management System...\n");
    this_thread::sleep_for(chrono::milliseconds(1000));
    
    load_customers();

    string choice;
    do {
        show_menu();
        getline(cin, choice);

        if (choice.length() != 1 || !isdigit(choice[0])) {
            print_bot_message();
            print_slow("Error: Please enter a number between 1 and 5.");
            continue;
        }

        int choiceNum = choice[0] - '0';
        
        switch (choiceNum) {
            case 1: applyForLoan(); break;
            case 2: viewCustomers(true); break;
            case 3: viewCustomers(false); break;
            case 4: mark_paid_menu(); break;
            case 5: 
                print_bot_message();
                print_slow("Shutting down system...");
                break;
            default:
                print_bot_message();
                print_slow("Error: Invalid command. Please enter a number between 1 and 5.");
        }
        
        if (choiceNum != 5) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != "5");

    return 0;
}