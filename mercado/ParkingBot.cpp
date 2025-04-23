#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <iomanip>

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

vector<vector<bool>> parkingSlots(LEVELS, vector<bool>(SLOTS_PER_LEVEL, false));
vector<Car> parkedCars;
queue<string> waitingQueue;
double totalIncome = 0.0;

int findCarIndex(string plate) {
    for (int i = 0; i < parkedCars.size(); ++i) {
        if (parkedCars[i].plate == plate) {
            return i;
        }
    }
    return -1;
}

double calculateFee(time_t in, time_t out, int hour = 1) {
    int hours = (int)difftime(out, in) / 3600;
    if (hours < 1) hours = 1;
    if (hour > hours) return 0;
    return 20 + (hour - 1) * 10 + calculateFee(in, out, hour + 1);
}

bool assignSlot(string plate, string type) {
    for (int i = 0; i < LEVELS; ++i) {
        for (int j = 0; j < SLOTS_PER_LEVEL; ++j) {
            if (!parkingSlots[i][j]) {
                parkingSlots[i][j] = true;
                Car car = {plate, type, i, j, time(nullptr)};
                parkedCars.push_back(car);
                cout << "Auto-parked " << plate << " at Level " << i + 1 << ", Slot " << j + 1 << endl;
                return true;
            }
        }
    }
    return false;
}

bool assignManualSlot(string plate, string type) {
    cout << "\n--- CURRENT PARKING LAYOUT ---\n";
    for (int l = 0; l < LEVELS; ++l) {
        cout << "Level " << l + 1 << ": ";
        for (int s = 0; s < SLOTS_PER_LEVEL; ++s) {
            if (parkingSlots[l][s]) {
                cout << "[X]";
            } else {
                if (s + 1 < 10) cout << "[0" << s + 1 << "]";
                else cout << "[" << s + 1 << "]";
            }
            if ((s + 1) % 10 == 0) cout << "\n           ";
        }
        cout << "\n";
    }

    int level, slot;
    cout << "\nChoose level (1 to " << LEVELS << "): ";
    cin >> level;
    cout << "Choose slot number: ";
    cin >> slot;

    level -= 1;
    slot -= 1;

    if (level < 0 || level >= LEVELS || slot < 0 || slot >= SLOTS_PER_LEVEL) {
        cout << "Invalid selection.\n";
        return false;
    }

    if (parkingSlots[level][slot]) {
        cout << "That slot is already taken!\n";
        return false;
    }

    parkingSlots[level][slot] = true;
    Car car = {plate, type, level, slot, time(nullptr)};
    parkedCars.push_back(car);

    cout << "Manually parked " << plate << " at Level " << level + 1 << ", Slot " << slot + 1 << "\n";
    return true;
}

void exitCar(string plate) {
    int idx = findCarIndex(plate);
    if (idx == -1) {
        cout << "Plate not found.\n";
        return;
    }

    Car car = parkedCars[idx];
    time_t now = time(nullptr);
    double fee = calculateFee(car.entryTime, now);
    totalIncome += fee;
    parkingSlots[car.level][car.slot] = false;

    cout << "\n--- RECEIPT ---\n";
    cout << "Plate     : " << car.plate << endl;
    cout << "Type      : " << car.type << endl;
    cout << "Level     : " << car.level + 1 << endl;
    cout << "Slot      : " << car.slot + 1 << endl;
    cout << "Fee       : PHP " << fixed << setprecision(2) << fee << endl;

    parkedCars.erase(parkedCars.begin() + idx);

    if (!waitingQueue.empty()) {
        string nextPlate = waitingQueue.front();
        waitingQueue.pop();
        string type;
        cout << "\nNext in queue: " << nextPlate << "\n";
        cout << "Enter vehicle type: ";
        cin >> type;

        bool parked = assignSlot(nextPlate, type);
        if (!parked) {
            assignManualSlot(nextPlate, type);
        }
    }
}

void showStatus() {
    int occupied = 0;
    cout << "\n=== PARKING STATUS ===\n";
    for (int l = 0; l < LEVELS; ++l) {
        cout << "Level " << l + 1 << ": ";
        for (int s = 0; s < SLOTS_PER_LEVEL; ++s) {
            cout << (parkingSlots[l][s] ? "[X]" : "[ ]");
            if ((s + 1) % 10 == 0) cout << "\n           ";
            if (parkingSlots[l][s]) occupied++;
        }
        cout << "\n";
    }

    cout << "Occupied : " << occupied << " / " << TOTAL_SLOTS << endl;
    cout << "Available: " << TOTAL_SLOTS - occupied << endl;
    cout << "Queue    : " << waitingQueue.size() << " cars\n";
    cout << "Income   : PHP " << fixed << setprecision(2) << totalIncome << endl;
}

void sortParkedCars() {
    int n = parkedCars.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (parkedCars[j].plate > parkedCars[j + 1].plate) {
                swap(parkedCars[j], parkedCars[j + 1]);
            }
        }
    }
}

void listParkedCars() {
    sortParkedCars();
    cout << "\n--- PARKED VEHICLES ---\n";
    for (const Car& car : parkedCars) {
        cout << "- " << car.plate << " (" << car.type << ") -> L" << car.level + 1 << " S" << car.slot + 1 << endl;
    }
}

void chatbot() {
    string cmd;
    while (true) {
        cout << "\nCommand (arrive / exit / status / list / quit): ";
        cin >> cmd;

        if (cmd == "arrive") {
            string plate, type, mode;
            cout << "Plate number: ";
            cin >> plate;

            if (findCarIndex(plate) != -1) {
                cout << "Car already parked!\n";
                continue;
            }

            cout << "Vehicle type (car/motorcycle/ev): ";
            cin >> type;
            cout << "Choose parking mode (auto/manual): ";
            cin >> mode;

            bool parked = false;
            if (mode == "manual") {
                parked = assignManualSlot(plate, type);
            } else {
                parked = assignSlot(plate, type);
            }

            if (!parked) {
                cout << "Parking failed. Added to queue.\n";
                waitingQueue.push(plate);
            }

        } else if (cmd == "exit") {
            string plate;
            cout << "Plate to exit: ";
            cin >> plate;
            exitCar(plate);

        } else if (cmd == "status") {
            showStatus();

        } else if (cmd == "list") {
            listParkedCars();

        } else if (cmd == "quit") {
            cout << "Exiting ParkingBot...\n";
            break;

        } else {
            cout << "Unknown command.\n";
        }
    }
}

int main() {
    cout << "Welcome to ParkingBot \n";
    cout << "Building has " << LEVELS << " Levels with " << SLOTS_PER_LEVEL << " slots each (Total: " << TOTAL_SLOTS << " slots)\n";
    chatbot();
    return 0;
}
