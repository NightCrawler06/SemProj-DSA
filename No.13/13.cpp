#include <iostream>
#include <vector>
#include <string>
#include <limits>
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

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showPatientsAboutToFinish(const vector<Room>& hospitalRooms) {
    cout << "\n************************ Patients Nearing Discharge ************************\n";
    cout << "* Patients with less than 10 days remaining in their treatment plan         *\n";
    cout << "*****************************************************************************\n";
    
    bool foundPatients = false;
    
    for (int i = 0; i < hospitalRooms.size(); ++i) {
        Room room = hospitalRooms[i];
        for (int j = 0; j < room.patients.size(); ++j) {
            Patient patient = room.patients[j];
            if (patient.daysLeft <= 10) {
                cout << "* Room #" << room.roomNumber << " | Patient: " << patient.name
                     << " | Illness: " << patient.illness
                     << " | Medicine: " << patient.medicine
                     << " | Days Left: " << patient.daysLeft << endl;
                foundPatients = true;
            }
        }
    }
    
    if (!foundPatients) {
        cout << "* No patients are nearing completion of their treatment at this time.    *\n";
    }
    
    cout << "*****************************************************************************\n";
}

void showAllRoomDetails(const vector<Room>& hospitalRooms) {
    cout << "\n************************ Hospital Room Information ************************\n";
    cout << "* Detailed information about all rooms and patients                        *\n";
    cout << "*****************************************************************************\n";
    
    for (int i = 0; i < hospitalRooms.size(); ++i) {
        Room room = hospitalRooms[i];
        cout << "\n-------------------- Room #" << room.roomNumber << " (" << room.roomType << ") --------------------\n";
        
        if (room.patients.empty()) {
            cout << "* No patients currently assigned to this room.\n";
        } else {
            for (int j = 0; j < room.patients.size(); ++j) {
                Patient patient = room.patients[j];
                cout << "* Patient #" << (j + 1) << ":\n";
                cout << "* Name: " << patient.name << "\n";
                cout << "* Illness: " << patient.illness << "\n";
                cout << "* Medicine: " << patient.medicine << "\n";
                cout << "* Time to take: " << patient.medicineTime << "\n";
                cout << "* Days Left: " << patient.daysLeft << "\n";
                
                if (j < room.patients.size() - 1) {
                    cout << "* ----------------------------------------\n";
                }
            }
        }
    }
    
    cout << "*****************************************************************************\n";
}

int main() {
    vector<Room> hospitalRooms;

    cout << "************************ Hospital Management System ************************\n";
    cout << "* Welcome to the Hospital Management System! This program helps you        *\n";
    cout << "* manage patient information and track treatment progress.                 *\n";
    cout << "*****************************************************************************\n";

    int totalRooms;
    cout << "\nEnter the total number of rooms (minimum of 15): ";
    cin >> totalRooms;

    if (totalRooms < 15) {
        cout << "\n************************ Error ************************\n";
        cout << "* The hospital must have at least 15 rooms.          *\n";
        cout << "* Program will now exit.                             *\n";
        cout << "*******************************************************\n";
        return 0;
    }

    for (int i = 0; i < totalRooms; ++i) {
        Room room;
        cout << "\n************************ Room Setup ************************\n";
        cout << "* Enter details for Room #" << i + 1 << "                              *\n";
        cout << "***********************************************************\n";

        room.roomNumber = i + 1;
        cout << "Enter room type (Private, Semi-private, Ward): ";
        cin >> room.roomType;

        int patientCount;
        cout << "How many patients in this room? (1 or 2): ";
        cin >> patientCount;

        if (patientCount > 0) {
            clearInputBuffer(); // Clear buffer before reading patient details
        }

        for (int j = 0; j < patientCount; ++j) {
            Patient patient;
            cout << "\n-------------------- Patient #" << j + 1 << " --------------------\n";
            
            cout << "Name: ";
            getline(cin, patient.name);

            cout << "Illness: ";
            getline(cin, patient.illness);

            cout << "Medicine: ";
            getline(cin, patient.medicine);

            cout << "Time to take medicine: ";
            getline(cin, patient.medicineTime);

            cout << "Days left for treatment: ";
            cin >> patient.daysLeft;
            clearInputBuffer(); // Clear buffer after reading days

            room.patients.push_back(patient);
        }

        hospitalRooms.push_back(room);
    }

    showAllRoomDetails(hospitalRooms);

    showPatientsAboutToFinish(hospitalRooms);

    cout << "\n*****************************************************************************\n";
    cout << "*  Thank you for using the Hospital Management System! Providing quality    *\n";
    cout << "*      care through better organization and patient monitoring.             *\n";
    cout << "*****************************************************************************\n";

    return 0;
}