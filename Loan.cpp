#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;



struct Customer {
    string customerName;
    double loanAmount;
    double interestRate;
    int repaymentMonths;
    bool isLoanPaid;
    string collateralItemDescription;
    double collateralValue;
    string applicationDate; 
};


vector<Customer> customerRecords;

string addMonthsToDate(string dateStr, int monthsToAdd, int day = 15) {
    int year = stoi(dateStr.substr(0, 4));
    int month = stoi(dateStr.substr(5, 2));

    month += monthsToAdd;
    year += (month - 1) / 12;
    month = ((month - 1) % 12) + 1;

    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
    return string(buffer);
}



void saveLoansToFile() {
    ofstream outFile("savedLoans.txt");
    for (const Customer& c : customerRecords) {
        outFile << c.customerName << '\n'
                << c.loanAmount << '\n'
                << c.interestRate << '\n'
                << c.repaymentMonths << '\n'
                << c.isLoanPaid << '\n'
                << c.collateralItemDescription << '\n'
                << c.collateralValue << '\n'
                << c.applicationDate << '\n';
    }    
    outFile.close();
}


void loadLoansFromFile() {
    ifstream inFile("savedLoans.txt");
    Customer loadedCustomer;
    while (getline(inFile, loadedCustomer.customerName)) {
        inFile >> loadedCustomer.loanAmount;
        inFile >> loadedCustomer.interestRate;
        inFile >> loadedCustomer.repaymentMonths;
        inFile >> loadedCustomer.isLoanPaid;
        inFile.ignore();
        getline(inFile, loadedCustomer.collateralItemDescription);
        inFile >> loadedCustomer.collateralValue;
        getline(inFile, loadedCustomer.applicationDate);
        inFile.ignore();

        customerRecords.push_back(loadedCustomer);

    }
    inFile.close();
}


