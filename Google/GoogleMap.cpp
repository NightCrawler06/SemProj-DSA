#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Location {
    string name;
    string status;
    string description;
    string date; 
};

// Function para ma open yung location sa Google Maps
void openInGoogleMaps(const string& locationName) {
    string url = "start https://www.google.com/maps/search/" + locationName;
    system(url.c_str());
}

// Function para ma save yung location sa file
void saveLocations(Location locations[], int locationCount) {
    ofstream outFile("locations.txt");
    for (int i = 0; i < locationCount; i++) {
        outFile << locations[i].name << "\n" 
                << locations[i].status << "\n"
                << locations[i].description << "\n"
                << locations[i].date << "\n";
    }
    outFile.close();
}

// Function para ma load ung location sa file
int loadLocations(Location locations[]) {
    ifstream inFile("locations.txt");
    int count = 0;
    while (getline(inFile, locations[count].name) && count < 20) {
        getline(inFile, locations[count].status);
        getline(inFile, locations[count].description);
        getline(inFile, locations[count].date);
        count++;
    }
    inFile.close();
    return count;
}

// Function para ma sort alphabetically
void sortLocations(Location locations[], int locationCount) {
    sort(locations, locations + locationCount, [](const Location& a, const Location& b) {
        return a.name < b.name;
    });
}

int main() {
    Location locations[20];
    int locationCount = loadLocations(locations);  
    int choice;

    while (true) {
        cout << "\n===== Travel Chatbot =====\n";
        cout << "1. Add Location\n";
        cout << "2. List Locations\n";
        cout << "3. Search and Open Location\n";
        cout << "4. Sort Locations\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            if (locationCount >= 20) {
                cout << "You have reached the maximum number of locations.\n";
                continue;
            }
            cout << "Enter location name: ";
            getline(cin, locations[locationCount].name);
            cout << "Visited or Planned? ";
            getline(cin, locations[locationCount].status);
            cout << "Enter a brief description of the location: ";
            getline(cin, locations[locationCount].description);
            cout << "Enter the date of visit/planned (e.g., 2025-01-01): ";
            getline(cin, locations[locationCount].date);
            locationCount++;
            cout << "Location added successfully.\n";
            saveLocations(locations, locationCount); 
        }
        else if (choice == 2) {
            cout << "\n--- Locations ---\n";
            for (int i = 0; i < locationCount; i++) {
                cout << "Name: " << locations[i].name << "\n"
                     << "Status: " << locations[i].status << "\n"
                     << "Description: " << locations[i].description << "\n"
                     << "Date: " << locations[i].date << "\n"
                     << "-----------------\n";
            }
        }
        else if (choice == 3) {
            string searchName;
            cout << "Enter location name to search: ";
            getline(cin, searchName);
            bool found = false;
            for (int i = 0; i < locationCount; i++) {
                if (locations[i].name == searchName) {
                    cout << "Location found: " << locations[i].name << " (" << locations[i].status << ")\n"
                         << "Description: " << locations[i].description << "\n"
                         << "Date: " << locations[i].date << "\n";
                    char confirm;
                    cout << "Do you want to open this location in Google Maps? (y/n): ";
                    cin >> confirm;
                    cin.ignore();
                    if (confirm == 'y' || confirm == 'Y') {
                        openInGoogleMaps(locations[i].name);
                    } else {
                        cout << "Opening cancelled.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Location not found.\n";
            }
        }
        else if (choice == 4) {
            sortLocations(locations, locationCount);
            cout << "Locations sorted alphabetically by name.\n";
            saveLocations(locations, locationCount);  
        }
        else if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
