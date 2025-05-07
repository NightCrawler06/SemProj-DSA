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
    double totalExpenses = 0;
    double totalSavings = 0;
    double totalNeeds = 0;
    double totalWants = 0;
    double totalDebt = 0;
    double totalInvestments = 0;
    vector<pair<string, double>> needs;
    vector<pair<string, double>> wants;
};

map<string, int> monthsDays = {
    {"January", 31}, {"February", 28}, {"March", 31}, {"April", 30},
    {"May", 31}, {"June", 30}, {"July", 31}, {"August", 31},
    {"September", 30}, {"October", 31}, {"November", 30}, {"December", 31}
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

void trackUserExpenses(User &user, string timeFrame) {
    cout << "\n************************ Track Your Expenses ************************\n";
    if (timeFrame == "weeks") {
        cout << "* Let's track your weekly expenses.                                   *\n";
    } else {
        cout << "* Let's track your monthly expenses.                                  *\n";
    }
    cout << "* Please enter your expenses below.                                   *\n";
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

    user.totalExpenses += user.totalNeeds + user.totalWants;
    cout << "\nExpense tracking completed successfully!\n";
}

void showFinancialSummary(const User &user, string timeFrame) {
    cout << "\n************************ Financial Summary ************************\n";
    cout << "* Name: " << user.name << "\n";
    cout << "* Daily Income: PHP " << user.dailyIncome << "\n";
    cout << "* Weekly Income: PHP " << user.weeklyIncome << "\n";
    if (timeFrame == "month") {
        cout << "* Monthly Income: PHP " << user.monthlyIncome << "\n";
    }
    cout << "* Total Expenses: PHP " << user.totalExpenses << "\n";

    if (!user.needs.empty()) {
        cout << "\n-------------------- Needs Breakdown --------------------\n";
        for (const auto& need : user.needs) {
            cout << "* " << need.first << ": PHP " << need.second << "\n";
        }
    }

    if (!user.wants.empty()) {
        cout << "\n-------------------- Wants Breakdown --------------------\n";
        for (const auto& want : user.wants) {
            cout << "* " << want.first << ": PHP " << want.second << "\n";
        }
    }

    cout << "*******************************************************************\n";

    double budget = (timeFrame == "month") ? user.monthlyIncome : user.weeklyIncome;
    double remainingBalance = budget - user.totalExpenses;

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

    string timeFrame;
    int numberOfWeeks = 0;
    while (true) {
        cout << "What do you want to calculate, weeks or month? ";
        getline(cin, timeFrame);
        if (timeFrame == "weeks") {
            cout << "How many weeks do you want to calculate? ";
            cin >> numberOfWeeks;
            clearBuffer();
            if (numberOfWeeks > 0) break;
        } else if (timeFrame == "month") {
            break;
        } else {
            cout << "Invalid choice. Please enter 'weeks' or 'month'.\n";
        }
    }

    string month;
    int daysInMonth = 0;
    if (timeFrame == "month") {
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
    } else {
        daysInMonth = numberOfWeeks * 7;
    }

    vector<User> users(numUsers);

    for (int i = 0; i < numUsers; ++i) {
        cout << "\nEnter name for user " << (i + 1) << ": ";
        getline(cin, users[i].name);

        string incomeSource = getValidTextInput("What is your source of income? (allowance, business, employment, pension): ");
        cout << "Your income source is: " << incomeSource << endl;

        string anotherSource;
        cout << "Do you have another source of income? (YES/NO): ";
        getline(cin, anotherSource);
        if (anotherSource == "YES" || anotherSource == "yes") {
            string extraSource = getValidTextInput("Enter the name of the other income source: ");
            cout << "How much is the amount from " << extraSource << "? PHP ";
            double extraIncome = getValidNumberInput();
            users[i].dailyIncome += (extraIncome / daysInMonth);
        }

        if (incomeSource == "employment" || incomeSource == "Employment") {
            string response;
            double extra = 0.0;
            cout << "Do you have extra income? (YES/NO): "; getline(cin, response);
            if (response == "YES" || response == "yes") {
                cout << "How much is your extra income? PHP ";
                extra += getValidNumberInput();
            }
            cout << "Do you have a bonus? (YES/NO): "; getline(cin, response);
            if (response == "YES" || response == "yes") {
                cout << "How much is your bonus? PHP ";
                extra += getValidNumberInput();
            }
            cout << "Did you work overtime? (YES/NO): "; getline(cin, response);
            if (response == "YES" || response == "yes") {
                cout << "How much did you earn from overtime? PHP ";
                extra += getValidNumberInput();
            }
            users[i].dailyIncome += (extra / daysInMonth);
        }

        cout << "\nEnter daily income in PHP: ";
        users[i].dailyIncome += getValidNumberInput();  
        users[i].weeklyIncome = users[i].dailyIncome * 7;
        users[i].monthlyIncome = users[i].dailyIncome * 30;

        string unexpected;
        cout << "Do you have any unexpected expenses? (YES/NO): ";
        getline(cin, unexpected);
        if (unexpected == "YES" || unexpected == "yes") {
            string unexpectedName = getValidTextInput("What is your unexpected expense? ");
            cout << "How much was the unexpected expense? PHP ";
            double unexpectedCost = getValidNumberInput();
            users[i].totalExpenses += unexpectedCost;
            cout << "Noted: " << unexpectedName << " - PHP " << unexpectedCost << "\n";
        }
        

        string priority;
        cout << "Do you have any priority expenses for this " << timeFrame << "? (YES/NO): ";
        getline(cin, priority);
        if (priority == "YES" || priority == "yes") {
            string priorityName = getValidTextInput("What is your priority expense for this month? ");
            cout << "How much are your priority expenses? PHP ";
            double priorityCost = getValidNumberInput();
            users[i].totalExpenses += priorityCost;
            cout << "Noted: " << priorityName << " - PHP " << priorityCost << "\n";
        }
        

        trackUserExpenses(users[i], timeFrame);
        showFinancialSummary(users[i], timeFrame);

        double budgetForPeriod = users[i].dailyIncome * daysInMonth;
        cout << "Your budget for this " << timeFrame << " is: PHP " << budgetForPeriod << endl;
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
