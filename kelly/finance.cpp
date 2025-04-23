#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

struct BudgetEntry {
    string category;
    double amount;
};

struct BudgetUser {
    string name;
    string incomeSource;
    double dailyIncome;
    double monthlyIncome;
    vector<BudgetEntry> needs;
    vector<BudgetEntry> wants;
};

string months[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};
int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void pause() {
    cout << "Press Enter to continue...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string inputText(const string& prompt) {
    string response;
    while (true) {
        cout << prompt;
        getline(cin, response);
        if (!response.empty()) return response;
        cout << "Input cannot be empty. Try again.\n";
    }
}

double inputNumber(const string& prompt) {
    double number;
    while (true) {
        cout << prompt;
        cin >> number;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
        cout << "Invalid input. Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void collectExpenses(vector<BudgetEntry>& entries, const string& sectionName) {
    cout << "\n>>> " << sectionName << " EXPENSES <<<\n";
    int count = (sectionName == "NEEDS") ? 4 : (int)inputNumber("How many " + sectionName + " items do you want to enter? ");

    vector<string> defaultNeeds = {"Food", "Transport", "Rent", "Bills"};
    for (int i = 0; i < count; ++i) {
        string item = (sectionName == "NEEDS") ? defaultNeeds[i] : inputText("Enter item name: ");
        double cost = inputNumber("Cost for " + item + ": PHP ");
        entries.push_back({item, cost});
    }
}

void showSummary(const BudgetUser& user, int monthDays) {
    double totalNeeds = 0, totalWants = 0;
    for (const auto& n : user.needs) totalNeeds += n.amount;
    for (const auto& w : user.wants) totalWants += w.amount;
    double totalExpenses = totalNeeds + totalWants;
    double remaining = user.monthlyIncome - totalExpenses;

    cout << "\n============================================\n";
    cout << "           BUDGET SUMMARY - " << user.name << "\n";
    cout << "============================================\n";
    cout << "Income Source : " << user.incomeSource << "\n";
    cout << "Daily Income  : PHP " << fixed << setprecision(2) << user.dailyIncome << "\n";
    cout << "Monthly Income: PHP " << user.monthlyIncome << " (" << monthDays << " days)\n";

    cout << "\n-------------- NEEDS --------------\n";
    for (const auto& n : user.needs)
        cout << "- " << n.category << ": PHP " << n.amount << "\n";
    cout << "Total Needs : PHP " << totalNeeds << "\n";

    cout << "\n-------------- WANTS --------------\n";
    for (const auto& w : user.wants)
        cout << "- " << w.category << ": PHP " << w.amount << "\n";
    cout << "Total Wants : PHP " << totalWants << "\n";

    cout << "\n----------- SUMMARY STATS ----------\n";
    cout << "Total Expenses     : PHP " << totalExpenses << "\n";
    if (remaining < 0)
        cout << "Overbudget by      : PHP " << -remaining << "\n";
    else
        cout << "Remaining Budget   : PHP " << remaining << "\n";

    double percentNeeds = (totalNeeds / user.monthlyIncome) * 100;
    double percentWants = (totalWants / user.monthlyIncome) * 100;
    cout << "Needs % of Income  : " << percentNeeds << "%\n";
    cout << "Wants % of Income  : " << percentWants << "%\n";
    cout << "============================================\n";

    string filename = "summary_" + user.name + ".txt";
    ofstream file(filename);
    file << "BUDGET SUMMARY FOR: " << user.name << "\n";
    file << "Income Source : " << user.incomeSource << "\n";
    file << "Daily Income  : PHP " << fixed << setprecision(2) << user.dailyIncome << "\n";
    file << "Monthly Income: PHP " << user.monthlyIncome << " (" << monthDays << " days)\n\n";

    file << "[NEEDS]\n";
    for (const auto& n : user.needs)
        file << "- " << n.category << ": PHP " << n.amount << "\n";
    file << "Total Needs : PHP " << totalNeeds << "\n\n";

    file << "[WANTS]\n";
    for (const auto& w : user.wants)
        file << "- " << w.category << ": PHP " << w.amount << "\n";
    file << "Total Wants : PHP " << totalWants << "\n\n";

    file << "[SUMMARY]\n";
    file << "Total Expenses   : PHP " << totalExpenses << "\n";
    file << (remaining < 0 ? "Overspending     : PHP " : "Remaining Budget : PHP ") << abs(remaining) << "\n";
    file << "Needs % of Income: " << percentNeeds << "%\n";
    file << "Wants % of Income: " << percentWants << "%\n";
    file.close();

    cout << "Summary saved to '" << filename << "'\n";
}


int main() {
    cout << "\n==========================================\n";
    cout << "     BudgetMate 2025 - Monthly Planner \n";
    cout << "==========================================\n\n";

    int numUsers = (int)inputNumber("How many users will use the planner? ");
    string month;
    int days;
    while (true) {
        month = inputText("Enter the month you are budgeting for: ");
        for (int i = 0; i < 12; ++i) {
            if (months[i] == month) {
                days = monthDays[i];
                break;
            }
        }
        if (days) break;
        cout << "Invalid month. Try again.\n";
    }

    for (int i = 0; i < numUsers; ++i) {
        BudgetUser user;
        cout << "\n+--------------------------------------+\n";
        cout << "|           USER " << (i + 1) << " - SETUP            |\n";
        cout << "+--------------------------------------+\n";

        user.name = inputText("Enter your name: ");
        user.incomeSource = inputText("What is your income source (job, business, allowance, etc.)? ");
        user.dailyIncome = inputNumber("Enter your daily income (PHP): ");
        user.monthlyIncome = user.dailyIncome * days;

        collectExpenses(user.needs, "NEEDS");
        collectExpenses(user.wants, "WANTS");
        showSummary(user, days);
    }

    cout << "\n==========================================\n";
    cout << "  All users processed. Thank you for using\n";
    cout << "      BudgetMate 2025. Stay on track!   \n";
    cout << "==========================================\n";

    return 0;
}
