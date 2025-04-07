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

// Global variables para sa buong program
vector<struct Customer> all_customers;
string input;

// Function para mag-print ng text slowly
void print_slow(string text, int delay = 20) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

// Print yung bot message start
void print_bot_message() {
    cout << "\n[LoanBot]> ";
}

// Clear the screen
void clear_screen() {
    system("cls");
}

// Check kung valid ang name
bool check_name(string name) {
    if (name.empty()) {
        return false;
    }
    
    for (int i = 0; i < name.length(); i++) {
        char c = name[i];
        if (!isalnum(c) && c != ' ' && c != '_' && c != '-') {
            return false;
        }
    }
    
    return true;
}

// Print error message
void show_error(string message) {
    print_bot_message();
    print_slow(message);
    this_thread::sleep_for(chrono::milliseconds(2000)); 
}

// Date info storage
struct Date {
    int day;
    int month;
    int year;
};

// Customer info storage
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

// Print box around text
void print_box(string text) {
    int width;
    if (40 > text.length()) {
        width = 40;
    } else {
        width = text.length();
    }
    
    int padding = (width - text.length()) / 2;
    
    string dashes = "";
    for (int i = 0; i < width + 2; i++) {
        dashes += "-";
    }
    
    string spaces1 = "";
    for (int i = 0; i < padding; i++) {
        spaces1 += " ";
    }
    
    string spaces2 = "";
    for (int i = 0; i < width - text.length() - padding; i++) {
        spaces2 += " ";
    }

    cout << "\n+" << dashes << "+";
    cout << "\n| " << spaces1 << text << spaces2 << " |";
    cout << "\n+" << dashes << "+\n";
}

// Display main menu
void show_menu() {
    clear_screen();
    cout << "\n===========================================";
    cout << "\n         ChatBot Loan Manager Menu         ";
    cout << "\n===========================================";
    print_bot_message();
    print_slow("Available commands:");
    cout << "\n\n1. loan     - Apply for a new loan";
    cout << "\n2. paid     - View paid customers";
    cout << "\n3. unpaid   - View unpaid customers";
    cout << "\n4. mark     - Mark loan as paid";
    cout << "\n5. exit     - Exit program";
    cout << "\n===========================================\n";
    print_bot_message();
    print_slow("Enter command (1-5): ");
}

// Check kung leap year
bool is_leap_year(int year) {
    if (year % 400 == 0) {
        return true;
    }
    
    if (year % 100 == 0) {
        return false;
    }
    
    if (year % 4 == 0) {
        return true;
    }
    
    return false;
}

// Get number of days sa isang month
int get_days_in_month(int month, int year) {
    if (month == 1) return 31;
    if (month == 2) {
        if (is_leap_year(year)) {
            return 29;
        } else {
            return 28;
        }
    }
    if (month == 3) return 31;
    if (month == 4) return 30;
    if (month == 5) return 31;
    if (month == 6) return 30;
    if (month == 7) return 31;
    if (month == 8) return 31;
    if (month == 9) return 30;
    if (month == 10) return 31;
    if (month == 11) return 30;
    if (month == 12) return 31;
    
    return 30; // Default just in case
}

// Calculate next payment date
Date get_next_payment_date(Date current_date) {
    Date new_date;
    
    new_date.day = current_date.day;
    new_date.month = current_date.month + 1;
    new_date.year = current_date.year;
    
    if (new_date.month > 12) {
        new_date.month = 1;
        new_date.year = new_date.year + 1;
    }
    
    int max_days = get_days_in_month(new_date.month, new_date.year);
    if (new_date.day > max_days) {
        new_date.day = max_days;
    }
    
    return new_date;
}

// Get current system date
Date get_current_date() {
    Date today;
    time_t now = time(0);
    tm *localTime = localtime(&now);
    
    today.day = localTime->tm_mday;
    today.month = localTime->tm_mon + 1;
    today.year = localTime->tm_year + 1900;
    
    return today;
}

// Calculate monthly payment amount
double calculate_monthly_payment(double loan, double rate, int months) {
    double monthlyRate = rate / 100 / 12;
    double factor = pow(1 + monthlyRate, months);
    double payment = (loan * monthlyRate * factor) / (factor - 1);
    return payment;
}