void generateCustomerTransactionFile(const Customer& customer,
    double totalInterest,
    double totalRepayment,
    double monthlyPayment) {

    // gamitin ung name ng user para gawing filename
    string fileName = customer.customerName;
    replace(fileName.begin(), fileName.end(), ' ', '_');
    fileName += ".txt";

    ofstream outFile(fileName);
    if (!outFile) {
    cout << "Error: Couldn't create transaction file for " << customer.customerName << ".\n";
    return;
    }


    outFile << "+----------------------------------------------------------+\n";
    outFile << "|                  LOAN TRANSACTION SUMMARY                |\n";
    outFile << "+----------------------------------------------------------+\n";
    outFile << "| Customer Name     : " << setw(37) << left << customer.customerName << "|\n";
    outFile << "| Application Date  : " << setw(37) << left << customer.applicationDate << "|\n";
    outFile << "| Loan Amount       : PHP " << setw(33) << fixed << setprecision(2) << customer.loanAmount << "|\n";
    outFile << "| Interest Rate     : " << setw(37) << left << (to_string(customer.interestRate) + "%") << "|\n";
    outFile << "| Collateral        : " << setw(37) << left 
    << (customer.collateralItemDescription + " (PHP " + to_string((int)customer.collateralValue) + ")") << "|\n";
    outFile << "| Repayment Period  : " << setw(37) << left << (to_string(customer.repaymentMonths) + " months") << "|\n";
    outFile << "| Monthly Payment   : PHP " << setw(33) << monthlyPayment << "|\n";
    outFile << "| Total Interest    : PHP " << setw(33) << totalInterest << "|\n";
    outFile << "| Total Repayment   : PHP " << setw(33) << totalRepayment << "|\n";
    outFile << "+----------------------------------------------------------+\n\n";


    outFile << "+----------------------------------------------------------+\n";
    outFile << "|                     PAYMENT SCHEDULE                     |\n";
    outFile << "+------------+----------+----------+-----------+-----------+\n";
    outFile << "| Due Date   | Payment  | Interest | Principal | Remaining |\n";
    outFile << "+------------+----------+----------+-----------+-----------+\n";
    
    double remaining = totalRepayment;
    for (int m = 1; m <= customer.repaymentMonths; m++) {
        double monthlyInterest = totalInterest / customer.repaymentMonths;
        double principal = monthlyPayment - monthlyInterest;
        remaining -= monthlyPayment;
        if (remaining < 0) remaining = 0;
    
        string dueDate = addMonthsToDate(customer.applicationDate, m);
    
        outFile << "| " << std::left << std::setw(10) << dueDate << " | "
                << std::right << std::setw(8) << std::fixed << std::setprecision(2) << monthlyPayment << " | "
                << std::setw(8) << monthlyInterest << " | "
                << std::setw(9) << principal << " | "
                << std::setw(9) << remaining << " |\n";
    
        if (customer.repaymentMonths > 12 && m == 6) {
            outFile << "|   ... skipping middle months for clarity ...           |\n";
            m = customer.repaymentMonths - 6;
        }
    }
    
    outFile << "+------------+----------+----------+-----------+-----------+\n";


    outFile << "\n+----------------------------------------------------------+\n";
    outFile << "|                          NOTICE                          |\n";
    outFile << "|      Failure to repay  the loan in full within the       |\n";
    outFile << "|      agreed  repayment  period  will result in the       |\n";
    outFile << "|      forfeiture of the collateral item. The lender       |\n";
    outFile << "|      reserves the right to claim full ownership of       |\n";
    outFile << "|      the pledged collateral in accordance with the       |\n";
    outFile << "|      loan agreement.                                     |\n";
    outFile << "+----------------------------------------------------------+\n"; 

    outFile.close();
    cout << "Transaction record saved to \"" << fileName << "\".\n";
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
    double totalInterestAmount = selectedCustomer.loanAmount * selectedCustomer.interestRate / 100;
    double totalRepaymentAmount = selectedCustomer.loanAmount + totalInterestAmount;
    double monthlyInstallment = totalRepaymentAmount / selectedCustomer.repaymentMonths;

    cout << "\n+----------------------------------------------------------+";
    cout << "\nHere's your loan summary:\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "Customer Name     : " << selectedCustomer.customerName << "\n";
    cout << "Loan Amount       : PHP " << fixed << setprecision(2) << selectedCustomer.loanAmount << "\n";
    cout << "Interest Rate     : " << selectedCustomer.interestRate << "%\n";
    cout << "Collateral        : " << selectedCustomer.collateralItemDescription 
            << " (PHP " << selectedCustomer.collateralValue << ")\n";
    cout << "Repayment Period  : " << selectedCustomer.repaymentMonths << " months\n";
    cout << "Monthly Payment   : PHP " << monthlyInstallment << "\n";
    cout << "Total Interest    : PHP " << totalInterestAmount << "\n";
    cout << "Total Payment     : PHP " << totalRepaymentAmount << "\n";
    cout << "+----------------------------------------------------------+\n";

    cout << "\nHere's how your payment breakdown looks:\n";
    cout << "+------------+----------+----------+-----------+-----------+\n";
    cout << "|  Due Date  | Payment  | Interest | Principal | Remaining |\n";
    cout << "+------------+----------+----------+-----------+-----------+\n";
    

    double remainingBalance = totalRepaymentAmount;
    for (int month = 1; month <= selectedCustomer.repaymentMonths; month++) {
        double monthlyInterest = totalInterestAmount / selectedCustomer.repaymentMonths;
        double principalPayment = monthlyInstallment - monthlyInterest;
        remainingBalance -= monthlyInstallment;
        if (remainingBalance < 0) remainingBalance = 0;

        string dueDate = addMonthsToDate(selectedCustomer.applicationDate, month);
        cout << "| " << setw(9) << dueDate << " | "
            << setw(8) << monthlyInstallment << " | "
            << setw(8) << monthlyInterest << " | "
            << setw(9) << principalPayment << " | "
            << setw(9) << remainingBalance << " |\n";

        if (selectedCustomer.repaymentMonths > 12 && month == 6) {
            cout << "|   ... skipping middle months for clarity ...       |\n";
            month = selectedCustomer.repaymentMonths - 6;
        }
    }
    cout << "+------------+----------+----------+-----------+-----------+\n";
    
    cout << "\n+----------------------------------------------------------+\n";
    cout << "|                          NOTICE                          |\n";
    cout << "|      Failure to repay  the loan in full within the       |\n";
    cout << "|      agreed  repayment  period  will result in the       |\n";
    cout << "|      forfeiture of the collateral item. The lender       |\n";
    cout << "|      reserves the right to claim full ownership of       |\n";
    cout << "|      the pledged collateral in accordance with the       |\n";
    cout << "|      loan agreement.                                     |\n";
    cout << "+----------------------------------------------------------+\n"; 

}

bool isValidLoanAmount(double amount) {
    return amount >= 1000 && amount <= 500000;
}


