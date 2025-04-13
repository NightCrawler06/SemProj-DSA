#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

vector<string> bands = {"Dec Ave", "Ben and Ben", "Rivermaya"};
vector<string> seats = {"VIP", "Lower Box", "Upper Box", "General Admission"};


string toLower(string str) {
    for (char& c : str)
        c = tolower(c);
    return str;
}

string generateTicketID() {
    return "TKT" + to_string(rand() % 9000 + 1000);
}

bool isYesOrNo(const string& input) {
    string lowered = toLower(input);
    return (lowered == "yes" || lowered == "no");
}

string getCurrentDateTime() {
    time_t now = time(0);
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}


void saveTicketToFile(const string& name, const string& band, const string& time, const string& ticketID, const string& seatType, double price, const string& refundStatus) {
    ofstream file("tickets.txt", ios::app); 
    if (file.is_open()) {
        file << "Ticket ID   : " << ticketID << "\n";
        file << "Name        : " << name << "\n";
        file << "Band        : " << band << "\n";
        file << "Seat Type   : " << seatType << "\n";
        file << "Time        : " << time << "\n";
        file << "Booked At   : " << getCurrentDateTime() << "\n";
        file << "Price       : PHP" << fixed << setprecision(2) << price << "\n";
        file << "Refund      : " << refundStatus << "\n";
        file << "-------------------------------\n";
        file.close();
    } else {
        cout << "Error: Could not open tickets.txt for saving.\n";
    }
}

int main() {
    srand(time(0));
    const double ticketPrice = 1500.00;
    string continueBooking = "yes";
    int bookingCount = 0;


    cout << "\n===========================================\n";
    cout << "|           ConcertTicketBot 2025         |\n";
    cout << "|       Your Ultimate Booking Assistant   |\n";
    cout << "===========================================\n";



    while (toLower(continueBooking) == "yes") {
        string name, band, time, refund, refundStatus, ticketID, seatType;

        cout << "\nBooking a new ticket...\n";

        cout << "1. What's your name? ";
        getline(cin, name);
        while (name.empty()) {
            cout << "Please enter a valid name: ";
            getline(cin, name);
        }

        cout << "\n2. Choose a band:\n";
        for (int i = 0; i < bands.size(); i++) {
            cout << "  [" << i + 1 << "] " << bands[i] << endl;
        }
        int bandChoice;
        cout << "Enter choice (1-" << bands.size() << "): ";
        cin >> bandChoice;
        cin.ignore();  
        while (bandChoice < 1 || bandChoice > bands.size()) {
            cout << "Invalid. Choose again: ";
            cin >> bandChoice;
            cin.ignore();
        }
        band = bands[bandChoice - 1];


        cout << "\n3. Choose seating type:\n";
        for (int i = 0; i < seats.size(); i++) {
            cout << "  [" << i + 1 << "] " << seats[i] << endl;
        }
        int seatChoice;
        cout << "Enter choice (1-" << seats.size() << "): ";
        cin >> seatChoice;
        cin.ignore();  
        while (seatChoice < 1 || seatChoice > seats.size()) {
            cout << "Invalid. Choose again: ";
            cin >> seatChoice;
            cin.ignore();
        }
        seatType = seats[seatChoice - 1];


        cout << "\n4. What time is the concert? ";
        getline(cin, time);
        while (time.empty()) {
            cout << "Please enter a valid time: ";
            getline(cin, time);
        }

        cout << "\n5. Do you want to request a refund? (yes/no): ";
        getline(cin, refund);
        while (!isYesOrNo(refund)) {
            cout << "Invalid input. Please enter 'yes' or 'no': ";
            getline(cin, refund);
        }

        ticketID = generateTicketID();
        refundStatus = (toLower(refund) == "yes") ? "Requested" : "Not requested";

        cout << "\n+--------------- TICKET SUMMARY ----------------+\n";
        cout << "| Ticket ID    : " << ticketID << "\n";
        cout << "| Name         : " << name << "\n";
        cout << "| Band         : " << band << "\n";
        cout << "| Seat Type    : " << seatType << "\n";
        cout << "| Concert Time : " << time << "\n";
        cout << "| Ticket Price : PHP" << ticketPrice << "\n";
        cout << "| Refund       : " << refundStatus << "\n";
        cout << "+------------------------------------------------+\n";

        bookingCount++;
        cout << "Ticket booked successfully! Total this session: " << bookingCount << "\n";
        

        saveTicketToFile(name, band, time, ticketID, seatType, ticketPrice, refundStatus);

        cout << "Would you like to book another ticket? (yes/no): ";
        getline(cin, continueBooking);
    }

    cout << "\n===========================================\n";
    cout << "|    Thank you for using ConcertTicketBot! |\n";
    cout << "|   Enjoy the music and see you next time! |\n";
    cout << "===========================================\n";
    return 0;
}
