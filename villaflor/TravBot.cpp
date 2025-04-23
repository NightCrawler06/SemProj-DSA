#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <queue>


using namespace std;

queue<string> upcomingTrips;


struct Location {
    string name;
    string status;
    string description;
    string date;
};

vector<Location> journal;
vector<string> history;
const int MAX_LOCATIONS = 20;
const int MAX_HISTORY = 10;

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void addToHistory(const string& command) {
    if (history.size() == MAX_HISTORY) {
        history.erase(history.begin());
    }
    history.push_back(command);
}

void openGoogleMaps(const string& location) {
    string url = "start https://www.google.com/maps/search/" + location;
    system(url.c_str());
}

void saveJournal() {
    ofstream file("wander_journal.txt");
    for (const auto& loc : journal) {
        file << loc.name << "\n" << loc.status << "\n" << loc.description << "\n" << loc.date << "\n";
    }
    file.close();
}

void loadJournal() {
    ifstream file("wander_journal.txt");
    string name, status, desc, date;
    while (getline(file, name) && journal.size() < MAX_LOCATIONS) {
        getline(file, status);
        getline(file, desc);
        getline(file, date);
        journal.push_back({name, status, desc, date});
    }
    file.close();
}

void addLocation() {
    if (journal.size() >= MAX_LOCATIONS) {
        cout << "Maximum location entries reached (" << MAX_LOCATIONS << ").\n";
        return;
    }

    Location loc;
    cout << "Place name: ";
    getline(cin, loc.name);
    cout << "Visited or Planned? ";
    getline(cin, loc.status);
    cout << "Description: ";
    getline(cin, loc.description);
    cout << "Date (YYYY-MM-DD): ";
    getline(cin, loc.date);

    journal.push_back(loc);

    if (toLower(loc.status) == "planned") {
        upcomingTrips.push(loc.name);
    }

    cout << "\"" << loc.name << "\" added to your " << loc.status << " list.\n";
}


void showByStatus(const string& type) {
    cout << "\n" << (type == "visited" ? "Visited Places:" : "Planned Trips:") << "\n";
    bool found = false;
    for (const auto& loc : journal) {
        if (toLower(loc.status) == type) {
            cout << "- " << loc.name << " (" << loc.date << "): " << loc.description << "\n";
            found = true;
        }
    }
    if (!found) cout << "No entries found.\n";
}

void openLocation(const string& query) {
    for (const auto& loc : journal) {
        if (toLower(loc.name) == toLower(query)) {
            cout << "Opening " << loc.name << " in Google Maps...\n";
            openGoogleMaps(loc.name);
            return;
        }
    }
    cout << "Location not found.\n";
}

void searchLocation(const string& keyword) {
    string key = toLower(keyword);
    bool found = false;
    cout << "\nSearch results for \"" << keyword << "\":" << "\n";
    for (const auto& loc : journal) {
        if (toLower(loc.name).find(key) != string::npos || toLower(loc.description).find(key) != string::npos) {
            cout << "- " << loc.name << " (" << loc.status << "): " << loc.description << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matches found.\n";
}

void showSummary() {
    int visited = 0, planned = 0;
    for (const auto& loc : journal) {
        if (toLower(loc.status) == "visited") visited++;
        else if (toLower(loc.status) == "planned") planned++;
    }

    cout << "\nTravel Summary:\n";
    cout << "- Visited: " << visited << "\n";
    cout << "- Planned: " << planned << "\n";
    cout << "- Total: " << journal.size() << "/" << MAX_LOCATIONS << "\n";
}

void showHistory() {
    cout << "\nRecent Commands:\n";
    for (const auto& cmd : history) {
        cout << "> " << cmd << "\n";
    }
    if (history.empty()) cout << "No commands yet.\n";
}

void showHelp() {
    cout << "\nTravBot Commands:\n";
    cout << "add                  - Add new location\n";
    cout << "show visited         - View visited places\n";
    cout << "show planned         - View planned trips\n";
    cout << "next trip            - Show next planned trip\n";
    cout << "open <place>         - Open location in Google Maps\n";
    cout << "search <keyword>     - Search your entries\n";
    cout << "travel summary       - View trip stats\n";
    cout << "save this            - Save your journal\n";
    cout << "history              - Show recent commands\n";
    cout << "help                 - Show this guide\n";
    cout << "exit                 - End the session\n";
}

int main() {
    loadJournal();
    cout << "Hello! I'm TravBot, your travel companion.\n";
    cout << "Type 'help' to see what I can do.\n";

    string input;
    while (true) {
        cout << "\n> ";
        getline(cin, input);
        addToHistory(input);
        string lower = toLower(input);

        if (lower == "exit") break;
        else if (lower == "add") addLocation();
        else if (lower == "show visited") showByStatus("visited");
        else if (lower == "show planned") showByStatus("planned");
        else if (lower == "next trip") {
            if (!upcomingTrips.empty()) {
                cout << "Next planned trip: " << upcomingTrips.front() << "\n";
                upcomingTrips.pop(); 
            } else {
                cout << "No upcoming trips queued.\n";
            }
        }
        else if (lower.rfind("open ", 0) == 0) openLocation(input.substr(5));
        else if (lower.rfind("search ", 0) == 0) searchLocation(input.substr(7));
        else if (lower == "travel summary") showSummary();
        else if (lower == "save this") {
            saveJournal();
            cout << "Your journey has been saved.\n";
        }
        else if (lower == "history") showHistory();
        else if (lower == "help") showHelp();
        else cout << "Unknown command. Type 'help' to see available commands.\n";
    }

    cout << "\nThanks for using TravBot. See you on your next adventure.\n";
    return 0;
}
