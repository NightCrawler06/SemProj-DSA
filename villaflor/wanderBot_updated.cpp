#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

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
    cout << "\nWanderBot Commands:\n";
    cout << "add                  - Add new location\n";
    cout << "travel <start> to <end> <distance> - Estimate travel time & view route\n";
    cout << "show visited         - View visited places\n";
    cout << "show planned         - View planned trips\n";
    cout << "open <place>         - Open location in Google Maps\n";
    cout << "search <keyword>     - Search your entries\n";
    cout << "travel summary       - View trip stats\n";
    cout << "save this            - Save your journal\n";
    cout << "history              - Show recent commands\n";
    cout << "help                 - Show this guide\n";
    cout << "exit                 - End the session\n";
}

void estimateTravelTime(const string& from, const string& to, float distance) {
    cout << "\n📍 Travel Time from " << from << " to " << to << " (" << distance << " km):\n";
    cout << "- 🚗 By Car: " << (distance / 60.0) << " hours\n";
    cout << "- 🚲 By Bicycle: " << (distance / 15.0) << " hours\n";
    cout << "- 🚶 On Foot: " << (distance / 5.0) << " hours\n";

    cout << "\nOpen this route in Google Maps? (yes/no): ";
    string answer;
    getline(cin, answer);
    if (toLower(answer) == "yes") {
        string url = "start https://www.google.com/maps/dir/" + from + "/" + to;
        system(url.c_str());
    }
}


void preloadLocations() {
    vector<Location> preset = {
        {"Calayo Beach", "planned", "A calm beach in Nasugbu", "2025-05-01"},
        {"Tunnel in Nasugbu", "planned", "Iconic tunnel along scenic road", "2025-05-01"},
        {"Punta Fuego", "planned", "Private beach resort", "2025-05-01"},
        {"Canyon Cove", "planned", "Popular beach resort", "2025-05-01"},
        {"Fortune Island", "planned", "Greek-column ruins and cliffs", "2025-05-01"},
        {"Mount Batulao", "planned", "Hiking spot with scenic views", "2025-05-01"},
        {"Matabungkay Beach", "planned", "Classic beach spot with floating cottages", "2025-05-01"},
        {"Little Boracay (Calatagan)", "planned", "White sand stretch and clear waters", "2025-05-01"},
        {"Caleruega Church", "planned", "Wedding-favorite church with gardens", "2025-05-01"},
        {"Fantasy World (Lemery, Batangas)", "planned", "Abandoned theme park with Disney-like vibe", "2025-05-01"},
        {"Taal Volcano", "planned", "Famous lake-in-a-volcano-in-a-lake", "2025-05-01"},
        {"Sky Ranch Tagaytay", "planned", "Amusement rides with views", "2025-05-01"},
        {"People’s Park in the Sky", "planned", "Old presidential mansion with views", "2025-05-01"},
        {"Tagaytay Picnic Grove", "planned", "Picnic area with cable car and views", "2025-05-01"},
        {"Twin Lakes", "planned", "Scenic area with Starbucks and wine bar", "2025-05-01"},
        {"Museo Orlina", "planned", "Art museum featuring glass sculptures", "2025-05-01"},
        {"Ayala Mall (Serin, Tagaytay)", "planned", "Small cozy mall with nice gardens", "2025-05-01"},
        {"Festival Mall", "planned", "Big lifestyle mall in Alabang", "2025-05-01"},
        {"SM Mall of Asia", "planned", "Massive mall by Manila Bay", "2025-05-01"},
        {"Sombrero Island", "planned", "Small remote island shaped like a hat", "2025-05-01"}
    };

    journal.insert(journal.end(), preset.begin(), preset.end());
}



int main() {
    loadJournal();
    if (journal.empty()) preloadLocations();
    cout << "Hello! I'm WanderBot, your travel companion.\n";
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
        else if (lower.rfind("open ", 0) == 0) openLocation(input.substr(5));
        else if (lower.rfind("search ", 0) == 0) searchLocation(input.substr(7));
        else if (lower == "travel summary") showSummary();
        else if (lower == "save this") {
            saveJournal();
            cout << "Your journey has been saved.\n";
        }
        else if (lower == "history") showHistory();
        else if (lower == "help") showHelp();
        else if (lower.rfind("travel ", 0) == 0 && lower.find(" to ") != string::npos) {
            size_t toPos = lower.find(" to ");
            string rest = input.substr(toPos + 4);
            string from = input.substr(7, toPos - 7); // extract original casing
            size_t spacePos = rest.find_last_of(' ');
        
            if (spacePos == string::npos) {
                cout << "Invalid format. Use: travel <start> to <end> <distance_in_km>\n";
                continue;
            }
        
            string to = rest.substr(0, spacePos);
            try {
                float distance = stof(rest.substr(spacePos + 1));
                estimateTravelTime(from, to, distance);
            } catch (...) {
                cout << "Invalid distance. Make sure to enter a number.\n";
            }
        }        
        else cout << "Unknown command. Type 'help' to see available commands.\n";
    }

    cout << "\nThanks for using WanderBot. See you on your next adventure.\n";
    return 0;
}
