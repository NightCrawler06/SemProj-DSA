#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>


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

stack<Customer> paidLoanUndoStack;
queue<Customer> pendingLoanApplications;
vector<Customer> customerRecords;
double companyFundsAvailable = 10000000.0; 


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

    customerRecords.clear();  // clear any existing loaded data
    companyFundsAvailable = 10000000.0; // reset base funds

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

        // Subtract approved (unpaid) loans only
        if (!loadedCustomer.isLoanPaid) {
            companyFundsAvailable -= loadedCustomer.loanAmount;
        }
    }

    inFile.close();

    // Protect against invalid loan data
    if (companyFundsAvailable < 0) {
        cout << "Warning: Loan amounts exceeded available funds. Setting balance to zero.\n";
        companyFundsAvailable = 0;
    }
}




void generateCustomerReceipt(const Customer& customer,
    double totalInterest,
    double totalRepayment,
    double monthlyPayment) {


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
    cout << "\n========== LOANMATE COMMAND LIST ==========\n";
    
    cout << "\n-- Loan Application Commands --\n";
    cout << "  new             - Begin a new loan application\n";
    cout << "  review          - Approve or decline pending applications\n";

    cout << "\n-- Loan Status & Actions --\n";
    cout << "  view paid       - List all paid loans\n";
    cout << "  view active     - List all unpaid loans\n";
    cout << "  mark paid       - Mark a loan as fully paid\n";
    cout << "  undo            - Undo the last loan marked as paid\n";

    cout << "\n-- Info & Queries --\n";
    cout << "  help            - Show this help menu\n";
    cout << "  exit            - Save and quit the program\n";
    cout << "\n-- You can also ask questions like --\n";
    cout << "  > Who owes money?\n";
    cout << "  > What's the highest loan?\n";
    cout << "  > Show loans with 'vehicle' as collateral\n";
    cout << "  > Company funds status\n";

    cout << "\n===========================================\n";
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
    return amount >= 1000 && amount <= 10000000;
}


void applyNewLoan() {
    Customer newCustomer;
    cout << "\nSure thing! We'll walk through your loan application step-by-step.\n";
    cout << "No pressure - just answer as best as you can, and I'll do the rest!\n\n";

    cout << "First, may I have your full name? ";
    getline(cin, newCustomer.customerName);

    if (newCustomer.customerName.empty()) {
        cout << "Name cannot be empty. Let's try again another time.\n";
        return;
    }

    for (const Customer& c : customerRecords) {
        if (c.customerName == newCustomer.customerName) {
            cout << "It looks like a customer with this name already exists.\n";
            return;
        }
    }

    cout << "\nGreat, " << newCustomer.customerName << ".\n";
    cout << "Let's talk numbers. How much money are you hoping to borrow today (in PHP)? ";
    cin >> newCustomer.loanAmount;
    cin.ignore();

    if (!isValidLoanAmount(newCustomer.loanAmount)) {
        cout << "Hmm, that amount seems outside our allowed range.\n";
        cout << "We currently offer loans from PHP 1,000 up to PHP 10,000,000.\n";
        return;
    }

    cout << "\nOver how many months would you feel comfortable repaying the loan?\n";
    cout << "(We offer repayment terms between 3 and 24 months): ";
    string monthsInput;
    getline(cin, monthsInput);

    size_t numberStart = monthsInput.find_first_of("0123456789");
    if (numberStart == string::npos) {
        cout << "I didn't quite catch a valid number of months. Please try again like '12 months'.\n";
        return;
    }

    size_t numberEnd = monthsInput.find_first_not_of("0123456789", numberStart);
    string numberStr = monthsInput.substr(numberStart, numberEnd - numberStart);
    newCustomer.repaymentMonths = stoi(numberStr);

    if (newCustomer.repaymentMonths < 3 || newCustomer.repaymentMonths > 24) {
        cout << "Repayment terms must be between 3 and 24 months.\n";
        return;
    }

    cout << "\nTo help secure your loan, can you describe the item you're offering as collateral?\n";
    getline(cin, newCustomer.collateralItemDescription);
    if (newCustomer.collateralItemDescription.empty()) {
        cout << "Collateral description cannot be empty.\n";
        return;
    }



    cout << "What's the estimated value of that item? (PHP): ";
    cin >> newCustomer.collateralValue;
    cin.ignore();

    if (newCustomer.collateralValue <= newCustomer.loanAmount) {
        cout << "To proceed, the collateral value must be greater than the loan amount.\n";
        return;
    }

    cout << "\nAlmost done! When are you applying for this loan? (Use format YYYY-MM-DD): ";
    getline(cin, newCustomer.applicationDate);

    if (newCustomer.applicationDate.size() != 10 || newCustomer.applicationDate[4] != '-' || newCustomer.applicationDate[7] != '-') {
        cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        return;
    }


    newCustomer.interestRate = (newCustomer.loanAmount > 50000) ? 3.0 : 5.0;
    newCustomer.isLoanPaid = false;

    cout << "\nThanks for that. Here's a quick summary of what we've discussed:\n";
    showLoanSummary(newCustomer);

    cout << "Does everything look good to you? Would you like to submit this application? (Y/N): ";
    string confirmationResponse;
    getline(cin, confirmationResponse);

    if (confirmationResponse == "Y" || confirmationResponse == "y") {
        pendingLoanApplications.push(newCustomer);
        cout << "Thank you! Your loan application has been submitted for review.\n";
    } else {
        cout << "No problem - your loan application has been canceled.\n";
    }
}