void applyNewLoan() {

    Customer newCustomer;
    cout << "\nGreat! Let's begin your loan application.\n";

    cout << "Can you tell me your full name? ";
    getline(cin, newCustomer.customerName);

    if (newCustomer.customerName.empty()) {
        cout << "Name cannot be empty. Let's try again next time.\n";
        return;
    }


    for (const Customer& c : customerRecords) {
        if (c.customerName == newCustomer.customerName) {
            cout << "It looks like a customer with this name already exists.\n";
            return;
        }
    }

    cout << "Nice to meet you, " << newCustomer.customerName << ".\n";
    cout << "How much would you like to borrow (PHP)? ";
    cin >> newCustomer.loanAmount;
    cin.ignore();

    if (!isValidLoanAmount(newCustomer.loanAmount)) {
        cout << "Oops - the loan amount should be between PHP 1,000 and PHP 500,000.\n";
        return;
    }

    cout << "Over how many months would you like to repay the loan? ";
    string monthsInput;
    getline(cin, monthsInput);


    size_t numberStart = monthsInput.find_first_of("0123456789");
    if (numberStart == string::npos) {
        cout << "Sorry, I couldn't find a number in your input.\n";
        return;
    }

    size_t numberEnd = monthsInput.find_first_not_of("0123456789", numberStart);
    string numberStr = monthsInput.substr(numberStart, numberEnd - numberStart);

    newCustomer.repaymentMonths = stoi(numberStr);

    if (newCustomer.repaymentMonths < 3 || newCustomer.repaymentMonths > 24) {
        cout << "Repayment terms must be between 3 and 24 months.\n";
        return;
    }

    

    cout << "Can you describe the item you're offering as collateral? ";
    getline(cin, newCustomer.collateralItemDescription);

    cout << "And what's the estimated value of that item (PHP)? ";
    cin >> newCustomer.collateralValue;
    cin.ignore();

    if (newCustomer.collateralValue <= newCustomer.loanAmount) {
        cout << "To proceed, the collateral value must be greater than the loan amount.\n";
        return;
    }

    cout << "Lastly, what is today's date or the date of your loan application? (YYYY-MM-DD): ";
    getline(cin, newCustomer.applicationDate);


    newCustomer.interestRate = (newCustomer.loanAmount > 50000) ? 3.0 : 5.0;
    newCustomer.isLoanPaid = false;


    showLoanSummary(newCustomer);

    cout << "Do you accept these loan terms? (Y/N): ";
    string confirmationResponse;
    getline(cin, confirmationResponse);

    if (confirmationResponse == "Y" || confirmationResponse == "y") {
        customerRecords.push_back(newCustomer);

        saveLoansToFile();

        cout << "Awesome! Your loan has been recorded successfully.\n";

        double totalInterest = newCustomer.loanAmount * newCustomer.interestRate / 100;
        double totalRepayment = newCustomer.loanAmount + totalInterest;
        double monthlyPayment = totalRepayment / newCustomer.repaymentMonths;

        generateCustomerTransactionFile(newCustomer, totalInterest, totalRepayment, monthlyPayment);

    } else {
        cout << "No worries - your loan application has been canceled.\n";
    }
}


void showPaidLoans() {
    cout << "\nList of paid loans:\n";
    bool hasPaidLoans = false;
    for (const Customer& c : customerRecords) {
        if (c.isLoanPaid) {
            cout << "- " << c.customerName << ": PHP "
                    << fixed << setprecision(2) << c.loanAmount << "\n";

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
    for (const Customer& c : customerRecords) {
        if (!c.isLoanPaid) {
            cout << "- " << c.customerName << ": PHP "
                    << fixed << setprecision(2) << c.loanAmount << "\n";

            hasUnpaidLoans = true;
        }
    }
    
    
    if (!hasUnpaidLoans) {
        cout << "All loans have been paid. Great job!\n";
    }
}

void markLoanAsPaid() {
    cout << "\nSelect a loan to mark as paid:\n";
    vector<int> unpaidLoanIndexMap;

    for (size_t i = 0; i < customerRecords.size(); i++) {
        if (!customerRecords[i].isLoanPaid) {
            unpaidLoanIndexMap.push_back(i);
            cout << "[" << unpaidLoanIndexMap.size() << "] "
                << customerRecords[i].customerName << " - PHP "
                << fixed << setprecision(2) << customerRecords[i].loanAmount << "\n";
        }
    }


    if (unpaidLoanIndexMap.size() == 0) {
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

    if (selectedLoanNumber < 1 || selectedLoanNumber > unpaidLoanIndexMap.size()) {
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
    cout << "Hello! I'm LoanMate - your friendly loan assistant.\n";
    cout << "Type 'help' to see what I can do!\n";

    while (true) {
        cout << "\nWhat would you like to do? > ";
        getline(cin, userCommand);

        string lowercaseCommand = convertToLowercase(userCommand);

        if (lowercaseCommand.find("apply") != string::npos || lowercaseCommand.find("loan") != string::npos) {
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
            cout << "Sorry, I didn't understand: \"" << userCommand << "\". Try typing 'help' to see valid commands.\n";
        }
    }

    return 0;
}
 