#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class TimeBlock {
public:
    string time;
    string description;

    TimeBlock(string t, string d) {
        time = t;
        description = d;
    }
};

class DaySchedule {
public:
    int day;
    vector<TimeBlock> tasks;

    DaySchedule(int d) {
        day = d;
    }

    void addTask(string time, string desc) {
        tasks.emplace_back(time, desc);
    }

    void display(const string& month) const {
        cout << "\n+---------------------------------------------+\n";
        cout << "| SCHEDULE FOR " << month << " " << day << "\n";
        cout << "+---------------------------------------------+\n";
        for (const auto& task : tasks) {
            cout << "| Time: " << setw(10) << left << task.time 
                << "| Task: " << task.description << "\n";
        }
        cout << "+---------------------------------------------+\n";
    }

    void saveToFile(ofstream& out, const string& month) const {
        out << "\n+---------------------------------------------+\n";
        out << "| SCHEDULE FOR " << month << " " << day << "\n";
        out << "+---------------------------------------------+\n";
        for (const auto& task : tasks) {
            out << "| Time: " << setw(10) << left << task.time
                << "| Task: " << task.description << "\n";
        }
        out << "+---------------------------------------------+\n";
    }

    static string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
};

void runScheduleForMonth() {
    string month;
    int daysInMonth;

    cout << "\nEnter month: ";
    getline(cin, month);
    
    string lowerMonth = DaySchedule::toLower(month);

    if (lowerMonth == "january" || lowerMonth == "march" || lowerMonth == "may" ||
        lowerMonth == "july" || lowerMonth == "august" || lowerMonth == "october" ||
        lowerMonth == "december") {
        daysInMonth = 31;
    } else if (lowerMonth == "april" || lowerMonth == "june" || lowerMonth == "september" ||
               lowerMonth == "november") {
        daysInMonth = 30;
    } else if (lowerMonth == "february") {
        daysInMonth = 28; 
    } else {
        cout << "Invalid month. Defaulting to 30 days.\n";
        daysInMonth = 30;
    }

    vector<DaySchedule> monthSchedule;
    for (int i = 1; i <= daysInMonth; i++) {
        monthSchedule.emplace_back(i);
    }

    
    string more = "yes";
    while (DaySchedule::toLower(more) == "yes") {
        int day;
        string time, task;

        cout << "\nEnter day (1-" << daysInMonth << "): ";
        cin >> day;
        cin.ignore();

        if (day < 1 || day > daysInMonth) {
            cout << "Invalid day.\n";
            continue;
        }

        cout << "Enter time (e.g. 10:00 AM): ";
        getline(cin, time);
        cout << "Enter task or description: ";
        getline(cin, task);

        monthSchedule[day - 1].addTask(time, task);

        cout << "Add another task? (yes/no): ";
        getline(cin, more);
    }

    string view;
    cout << "\nWould you like to view the full schedule? (yes/no): ";
    getline(cin, view);

    if (DaySchedule::toLower(view) == "yes") {
        for (const auto& day : monthSchedule) {
            if (!day.tasks.empty()) {
                day.display(month);
            }
        }
    }

    string save;
    ifstream test("schedule_log.txt");
    bool hasData = false;
    if (test.is_open()) {
        string content;
        while (getline(test, content)) {
            if (DaySchedule::toLower(content).find("schedule for " + DaySchedule::toLower(month)) != string::npos) {
                hasData = true;
                break;
            }
        }
        test.close();
    }
    
    if (hasData) {
        cout << "Found saved data for " << month << ". Loading now...\n";
        ifstream in("schedule_log.txt");
        if (in.is_open()) {
            string line;
            int currentDay = -1;
            while (getline(in, line)) {
                if (line.find("SCHEDULE FOR") != string::npos) {
                    string lineLower = DaySchedule::toLower(line);
                    string monthMarker = "schedule for " + DaySchedule::toLower(month);
                    if (lineLower.find(monthMarker) == string::npos) {
                        currentDay = -1;
                        continue;
                    }
                    size_t pos = line.find_last_of(' ');
                    if (pos != string::npos) {
                        currentDay = stoi(line.substr(pos + 1));
                    }
                } else if (line.find("Time:") != string::npos && currentDay != -1) {
                    size_t timeStart = line.find("Time:") + 6;
                    size_t timeEnd = line.find("| Task:");
                    string time = line.substr(timeStart, timeEnd - timeStart - 1);
                    size_t taskStart = line.find("| Task:") + 8;
                    string task = line.substr(taskStart);
                    monthSchedule[currentDay - 1].addTask(time, task);
                }
            }
            in.close();
            cout << "Schedule for " << month << " loaded.\n";
        }
    }
        
    ofstream out("schedule_log.txt", ios::app);
    if (out.is_open()) {
        for (const auto& day : monthSchedule) {
            if (!day.tasks.empty()) {
                day.saveToFile(out, month);
            }
        }
        out.close();
        cout << "Schedule automatically saved to 'schedule_log.txt'\n";
    }
    


    int totalTasks = 0, activeDays = 0;
    for (const auto& day : monthSchedule) {
        if (!day.tasks.empty()) {
            totalTasks += day.tasks.size();
            activeDays++;
        }
    }

    cout << "\n+---------------------- SUMMARY ----------------------+\n";
    cout << "Month: " << month << "\n";
    cout << "Days with tasks: " << activeDays << "\n";
    cout << "Total tasks added: " << totalTasks << "\n";
    cout << "+-----------------------------------------------------+\n";
}

int main() {
    while (true) {
        cout << "\n+===============================================+\n";
        cout << "|        PERSONAL ASSISTANT SCHEDULER SYSTEM     |\n";
        cout << "|         Stay on track. Plan. Prioritize.       |\n";
        cout << "+===============================================+\n";
        cout << "\n[1] Add new schedule";
        cout << "\n[2] View saved schedule";
        cout << "\n[3] Search your schedule";
        cout << "\n[4] Exit";
        cout << "\n\nEnter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            runScheduleForMonth();
        } else if (choice == "2") {
            ifstream in("schedule_log.txt");
            if (in.is_open()) {
                cout << "\n=== SAVED SCHEDULE ===\n";
                string line;
                while (getline(in, line)) {
                    cout << line << "\n";
                }
                in.close();
            } else {
                cout << "\nNo saved schedule found.\n";
            }
        } else if (choice == "3") {
            ifstream in("schedule_log.txt");
            if (in.is_open()) {
                string keyword;
                cout << "\nEnter keyword or day to search (e.g. 'meeting' or '12'): ";
                getline(cin, keyword);
                cout << "\nSearch Results:\n";
                string line;
                bool found = false;
                while (getline(in, line)) {
                    if (DaySchedule::toLower(line).find(DaySchedule::toLower(keyword)) != string::npos) {
                        cout << line << "\n";
                        found = true;
                    }
                }
                if (!found) cout << "No matches found.\n";
                in.close();
            } else {
                cout << "\nNo saved schedule found.\n";
            }
        } else if (choice == "4") {
            cout << "\nExiting program. Goodbye!\n";
            break;
        } else {
            cout << "\nInvalid option. Please try again.\n";
        }
    }

    return 0;
}
