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
        
    cout << "\n-------------------- Needs --------------------\n";
    double foodExpense, transportExpense, rentExpense, billsExpense;

    cout << "Enter expense for Food: PHP ";
    foodExpense = getValidNumberInput();
    user.needs.push_back(make_pair("Food", foodExpense));
    user.totalNeeds += foodExpense;

    cout << "Enter expense for Transport: PHP ";
    transportExpense = getValidNumberInput();
    user.needs.push_back(make_pair("Transport", transportExpense));
    user.totalNeeds += transportExpense;

    cout << "Enter expense for Rent: PHP ";
    rentExpense = getValidNumberInput();
    user.needs.push_back(make_pair("Rent", rentExpense));
    user.totalNeeds += rentExpense;

    cout << "Enter expense for Bills: PHP ";
    billsExpense = getValidNumberInput();
    user.needs.push_back(make_pair("Bills", billsExpense));
    user.totalNeeds += billsExpense;

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

    user.totalExpenses = user.totalNeeds + user.totalWants;

    cout << "\nExpense tracking completed successfully!\n";
}

void showFinancialSummary(const User &user) {
    cout << "\n************************ Financial Summary ************************\n";
    cout << "* Name: " << user.name << "\n";
    cout << "* Daily Income: PHP " << user.dailyIncome << "\n";
    cout << "* Weekly Income: PHP " << user.weeklyIncome << "\n";
    cout << "* Monthly Income: PHP " << user.monthlyIncome << "\n";
    cout << "* Total Expenses: PHP " << user.totalExpenses << "\n";
    
    // Breakdown of needs
    if (!user.needs.empty()) {
        cout << "\n-------------------- Needs Breakdown --------------------\n";
        for (const auto& need : user.needs) {
            cout << "* " << need.first << ": PHP " << need.second << "\n";
        }
    }

    // Breakdown of wants
    if (!user.wants.empty()) {
        cout << "\n-------------------- Wants Breakdown --------------------\n";
        for (const auto& want : user.wants) {
            cout << "* " << want.first << ": PHP " << want.second << "\n";
        }
    }

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

    // Tanungin muna ang user kung anong month bago mag compute
    string month;
    int daysInMonth = 0; 
    while (true) {
        cout << "What month should we calculate for? (Enter a month from January to December): ";
        getline(cin, month);

        if (monthsDays.find(month) != monthsDays.end()) {
            daysInMonth = monthsDays[month]; 
            cout << "The month of " << month << " has " << daysInMonth << " days.\n";
            break;
        } else {
            cout << "Invalid month entered. Please try again.\n";
        }
    }

    for (int i = 0; i < numUsers; ++i) {
        cout << "\nEnter name for user " << (i + 1) << ": ";
        getline(cin, users[i].name);

        string incomeSource = getValidTextInput("What is your source of income? (allowance, business, employment, pension): ");
        cout << "Your income source is: " << incomeSource << endl;

        trackUserIncome(users[i]);
        trackUserExpenses(users[i]);
        showFinancialSummary(users[i]);

        double budgetForMonth = daysInMonth * users[i].dailyIncome;  
        cout << "Your budget for this month is: PHP " << budgetForMonth << endl;
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
