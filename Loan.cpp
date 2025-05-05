#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <fstream>


using namespace std;

const int MAX_NUMBER_OF_CUSTOMERS = 17;

struct Customer {
    string customerName;
    double loanAmount;
    double interestRate;
    int repaymentMonths;
    bool isLoanPaid;
    string collateralItemDescription;
    double collateralValue;
};

Customer customerRecords[MAX_NUMBER_OF_CUSTOMERS];
int totalCustomerCount = 0;

void saveLoansToFile() {
    ofstream outFile("loans.txt");
    for (int i = 0; i < totalCustomerCount; i++) {
        outFile << customerRecords[i].customerName << '\n'
                << customerRecords[i].loanAmount << '\n'
                << customerRecords[i].interestRate << '\n'
                << customerRecords[i].repaymentMonths << '\n'
                << customerRecords[i].isLoanPaid << '\n'
                << customerRecords[i].collateralItemDescription << '\n'
                << customerRecords[i].collateralValue << '\n';
    }
    outFile.close();
}


void loadLoansFromFile() {
    ifstream inFile("loans.txt");
    Customer loadedCustomer;
    while (getline(inFile, loadedCustomer.customerName)) {
        inFile >> loadedCustomer.loanAmount;
        inFile >> loadedCustomer.interestRate;
        inFile >> loadedCustomer.repaymentMonths;
        inFile >> loadedCustomer.isLoanPaid;
        inFile.ignore(); // skip leftover newline
        getline(inFile, loadedCustomer.collateralItemDescription);
        inFile >> loadedCustomer.collateralValue;
        inFile.ignore();

        customerRecords[totalCustomerCount++] = loadedCustomer;
    }
    inFile.close();
}




string convertToLowercase(string inputText) {
    transform(inputText.begin(), inputText.end(), inputText.begin(), ::tolower);
    return inputText;
}

void showHelpMenu() {
    cout << "\nHere are the available commands:\n";
    cout << "  new         - Start a new loan application\n";
    cout << "  view paid   - Show all fully paid loans\n";
    cout << "  view active - Show all active (unpaid) loans\n";
    cout << "  mark paid   - Mark a specific loan as paid\n";
    cout << "  help        - Show this help message again\n";
    cout << "  exit        - Exit the chatbot\n";
}



void showLoanSummary(const Customer& selectedCustomer) {
//                                ^      
// gamiting reference yung customer struct
    double totalInterestAmount = selectedCustomer.loanAmount * selectedCustomer.interestRate / 100;
    double totalRepaymentAmount = selectedCustomer.loanAmount + totalInterestAmount;
    double monthlyInstallment = totalRepaymentAmount / selectedCustomer.repaymentMonths;

    cout << "\nHere's your loan summary:\n";
    cout << "--------------------------------------------\n";
    cout << "Customer Name     : " << selectedCustomer.customerName << "\n";
    cout << "Loan Amount       : PHP " << fixed << setprecision(2) << selectedCustomer.loanAmount << "\n";
    cout << "Interest Rate     : " << selectedCustomer.interestRate << "%\n";
    cout << "Collateral        : " << selectedCustomer.collateralItemDescription 
         << " (PHP " << selectedCustomer.collateralValue << ")\n";
    cout << "Repayment Period  : " << selectedCustomer.repaymentMonths << " months\n";
    cout << "Monthly Payment   : PHP " << monthlyInstallment << "\n";
    cout << "Total Interest    : PHP " << totalInterestAmount << "\n";
    cout << "Total Payment     : PHP " << totalRepaymentAmount << "\n";
    cout << "--------------------------------------------\n";

    cout << "Here's how your payment breakdown looks:\n";
    cout << "+--------+----------+----------+-----------+-----------+\n";
    cout << "| Month  | Payment  | Interest | Principal | Remaining |\n";
    cout << "+--------+----------+----------+-----------+-----------+\n";

    double remainingBalance = totalRepaymentAmount;
    for (int month = 1; month <= selectedCustomer.repaymentMonths; month++) {
        double monthlyInterest = totalInterestAmount / selectedCustomer.repaymentMonths;
        double principalPayment = monthlyInstallment - monthlyInterest;
        remainingBalance -= monthlyInstallment;
        if (remainingBalance < 0) remainingBalance = 0;

        cout << "| " << setw(6) << month << " | "
             << setw(8) << monthlyInstallment << " | "
             << setw(8) << monthlyInterest << " | "
             << setw(9) << principalPayment << " | "
             << setw(9) << remainingBalance << " |\n";

        if (selectedCustomer.repaymentMonths > 12 && month == 6) {
            cout << "|   ... skipping middle months for clarity ...       |\n";
            month = selectedCustomer.repaymentMonths - 6;
        }
    }
    cout << "+--------+----------+----------+-----------+-----------+\n";
}