void reviewPendingApplications() {
    if (pendingLoanApplications.empty()) {
        cout << "\nNo pending loan applications.\n";
        return;
    }

    int totalApplications = pendingLoanApplications.size();
    int currentIndex = 1;

    while (!pendingLoanApplications.empty()) {
        Customer selected = pendingLoanApplications.front();
        pendingLoanApplications.pop();

        cout << "\nReviewing application " << currentIndex << " of " << totalApplications << ":\n";
        showLoanSummary(selected);

        cout << "Approve this loan? (Y/N): ";
        string decision;
        getline(cin, decision);

        if (decision == "Y" || decision == "y") {
            if (selected.loanAmount > companyFundsAvailable) {
                cout << "Insufficient funds. Cannot approve this loan.\n";
            } else {
                customerRecords.push_back(selected);
                companyFundsAvailable -= selected.loanAmount;
                saveLoansToFile();

                double totalInterest = selected.loanAmount * selected.interestRate / 100;
                double totalRepayment = selected.loanAmount + totalInterest;
                double monthlyPayment = totalRepayment / selected.repaymentMonths;

                generateCustomerReceipt(selected, totalInterest, totalRepayment, monthlyPayment);
                cout << "Loan approved and recorded.\n";
            }
        } else {
            cout << "Loan was declined.\n";
        }

        currentIndex++;
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

    paidLoanUndoStack.push(customerRecords[loanIndexToMark]);

    customerRecords[loanIndexToMark].isLoanPaid = true;
    saveLoansToFile();


    cout << "Loan has been marked as paid.\n";
}


void undoLastPaidLoan() {
    if (paidLoanUndoStack.empty()) {
        cout << "No undoable actions available.\n";
        return;
    }

    Customer last = paidLoanUndoStack.top();
    paidLoanUndoStack.pop();

    for (Customer& c : customerRecords) {
        if (c.customerName == last.customerName && c.isLoanPaid) {
            c.isLoanPaid = false;
            saveLoansToFile();
            cout << "Undo successful: Loan for " << c.customerName << " marked as unpaid.\n";
            return;
        }
    }

    cout << "Could not undo the last action.\n";
}



void functionForAnswering(const string& command) {
    string lowercaseCommand = convertToLowercase(command);

    if (lowercaseCommand.find("most loan") != string::npos || lowercaseCommand.find("highest loan") != string::npos) {
        if (customerRecords.empty()) {
            cout << "No loan records available.\n";
            return;
        }
        auto it = max_element(customerRecords.begin(), customerRecords.end(), 
            [](const Customer& a, const Customer& b) {
                return a.loanAmount < b.loanAmount;
            });
        cout << "Customer with the highest loan is: " << it->customerName 
             << " - PHP " << fixed << setprecision(2) << it->loanAmount << "\n";

    } else if (lowercaseCommand.find("least loan") != string::npos || lowercaseCommand.find("smallest loan") != string::npos) {
        if (customerRecords.empty()) {
            cout << "No loan records available.\n";
            return;
        }
        auto it = min_element(customerRecords.begin(), customerRecords.end(), 
            [](const Customer& a, const Customer& b) {
                return a.loanAmount < b.loanAmount;
            });
        cout << "Customer with the smallest loan is: " << it->customerName 
             << " - PHP " << fixed << setprecision(2) << it->loanAmount << "\n";

    } else if (lowercaseCommand.find("collateral") != string::npos) {
        string keyword;
        size_t pos = lowercaseCommand.find("with ");
        if (pos != string::npos) {
            keyword = lowercaseCommand.substr(pos + 5);
            size_t quote = keyword.find("'");
            if (quote != string::npos) {
                keyword = keyword.substr(quote + 1);
                keyword = keyword.substr(0, keyword.find("'"));
            } else {
                keyword = keyword.substr(0, keyword.find(" "));
            }
            keyword = convertToLowercase(keyword);
            cout << "Searching for collateral containing: '" << keyword << "'\n";
        } else {
            cout << "Enter the keyword to search in collateral (e.g. house, car): ";
            getline(cin, keyword);
            keyword = convertToLowercase(keyword);
        }

        bool found = false;
        for (const Customer& c : customerRecords) {
            if (convertToLowercase(c.collateralItemDescription).find(keyword) != string::npos) {
                cout << "- " << c.customerName << ": " << c.collateralItemDescription << " (PHP "
                     << fixed << setprecision(2) << c.collateralValue << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No customers found with collateral related to '" << keyword << "'.\n";
        }

    } else if (
        lowercaseCommand.find("doesn't pay") != string::npos || 
        lowercaseCommand.find("hasn't paid") != string::npos || 
        lowercaseCommand.find("not paid") != string::npos || 
        lowercaseCommand.find("unpaid") != string::npos
    ) {
        bool found = false;
        for (const Customer& c : customerRecords) {
            if (!c.isLoanPaid) {
                cout << "- " << c.customerName << ": PHP " << fixed << setprecision(2) << c.loanAmount << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "All customers have paid their loans.\n";
        }

    } else if (
        lowercaseCommand.find("company") != string::npos ||
        (lowercaseCommand.find("balance") != string::npos ||
         lowercaseCommand.find("funds") != string::npos ||
         lowercaseCommand.find("money") != string::npos)
    ) {
        cout << "The company currently has PHP " << fixed << setprecision(2) << companyFundsAvailable << " available for lending.\n";
    } else {
        cout << "I'm not sure how to answer that. Try asking about 'most loan', 'collateral', or 'who doesn't pay'.\n";
    }
}


int main() {
    loadLoansFromFile(); 
    string userCommand;
    cout << "Hello! I'm LoanMate - your friendly loan assistant.\n";
    cout << "Type 'help' to see what I can do!\n";

    while (true) {
        cout << "\n[LoanMate]> ";
        getline(cin, userCommand);
        string lowercaseCommand = convertToLowercase(userCommand);

        if (lowercaseCommand.find("apply") != string::npos || lowercaseCommand.find("borrow") != string::npos) {
            applyNewLoan();
        } else if (lowercaseCommand.find("active") != string::npos || lowercaseCommand.find("unpaid") != string::npos) {
            showUnpaidLoans();
        } else if (lowercaseCommand.find("mark") != string::npos) {
            markLoanAsPaid();
        } else if (lowercaseCommand.find("paid") != string::npos ) {
            showPaidLoans();
        } else if (lowercaseCommand.find("undo") != string::npos) {
            undoLastPaidLoan();
        } else if (lowercaseCommand.find("help") != string::npos) {
            showHelpMenu();
        } else if (
            lowercaseCommand.find("who") != string::npos ||
            lowercaseCommand.find("has") != string::npos ||
            lowercaseCommand.find("collateral") != string::npos ||
            lowercaseCommand.find("company") != string::npos ||
            lowercaseCommand.find("money") != string::npos ||  
            lowercaseCommand.find("funds") != string::npos ||  
            lowercaseCommand.find("owe") != string::npos ||
            lowercaseCommand.find("unpaid") != string::npos ||
            lowercaseCommand.find("how much") != string::npos
        ) {
            functionForAnswering(userCommand);
        } else if (lowercaseCommand.find("review") != string::npos) {
            reviewPendingApplications();    
        } else if (lowercaseCommand.find("hi") != string::npos ||
            lowercaseCommand.find("hello") != string::npos ||
            lowercaseCommand.find("hey") != string::npos ||
            lowercaseCommand.find("good morning") != string::npos ||
            lowercaseCommand.find("good afternoon") != string::npos ||
            lowercaseCommand.find("good evening") != string::npos) {
            cout << "Hi there! How can I help you with loans today?\n";
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