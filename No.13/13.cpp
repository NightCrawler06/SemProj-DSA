#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Patient {
    string name;
    string illness;
    string medicine;
    string medicineTime;
    int daysLeft;
};

struct Room {
    int roomNumber;
    vector<Patient> patients;
    string roomType;
};

void showPatientsAboutToFinish(const vector<Room>& hospitalRooms) {
    cout << "\n--- Patients nearing completion of their treatment (less than 10 days left) ---\n";
    for (int i = 0; i < hospitalRooms.size(); ++i) {
        Room room = hospitalRooms[i];
        for (int j = 0; j < room.patients.size(); ++j) {
            Patient patient = room.patients[j];
            if (patient.daysLeft <= 10) {
                cout << "Patient: " << patient.name
                        << ", Illness: " << patient.illness
                        << ", Medicine: " << patient.medicine
                        << ", Days Left: " << patient.daysLeft << endl;
            }
        }
    }
}

void showAllRoomDetails(const vector<Room>& hospitalRooms) {
    cout << "\n--- Room Information ---\n";
    for (int i = 0; i < hospitalRooms.size(); ++i) {
        Room room = hospitalRooms[i];
        cout << "Room #" << room.roomNumber << " (" << room.roomType << "):\n";
        for (int j = 0; j < room.patients.size(); ++j) {
            Patient patient = room.patients[j];
            cout << "Name: " << patient.name
                    << ", Illness: " << patient.illness
                    << ", Medicine: " << patient.medicine
                    << ", Time to take: " << patient.medicineTime
                    << ", Days Left: " << patient.daysLeft << endl;
        }
    }
}

int main() {
    vector<Room> hospitalRooms;

    int totalRooms;
    cout << "Enter the total number of rooms (minimum of 15): ";
    cin >> totalRooms;

    if (totalRooms < 15) {
        cout << "The hospital must have at least 15 rooms. Exiting...\n";
        return 0;
    }

    for (int i = 0; i < totalRooms; ++i) {
        Room room;
        cout << "\nEnter details for Room #" << i + 1 << ":\n";

        room.roomNumber = i + 1;
        cout << "Enter room type (Private, Semi-private, Ward): ";
        cin >> room.roomType;

        int patientCount;
        cout << "How many patients in this room? (1 or 2): ";
        cin >> patientCount;

        for (int j = 0; j < patientCount; ++j) {
            Patient patient;
            cout << "Enter details for Patient #" << j + 1 << ":\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, patient.name);

            cout << "Illness: ";
            getline(cin, patient.illness);

            cout << "Medicine: ";
            getline(cin, patient.medicine);

            cout << "Time to take medicine: ";
            getline(cin, patient.medicineTime);

            cout << "Days left for treatment: ";
            cin >> patient.daysLeft;

            room.patients.push_back(patient);
        }

        hospitalRooms.push_back(room);
    }

    showAllRoomDetails(hospitalRooms);

    showPatientsAboutToFinish(hospitalRooms);

    return 0;
}
