#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

const int LEVELS = 5;
const int SLOTS_PER_LEVEL = 30;
const int TOTAL_SLOTS = LEVELS * SLOTS_PER_LEVEL;
const int MAX_QUEUE = 20;

struct Car {
    char plate[16];
    char type[12];
    int slotIndex;
    time_t entryTime;
};

Car parked[TOTAL_SLOTS];
bool occupied[TOTAL_SLOTS] = {false};
char queuePlates[MAX_QUEUE][16];
char queueTypes[MAX_QUEUE][12];
int queueFront = 0, queueRear = 0, queueSize = 0;
double income = 0.0;

int getFreeSlot() {
    for (int i = 0; i < TOTAL_SLOTS; ++i)
        if (!occupied[i]) return i;
    return -1;
}

void drawTitle(const char* title) {
    cout << "\n=========================================\n";
    cout << "          " << title << "\n";
    cout << "=========================================\n";
}

void showMenu() {
    drawTitle("PARKPAL MAIN MENU");
    cout << "[1] Register a Vehicle\n";
    cout << "[2] Remove a Vehicle\n";
    cout << "[3] View Dashboard\n";
    cout << "[4] Show Parking Grid\n";
    cout << "[5] List Parked Vehicles\n";
    cout << "[0] Exit\n";
    cout << "-----------------------------------------\n";
    cout << "Enter your choice: ";
}

void showGrid() {
    drawTitle("PARKING GRID (X = occupied)");
    for (int lvl = 0; lvl < LEVELS; ++lvl) {
        cout << "Level " << lvl + 1 << ":\n";
        for (int s = 0; s < SLOTS_PER_LEVEL; ++s) {
            int idx = lvl * SLOTS_PER_LEVEL + s;
            cout << "[" << setw(2) << s + 1 << ":" << (occupied[idx] ? "X" : " ") << "] ";
            if ((s + 1) % 10 == 0) cout << "\n";
        }
        cout << "\n";
    }
}

void listCars() {
    drawTitle("CURRENTLY PARKED VEHICLES");
    for (int i = 0; i < TOTAL_SLOTS; ++i) {
        if (occupied[i]) {
            int lvl = i / SLOTS_PER_LEVEL + 1;
            int slot = i % SLOTS_PER_LEVEL + 1;
            cout << "- Plate: " << parked[i].plate 
                 << " | Type: " << parked[i].type
                 << " | Location: L" << lvl << " S" << slot << "\n";
        }
    }
}

double calcFee(time_t in, time_t out) {
    int hrs = max(1, (int)difftime(out, in) / 3600);
    return 20 + (hrs - 1) * 10;
}

void registerVehicle() {
    char plate[16], type[12];
    cout << "Enter plate number: "; cin >> plate;
    cout << "Enter vehicle type: "; cin >> type;

    for (int i = 0; i < TOTAL_SLOTS; ++i) {
        if (occupied[i] && strcmp(parked[i].plate, plate) == 0) {
            cout << "This vehicle is already parked.\n";
            return;
        }
    }

    int choice;
    cout << "Choose parking mode: [1] Auto [2] Manual: ";
    cin >> choice;

    int slot = -1;
    if (choice == 1) {
        slot = getFreeSlot();
    } else if (choice == 2) {
        int level, slotNum;
        cout << "Enter level (1-" << LEVELS << "): ";
        cin >> level;
        cout << "Enter slot (1-" << SLOTS_PER_LEVEL << "): ";
        cin >> slotNum;

        level--; slotNum--;
        int idx = level * SLOTS_PER_LEVEL + slotNum;

        if (level < 0 || level >= LEVELS || slotNum < 0 || slotNum >= SLOTS_PER_LEVEL) {
            cout << "Invalid level or slot.\n";
            return;
        }
        if (occupied[idx]) {
            cout << "That slot is already occupied.\n";
            return;
        }
        slot = idx;
    } else {
        cout << "Invalid parking mode.\n";
        return;
    }

    if (slot == -1) {
        if (queueSize < MAX_QUEUE) {
            strcpy(queuePlates[queueRear], plate);
            strcpy(queueTypes[queueRear], type);
            queueRear = (queueRear + 1) % MAX_QUEUE;
            queueSize++;
            cout << "Parking full. Added to queue.\n";
        } else {
            cout << "Parking and queue are full.\n";
        }
        return;
    }

    occupied[slot] = true;
    strcpy(parked[slot].plate, plate);
    strcpy(parked[slot].type, type);
    parked[slot].entryTime = time(0);
    parked[slot].slotIndex = slot;

    int lvl = slot / SLOTS_PER_LEVEL + 1;
    int s = slot % SLOTS_PER_LEVEL + 1;
    cout << "Vehicle parked at Level " << lvl << ", Slot " << s << "\n";
}


void removeVehicle() {
    char plate[16];
    cout << "Enter plate number to remove: "; cin >> plate;

    int idx = -1;
    for (int i = 0; i < TOTAL_SLOTS; ++i) {
        if (occupied[i] && strcmp(parked[i].plate, plate) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Vehicle not found.\n";
        return;
    }

    time_t now = time(0);
    double fee = calcFee(parked[idx].entryTime, now);
    income += fee;
    occupied[idx] = false;

    cout << fixed << setprecision(2);
    cout << "Vehicle removed. Fee: PHP " << fee << "\n";

    if (queueSize > 0) {
        strcpy(parked[idx].plate, queuePlates[queueFront]);
        strcpy(parked[idx].type, queueTypes[queueFront]);
        parked[idx].entryTime = time(0);
        occupied[idx] = true;

        queueFront = (queueFront + 1) % MAX_QUEUE;
        queueSize--;

        cout << "Queued vehicle " << parked[idx].plate << " parked in freed slot.\n";
    }
}

void dashboard() {
    int used = 0;
    for (int i = 0; i < TOTAL_SLOTS; ++i)
        if (occupied[i]) used++;

    drawTitle("PARKING DASHBOARD");
    cout << "Total Slots Used : " << used << " / " << TOTAL_SLOTS << "\n";
    cout << "Queue Length     : " << queueSize << "\n";
    cout << "Total Income     : PHP " << fixed << setprecision(2) << income << "\n";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: registerVehicle(); break;
            case 2: removeVehicle(); break;
            case 3: dashboard(); break;
            case 4: showGrid(); break;
            case 5: listCars(); break;
            case 0: cout << "Shutting down...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