void applyNewLoan() {
    if (totalCustomerCount >= MAX_NUMBER_OF_CUSTOMERS) {
        cout << "Sorry, we've reached our limit of customers for now.\n";
        return;
    }

    Customer newCustomer;
    cout << "\nLet's begin your loan application.\n";
    cout << "What's your full name? ";
    getline(cin, newCustomer.customerName);

    if (newCustomer.customerName.empty()) {
        cout << "Name cannot be empty.\n";
        return;
    }

    for (int customerIndex = 0; customerIndex < totalCustomerCount; customerIndex++) {
        if (customerRecords[customerIndex].customerName == newCustomer.customerName) {
            cout << "A customer with this name already exists.\n";
            return;
        }
    }

    cout << "Enter your desired loan amount (PHP): ";
    cin >> newCustomer.loanAmount;
    cin.ignore();
    if (newCustomer.loanAmount < 1000 || newCustomer.loanAmount > 500000) {
        cout << "Loan should be between PHP 1,000 and PHP 500,000.\n";
        return;
    }

    cout << "For how many months do you want to repay? ";
    cin >> newCustomer.repaymentMonths;
    cin.ignore();
    if (newCustomer.repaymentMonths < 3 || newCustomer.repaymentMonths > 24) {
        cout << "Repayment must be between 3 and 24 months.\n";
        return;
    }

    cout << "Describe your collateral item: ";
    getline(cin, newCustomer.collateralItemDescription);

    cout << "What is the value of your collateral (PHP)? ";
    cin >> newCustomer.collateralValue;
    cin.ignore();
    if (newCustomer.collateralValue <= newCustomer.loanAmount) {
        cout << "Collateral must be worth more than the loan amount.\n";
        return;
    }

    newCustomer.interestRate = (newCustomer.loanAmount > 50000) ? 3.0 : 5.0;
    newCustomer.isLoanPaid = false;

    showLoanSummary(newCustomer);

    cout << "Do you accept these loan terms? (Y/N): ";
    string confirmationResponse;
    getline(cin, confirmationResponse);

    if (confirmationResponse == "Y" || confirmationResponse == "y") {
        customerRecords[totalCustomerCount++] = newCustomer;
        saveLoansToFile();
        cout << "Your loan has been added successfully.\n";
    } else {
        cout << "Loan application has been canceled.\n";
    }
}

void showPaidLoans() {
    cout << "\nList of paid loans:\n";
    bool hasPaidLoans = false;
    for (int customerIndex = 0; customerIndex < totalCustomerCount; customerIndex++) {
        if (customerRecords[customerIndex].isLoanPaid) {
            cout << "- " << customerRecords[customerIndex].customerName << ": PHP "
                 << fixed << setprecision(2) << customerRecords[customerIndex].loanAmount << "\n";
            hasPaidLoans = true;
        }
    }
    if (!hasPaidLoans) {
        cout << "No loans have been paid yet.\n";
    }
}

void showUnpaidLoans() {
    cout << "\nList of active (unpaid) loans:\n";
    bool hasUnpaidLoans = false;
    for (int customerIndex = 0; customerIndex < totalCustomerCount; customerIndex++) {
        if (!customerRecords[customerIndex].isLoanPaid) {
            cout << "- " << customerRecords[customerIndex].customerName << ": PHP "
                 << fixed << setprecision(2) << customerRecords[customerIndex].loanAmount << "\n";
            hasUnpaidLoans = true;
        }
    }
    if (!hasUnpaidLoans) {
        cout << "All loans have been paid. Great job!\n";
    }
}

void markLoanAsPaid() {
    cout << "\nSelect a loan to mark as paid:\n";
    int unpaidLoanIndexMap[MAX_NUMBER_OF_CUSTOMERS];
    int unpaidLoanCount = 0;

    for (int customerIndex = 0; customerIndex < totalCustomerCount; customerIndex++) {
        if (!customerRecords[customerIndex].isLoanPaid) {
            unpaidLoanIndexMap[unpaidLoanCount] = customerIndex;
            cout << "[" << unpaidLoanCount + 1 << "] " << customerRecords[customerIndex].customerName
                 << " - PHP " << fixed << setprecision(2) << customerRecords[customerIndex].loanAmount << "\n";
            unpaidLoanCount++;
        }
    }

    if (unpaidLoanCount == 0) {
        cout << "No unpaid loans to mark.\n";
        return;
    }

    cout << "Enter the number of the loan to mark as paid (0 to cancel): ";
    int selectedLoanNumber;
    cin >> selectedLoanNumber;
    cin.ignore();

    if (selectedLoanNumber == 0) {
        cout << "No changes made.\n";
        return;
    }

    if (selectedLoanNumber < 1 || selectedLoanNumber > unpaidLoanCount) {
        cout << "Invalid selection.\n";
        return;
    }

    int loanIndexToMark = unpaidLoanIndexMap[selectedLoanNumber - 1];
    customerRecords[loanIndexToMark].isLoanPaid = true;
    saveLoansToFile();
    cout << "Loan has been marked as paid.\n";
}

int main() {
    loadLoansFromFile(); 
    string userCommand;
    cout << "Hello! I'm LoanMate — your friendly loan assistant.\n";
    cout << "Type 'help' to see what I can do!\n";

    while (true) {
        cout << "\nWhat would you like to do? > ";
        getline(cin, userCommand);

        string lowercaseCommand = convertToLowercase(userCommand);

        if (lowercaseCommand.find("new") != string::npos) {
            applyNewLoan();
        } else if (lowercaseCommand.find("paid") != string::npos && lowercaseCommand.find("mark") == string::npos) {
            showPaidLoans();
        } else if (lowercaseCommand.find("active") != string::npos || lowercaseCommand.find("unpaid") != string::npos) {
            showUnpaidLoans();
        } else if (lowercaseCommand.find("mark") != string::npos) {
            markLoanAsPaid();
        } else if (lowercaseCommand.find("help") != string::npos) {
            showHelpMenu();
        } else if (lowercaseCommand.find("exit") != string::npos || lowercaseCommand.find("quit") != string::npos) {
            cout << "Goodbye! Thanks for using LoanMate.\n";
            saveLoansToFile(); 
            break;
        } else {
            cout << "Sorry, I didn't understand that. Try 'new', 'paid', or 'help'.\n";
        }
    }

    return 0;
}
