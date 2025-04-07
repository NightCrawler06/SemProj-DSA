#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct User {
    string name;
    double dailyIncome;
    double weeklyIncome;
    double monthlyIncome;
    double totalExpenses;
    double totalSavings;
    double totalNeeds;
    double totalWants;
    double totalDebt;
    double totalInvestments;
    vector<pair<string, double>> needs;  // para ma store und needs at ung expenses
    vector<pair<string, double>> wants;  // para ma store und wants at ung expenses
};

map<string, int> monthsDays = {
    {"January", 31},
    {"February", 28},
    {"March", 31},
    {"April", 30},
    {"May", 31},
    {"June", 30},
    {"July", 31},
    {"August", 31},
    {"September", 30},
    {"October", 31},
    {"November", 30},
    {"December", 31}
};

void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double getValidNumberInput() {
    double value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input, please enter a valid number.\n";
            clearBuffer();
        } else {
            clearBuffer();
            return value;
        }
    }
}

string getValidTextInput(string prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. Please try again.\n";
        } else {
            return input;
        }
    }
}

void trackUserIncome(User &user) {
    cout << "\nEnter daily income in PHP: ";
    user.dailyIncome = getValidNumberInput();
    user.weeklyIncome = user.dailyIncome * 7;
    user.monthlyIncome = user.dailyIncome * 30;
    cout << "Income tracked successfully!\n";
}

void trackUserExpenses(User &user) {
    cout << "\n************************ Track Your Expenses ************************\n";
    cout << "* Let's track your monthly expenses.                                   *\n";
    cout << "* Please enter your expenses below.                                    *\n";
    cout << "***********************************************************************\n";

    // para sa Needs
    cout << "\n-------------------- Needs --------------------\n";
    int numNeeds;
    cout << "Enter the number of needs: ";
    while (true) {
        cin >> numNeeds;
        clearBuffer();
        if (numNeeds < 0) {
            cout << "Number of needs cannot be negative. Please enter a valid number.\n";
        } else {
            break;
        }
    }

    if (numNeeds > 0) {
        for (int i = 0; i < numNeeds; ++i) {
            string need;
            double expense;
            cout << "\nEnter name of need " << (i + 1) << ": ";
            getline(cin, need);
            cout << "Enter expense for " << need << ": PHP ";
            expense = getValidNumberInput();
            user.needs.push_back(make_pair(need, expense));
            user.totalNeeds += expense;
        }
    } else {
        cout << "No needs entered.\n";
    }

    // para sa Wants
    cout << "\n-------------------- Wants --------------------\n";
    int numWants;
    cout << "Enter the number of wants: ";
    while (true) {
        cin >> numWants;
        clearBuffer();
        if (numWants < 0) {
            cout << "Number of wants cannot be negative. Please enter a valid number.\n";
        } else {
            break;
        }
    }

    if (numWants > 0) {
        for (int i = 0; i < numWants; ++i) {
            string want;
            double expense;
            cout << "\nEnter name of want " << (i + 1) << ": ";
            getline(cin, want);
            cout << "Enter expense for " << want << ": PHP ";
            expense = getValidNumberInput();
            user.wants.push_back(make_pair(want, expense));
            user.totalWants += expense;
        }
    } else {
        cout << "No wants entered.\n";
    }

    // para sa Savings, Debt, and Investments
    cout << "\n-------------------- Savings, Debt, and Investments --------------------\n";
    
    cout << "Enter total savings for the month: PHP ";
    user.totalSavings = getValidNumberInput();
    
    cout << "Enter total debt for the month: PHP ";
    user.totalDebt = getValidNumberInput();
    
    cout << "Enter total investments for the month: PHP ";
    user.totalInvestments = getValidNumberInput();
    
    user.totalExpenses = user.totalNeeds + user.totalWants + user.totalSavings + user.totalDebt + user.totalInvestments;

    cout << "\nExpense tracking completed successfully!\n";
}

void showFinancialSummary(const User &user) {
    cout << "\n************************ Financial Summary ************************\n";
    cout << "* Name: " << user.name << "\n";
    cout << "* Daily Income: PHP " << user.dailyIncome << "\n";
    cout << "* Weekly Income: PHP " << user.weeklyIncome << "\n";
    cout << "* Monthly Income: PHP " << user.monthlyIncome << "\n";
    cout << "* Total Expenses: PHP " << user.totalExpenses << "\n";
    cout << "* Total Savings: PHP " << user.totalSavings << "\n";
    cout << "* Total Debt: PHP " << user.totalDebt << "\n";
    cout << "* Total Investments: PHP " << user.totalInvestments << "\n";
    cout << "*******************************************************************\n";
    
    double remainingBalance = user.monthlyIncome - user.totalExpenses;
    
    if (remainingBalance < 0) {
        cout << "* Warning: You are overspending by PHP " << -remainingBalance << ". Try to reduce your expenses.\n";
    } else {
        cout << "* Great job! You are within your budget. Your remaining balance is PHP " << remainingBalance << ".\n";
    }
}

void trackBudgetForAllUsers() {
    int numUsers;
    cout << "Enter the number of users: ";
    while (true) {
        cin >> numUsers;
        clearBuffer();
        if (numUsers < 1) {
            cout << "There must be at least one user. Please enter a valid number.\n";
        } else {
            break;
        }
    }

    vector<User> users(numUsers);

    for (int i = 0; i < numUsers; ++i) {
        cout << "\nEnter name for user " << (i + 1) << ": ";
        getline(cin, users[i].name);

        string incomeSource = getValidTextInput("What is your source of income? (allowance, business, employment, pension): ");
        cout << "Your income source is: " << incomeSource << endl;
        
        trackUserIncome(users[i]);
        trackUserExpenses(users[i]);
        showFinancialSummary(users[i]);

        string durationChoice;
        while (true) {
            cout << "Do you want to track income and expenses weekly or monthly? (Enter 'weekly' or 'monthly'): ";
            cin >> durationChoice;
            clearBuffer();

            if (durationChoice == "monthly") {
                string month;
                while (true) {
                    cout << "Enter the month (January to December): ";
                    getline(cin, month);

                    if (monthsDays.find(month) != monthsDays.end()) {
                        int daysInMonth = monthsDays[month];
                        cout << "The month of " << month << " has " << daysInMonth << " days.\n";
                        
                        double budgetForMonth = daysInMonth * users[i].dailyIncome;
                        cout << "Your budget for this month is: PHP " << budgetForMonth << endl;
                        break;
                    } else {
                        cout << "Invalid month entered. Please try again.\n";
                    }
                }
                break;
            } else if (durationChoice == "weekly") { 
                cout << "You chose to track for 7 days.\n";
                break;
            } else {
                cout << "Invalid input, please choose 'weekly' or 'monthly'.\n";
            }
        }
    }
}

int main() {
    cout << "************************ Budget and Finance Advisor ************************\n";
    cout << "* Welcome to the Budget and Finance Advisor Chatbot! This chatbot helps you *\n";
    cout << "*      track your income, expenses, and savings. Let's get started!         *\n";
    cout << "*****************************************************************************\n";

    trackBudgetForAllUsers();

    cout << "*****************************************************************************\n";
    cout << "*  Thank you for using the Budget and Finance Advisor Chatbot! Stay on top  *\n";
    cout << "*       of your finances and make smart financial decisions.                *\n";
    cout << "*****************************************************************************\n";

    return 0;
}
