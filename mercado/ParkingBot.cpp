#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

const int LEVELS = 5;
const int SLOTS_PER_LEVEL = 30;
const int TOTAL_SLOTS = LEVELS * SLOTS_PER_LEVEL;

struct Car {
    string plate;
    string type;  
    int level;
    int slot;
    time_t entryTime;
};

vector<vector<bool>> parkingLevels(LEVELS, vector<bool>(SLOTS_PER_LEVEL, false));
map<string, Car> parkedCars;
queue<string> waitingQueue;
double totalIncome = 0.0;

string timeToStr(time_t t) {
    char buffer[80];
    struct tm* timeInfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%b %d %Y %I:%M:%S %p", timeInfo);
    return string(buffer);
}


double calculateFee(time_t in, time_t out) {
    int hours = (int)difftime(out, in) / 3600;
    if (hours < 1) hours = 1;
    double fee = 0;
    for (int i = 1; i <= hours; ++i)
        fee += 20 + (i - 1) * 10;  
    return fee;
}

void saveData() {
    ofstream file("parking_data.txt");
    for (const auto& pair : parkedCars) {
        const Car& car = pair.second;
        file << car.plate << " " << car.type << " " << car.level << " " << car.slot << " " << car.entryTime << "\n";
    }
    ofstream incomeFile("total_income.txt");
    incomeFile << totalIncome;
}

void loadData() {
    ifstream file("parking_data.txt");
    string plate, type;
    int level, slot;
    time_t entry;
    while (file >> plate >> type >> level >> slot >> entry) {
        Car car = {plate, type, level, slot, entry};
        parkedCars[plate] = car;
        parkingLevels[level][slot] = true;
    }

    ifstream incomeFile("total_income.txt");
    if (incomeFile) incomeFile >> totalIncome;
}

bool assignSlot(string plate, string type) {
    cout << "\n--- CURRENT PARKING STATUS ---\n";
    for (int l = 0; l < LEVELS; ++l) {
        cout << "Level " << l + 1 << ": ";
        for (int s = 0; s < SLOTS_PER_LEVEL; ++s) {
            cout << (parkingLevels[l][s] ? "[X]" : "[" + to_string(s + 1) + "]");
            if ((s + 1) % 10 == 0) cout << "\n           ";
        }
        cout << "\n";
    }

    int chosenLevel;
    cout << "\nChoose a level (1 to " << LEVELS << "): ";
    cin >> chosenLevel;

    if (chosenLevel < 1 || chosenLevel > LEVELS) {
        cout << "Invalid level.\n";
        return false;
    }

    int levelIndex = chosenLevel - 1;

    vector<int> availableSlots;
    for (int i = 0; i < SLOTS_PER_LEVEL; ++i) {
        if (!parkingLevels[levelIndex][i]) {
            availableSlots.push_back(i + 1);
        }
    }

    if (availableSlots.empty()) {
        cout << "No available slots in Level " << chosenLevel << ".\n";
        return false;
    }

    cout << "Available slots on Level " << chosenLevel << ": ";
    for (int s : availableSlots) cout << "[" << s << "] ";

    cout << "\n";

    int chosenSlot;
    while (true) {
        cout << "Choose a slot from the list above: ";
        cin >> chosenSlot;

        if (find(availableSlots.begin(), availableSlots.end(), chosenSlot) != availableSlots.end()) {
            int slotIndex = chosenSlot - 1;
            parkingLevels[levelIndex][slotIndex] = true;
            Car car = {plate, type, levelIndex, slotIndex, time(nullptr)};
            parkedCars[plate] = car;

            cout << "Vehicle " << plate << " (" << type << ") parked at Level "
                 << chosenLevel << ", Slot " << chosenSlot << " at "
                 << timeToStr(car.entryTime) << endl;
            return true;
        } else {
            cout << "Invalid slot. Please choose from the available ones.\n";
        }
    }
}


void exitCar(string plate) {
    if (parkedCars.find(plate) == parkedCars.end()) {
        cout << "Plate not found.\n";
        return;
    }
    Car car = parkedCars[plate];
    time_t outTime = time(nullptr);
    double fee = calculateFee(car.entryTime, outTime);
    totalIncome += fee;
    parkingLevels[car.level][car.slot] = false;

    cout << "\n=====================================\n";
    cout << "        PARKING RECEIPT\n";
    cout << "=====================================\n";
    cout << "Plate No.     : " << car.plate << "\n";
    cout << "Vehicle Type  : " << car.type << "\n";
    cout << "Parked At     : Level " << car.level + 1 << ", Slot " << car.slot + 1 << "\n";
    cout << "Entry Time    : " << timeToStr(car.entryTime) << "\n";
    cout << "Exit Time     : " << timeToStr(outTime) << "\n";
    cout << "-------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "TOTAL FEE     : PHP " << fee << "\n";
    cout << "=====================================\n";


    parkedCars.erase(plate);
    saveData();

    if (!waitingQueue.empty()) {
        string nextPlate = waitingQueue.front();
        waitingQueue.pop();
        string type;
        cout << "\nNext in queue: " << nextPlate << " now being parked.\n";
        cout << "Vehicle type for " << nextPlate << " (car/motorcycle/ev): ";
        cin >> type;
        assignSlot(nextPlate, type);
    }
}

void showStatus() {
    int count = 0;
    cout << "\n=== PARKING STATUS ===\n";
    for (int l = 0; l < LEVELS; ++l) {
        cout << "Level " << l + 1 << ": ";
        for (int s = 0; s < SLOTS_PER_LEVEL; ++s) {
            cout << (parkingLevels[l][s] ? "[X]" : "[ ]");
            if (parkingLevels[l][s]) count++;
        }
        cout << endl;
    }
    cout << "\nOccupied: " << count << " / " << TOTAL_SLOTS << endl;
    cout << "Available: " << TOTAL_SLOTS - count << endl;
    cout << "Cars in queue: " << waitingQueue.size() << endl;
    cout << "Total Income Collected: PHP" << fixed << setprecision(2) << totalIncome << endl;
}

void chatbot() {
    string input;
    while (true) {
        cout << "\nCommand (arrive/exit/status/list/quit): ";
        cin >> input;

        if (input == "arrive") {
            string plate, type;
            cout << "Plate number: ";
            cin >> plate;
            if (parkedCars.count(plate)) {
                cout << "Already parked.\n";
                continue;
            }
            cout << "Vehicle type (car/motorcycle/ev): ";
            cin >> type;
            if (!assignSlot(plate, type)) {
                cout << "Parking full. Added to queue.\n";
                waitingQueue.push(plate);
            }
            saveData();
        } else if (input == "exit") {
            string plate;
            cout << "Plate number to exit: ";
            cin >> plate;
            exitCar(plate);
        } else if (input == "status") {
            showStatus();
        } else if (input == "list") {
            cout << "\nCurrently Parked Vehicles:\n";
            for (const auto& pair : parkedCars) {
                const Car& car = pair.second;
                cout << "- " << car.plate << " (" << car.type << ") at L" << car.level + 1
                     << " S" << car.slot + 1 << " | In: " << timeToStr(car.entryTime) << endl;
            }
        } else if (input == "quit") {
            saveData();
            cout << "Exiting Parking Manager...\n";
            break;
        } else {
            cout << "Unknown command. Try: arrive, exit, status, list, quit.\n";
        }
    }
}

int main() {
    cout << "Welcome to ParkingSpaceManagerBot\n";
    cout << "Building has 5 Levels with 30 slots each (Total: 150 slots)\n";
    loadData();
    chatbot();
    return 0;
}