// Save customers sa file
void save_customers_to_file() {
    ofstream file;
    file.open("customers.txt");
    
    for (int i = 0; i < all_customers.size(); i++) {
        Customer c = all_customers[i];
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

// Mark loan as paid
bool mark_loan_as_paid(string name) {
    bool found = false;
    int index = -1;
    
    // Find the customer
    for (int i = 0; i < all_customers.size(); i++) {
        if (all_customers[i].name == name) {
            found = true;
            index = i;
            break;
        }
    }
    
    if (found) {
        if (all_customers[index].isPaid) {
            print_bot_message();
            print_slow("Error: This loan is already marked as paid.");
            return false;
        }
        
        // Show loan details before confirmation
        cout << "\n----------------------------------------";
        cout << "\nLOAN DETAILS";
        cout << "\n----------------------------------------";
        cout << "\nCustomer Name: " << all_customers[index].name;
        cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << all_customers[index].loanAmount;
        cout << "\nInterest Rate: " << all_customers[index].interestRate << "%";
        cout << "\nCollateral: " << all_customers[index].collateralItem;
        cout << "\nNext Payment Date: " << all_customers[index].nextPaymentDate.day << "/"
             << all_customers[index].nextPaymentDate.month << "/" << all_customers[index].nextPaymentDate.year;
        cout << "\n----------------------------------------\n";

        print_bot_message();
        print_slow("Are you sure you want to mark this loan as paid? (Y/n): ");
        string confirm;
        getline(cin, confirm);
        
        if (confirm.empty()) {
            confirm = "y";
        }

        if (confirm == "y" || confirm == "Y") {
            all_customers[index].isPaid = true;
            print_bot_message();
            print_slow("Loan status updated successfully.");
            save_customers_to_file();
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

// View list ng customers
void viewCustomers(bool paid_status) {
    print_bot_message();
    print_slow("Retrieving customer data...\n");
    
    cout << "\n----------------------------------------";
    if (paid_status) {
        cout << "\nSTATUS: PAID LOANS";
    } else {
        cout << "\nSTATUS: UNPAID LOANS";
    }
    cout << "\n----------------------------------------\n";
    
    // Store indices ng matching customers
    vector<int> valid_indices;
    
    for (int i = 0; i < all_customers.size(); i++) {
        Customer c = all_customers[i];
        if (c.isPaid == paid_status) {
            cout << "\n[" << valid_indices.size() + 1 << "] Customer Name: " << c.name;
            cout << "\n    Loan Amount: PHP " << fixed << setprecision(2) << c.loanAmount;
            cout << "\n    Next Payment: " << c.nextPaymentDate.day << "/"
                 << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
            cout << "\n----------------------------------------";
            valid_indices.push_back(i);
        }
    }
    
    if (valid_indices.size() == 0) {
        print_bot_message();
        print_slow("No matching records found.");
        return;
    }
    
    // Only show options for unpaid loans
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
        
        // Make uppercase para madaling i-compare
        for (int i = 0; i < option.length(); i++) {
            option[i] = toupper(option[i]);
        }
        
        if (option == "R") {
            break;  // Return to menu
        } else if (!paid_status && option == "M") {
            // Mark a loan as paid
            print_bot_message();
            print_slow("Enter customer name to mark as paid: ");
            string name;
            getline(cin, name);
            
            if (mark_loan_as_paid(name)) {
                // Refresh list kung may loan na-mark as paid
                viewCustomers(paid_status);
                return;
            }
        } else {
            // Try to interpret as a loan number
            try {
                int index = stoi(option) - 1;
                if (index >= 0 && index < valid_indices.size()) {
                    // Show details or allow marking specific loan as paid
                    int customer_index = valid_indices[index];
                    Customer c = all_customers[customer_index];
                    
                    // Display full loan details
                    cout << "\n----------------------------------------";
                    cout << "\nDETAILED LOAN INFORMATION";
                    cout << "\n----------------------------------------";
                    cout << "\nCustomer Name: " << c.name;
                    cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << c.loanAmount;
                    cout << "\nInterest Rate: " << c.interestRate << "%";
                    cout << "\nRepayment Period: " << c.months << " months";
                    cout << "\nCollateral Item: " << c.collateralItem;
                    cout << "\nCollateral Value: PHP " << fixed << setprecision(2) << c.collateralValue;
                    if (c.isPaid) {
                        cout << "\nPayment Status: PAID";
                    } else {
                        cout << "\nPayment Status: UNPAID";
                    }
                    cout << "\nNext Payment Date: " << c.nextPaymentDate.day << "/"
                         << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
                    cout << "\n----------------------------------------\n";
                    
                    // If unpaid, offer to mark as paid
                    if (!paid_status) {
                        print_bot_message();
                        print_slow("Mark this loan as paid? (Y/n): ");
                        string confirm;
                        getline(cin, confirm);
                        
                        if (confirm.empty() || confirm == "y" || confirm == "Y") {
                            if (mark_loan_as_paid(c.name)) {
                                // Refresh list kung may loan na-mark as paid
                                viewCustomers(paid_status);
                                return;
                            }
                        }
                    } else {
                        print_bot_message();
                        print_slow("Press Enter to continue...");
                        cin.get();
                    }
                    
                    break;  // Return to menu after showing details
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

// Mark loan as paid (menu option)
void mark_paid_menu() {
    if (all_customers.size() == 0) {
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
    
    for (int i = 0; i < all_customers.size(); i++) {
        Customer c = all_customers[i];
        if (c.isPaid == false) {
            cout << "\n\n" << counter << ". Name    : " << c.name;
            cout << "\n   Amount  : PHP " << fixed << setprecision(2) << c.loanAmount;
            
            // Format date with leading zeros
            cout << "\n   Due Date: ";
            if (c.nextPaymentDate.day < 10) cout << "0";
            cout << c.nextPaymentDate.day << "/";
            if (c.nextPaymentDate.month < 10) cout << "0";
            cout << c.nextPaymentDate.month << "/" << c.nextPaymentDate.year;
            
            has_unpaid = true;
            counter = counter + 1;
        }
    }
    cout << "\n+--------------------------------+\n";

    if (has_unpaid == false) {
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

// Clear input buffer after numeric input
void clear_input() {
    cin.clear();
    cin.ignore(999999, '\n');
}

// Get valid amount from user
double get_valid_amount(string prompt) {
    double amount;
    while (true) {
        print_bot_message();
        print_slow(prompt);
        
        cin >> amount;
        
        if (cin.fail()) {
            show_error("Error: Please enter a valid number.");
            clear_input();
            continue;
        }
        
        if (amount <= 0) {
            show_error("Error: Amount must be greater than 0.");
            continue;
        }
        
        break;
    }
    clear_input();
    return amount;
}

// Get valid integer from user
int get_valid_integer(string prompt, int min, int max) {
    int value;
    while (true) {
        print_bot_message();
        print_slow(prompt);
        
        cin >> value;
        
        if (cin.fail()) {
            show_error("Error: Please enter a valid number.");
            clear_input();
            continue;
        }
        
        if (value < min || value > max) {
            show_error("Error: Value must be between " + to_string(min) + " and " + to_string(max) + ".");
            continue;
        }
        
        break;
    }
    clear_input();
    return value;
}

// Apply for new loan
void applyForLoan() {
    Customer new_customer;
    clear_screen();
    cout << "\n===========================================";
    cout << "\n           LOAN APPLICATION FORM          ";
    cout << "\n===========================================\n";

    // Name validation
    while (true) {
        print_bot_message();
        print_slow("Enter customer name: ");
        getline(cin, new_customer.name);
        
        if (!check_name(new_customer.name)) {
            show_error("Error: Name must contain only letters, numbers, spaces, underscores, or hyphens.");
            continue;
        }
        
        // Check for duplicate names
        bool duplicate = false;
        for (int i = 0; i < all_customers.size(); i++) {
            if (all_customers[i].name == new_customer.name) {
                duplicate = true;
                break;
            }
        }
        
        if (duplicate) {
            show_error("Error: A customer with this name already exists.");
            continue;
        }
        
        break;
    }
    
    // Loan amount validation
    while (true) {
        new_customer.loanAmount = get_valid_amount("Enter loan amount (PHP): ");
        
        if (new_customer.loanAmount < 1000) {
            show_error("Error: Minimum loan amount is PHP 1,000.");
            continue;
        }
        
        if (new_customer.loanAmount > 1000000) {
            show_error("Error: Maximum loan amount is PHP 1,000,000.");
            continue;
        }
        
        break;
    }
    
    // Repayment period validation
    new_customer.months = get_valid_integer("Enter repayment period (months): ", 3, 60);
    
    // Collateral type validation
    while (true) {
        print_bot_message();
        print_slow("Enter collateral description: ");
        getline(cin, new_customer.collateralItem);
        
        if (new_customer.collateralItem.empty()) {
            print_bot_message();
            print_slow("Error: Collateral description cannot be empty.");
            continue;
        }
        
        if (new_customer.collateralItem.length() < 3) {
            print_bot_message();
            print_slow("Error: Please provide a more detailed description (at least 3 characters).");
            continue;
        }
        
        // Check kung puro spaces lang
        bool only_spaces = true;
        for (int i = 0; i < new_customer.collateralItem.length(); i++) {
            if (!isspace(new_customer.collateralItem[i])) {
                only_spaces = false;
                break;
            }
        }
        
        if (only_spaces) {
            print_bot_message();
            print_slow("Error: Description cannot be only whitespace.");
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
    if (new_customer.loanAmount > 50000) {
        new_customer.interestRate = 6.0;
    } else {
        new_customer.interestRate = 5.0;
    }
    
    new_customer.isPaid = false;
    new_customer.paymentDate = get_current_date();
    new_customer.nextPaymentDate = get_next_payment_date(new_customer.paymentDate);
    double monthly_payment = calculate_monthly_payment(new_customer.loanAmount, new_customer.interestRate, new_customer.months);

    // Display loan summary
    cout << "\n===========================================";
    cout << "\n           LOAN APPROVAL NOTICE           ";
    cout << "\n===========================================";
    cout << "\nCustomer Name: " << new_customer.name;
    cout << "\nLoan Amount: PHP " << fixed << setprecision(2) << new_customer.loanAmount;
    cout << "\nInterest Rate: " << new_customer.interestRate << "%";
    cout << "\nCollateral: " << new_customer.collateralItem;
    cout << "\nCollateral Value: PHP " << fixed << setprecision(2) << new_customer.collateralValue;
    cout << "\n===========================================";

    // Add Payment Terms section
    cout << "\n===========================================";
    cout << "\n           PAYMENT TERMS                  ";
    cout << "\n===========================================";
    cout << "\nMonthly Payment: PHP " << fixed << setprecision(2) << monthly_payment;
    cout << "\nInterest Rate: " << new_customer.interestRate << "%";
    cout << "\nRepayment Period: " << new_customer.months << " months";
    cout << "\n===========================================";

    // Confirmation prompt
    print_bot_message();
    print_slow("Do you accept the loan terms? (Y/n): ");
    string confirm;
    getline(cin, confirm);
    
    // Convert to lowercase
    for (int i = 0; i < confirm.length(); i++) {
        confirm[i] = tolower(confirm[i]);
    }
    
    if (confirm.empty()) {
        confirm = "y";
    }

    if (confirm == "y" || confirm == "yes") {
        all_customers.push_back(new_customer);
        save_customers_to_file();
        print_bot_message();
        print_slow("Loan application successful!");
    } else {
        print_bot_message();
        print_slow("Loan application cancelled.");
    }
}

// Load customers from file
void load_customers_from_file() {
    ifstream file("customers.txt");
    string line;
    
    // Clear existing customers
    all_customers.clear();
    
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
        
        // Last field is collateral value
        c.collateralValue = stod(line);
        
        all_customers.push_back(c);
    }
    
    file.close();
}

// Main function
int main() {
    string choice;
    
    clear_screen();
    print_bot_message();
    print_slow("Initializing Loan Management System...\n");
    this_thread::sleep_for(chrono::milliseconds(1000));
    
    // Try to load existing customers
    load_customers_from_file();

    do {
        show_menu();
        getline(cin, choice);

        if (choice.length() != 1) {
            print_bot_message();
            print_slow("Error: Please enter a number between 1 and 5.");
            continue;
        }
        
        if (!isdigit(choice[0])) {
            print_bot_message();
            print_slow("Error: Please enter a number between 1 and 5.");
            continue;
        }

        int choiceNum = choice[0] - '0';
        
        switch (choiceNum) {
            case 1:
                applyForLoan();
                break;
            case 2:
                viewCustomers(true);
                break;
            case 3:
                viewCustomers(false);
                break;
            case 4:
                mark_paid_menu();
                break;
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