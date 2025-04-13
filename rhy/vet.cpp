#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

using namespace std;

string toLower(string s) {
    for (char& c : s) c = tolower(c);
    return s;
}

string getDateTimeNow() {
    time_t now = time(0);
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void listBreeds(const string& type) {
    map<string, vector<string>> breedMap = {
        {"dog", {
            "Australian Cattle Dog", "Australian Kelpie", "German Shepherd Dog", "Border Collie Dog",
            "Boxer Dog", "Bullmastiff", "Doberman Pinscher Dog", "Great Dane Dog", "Mastiff Dog"
        }},
        {"cat", {
            "Persian", "Maine Coon", "Siamese", "Bengal", "Sphynx", "Ragdoll", "British Shorthair"
        }},
        {"bird", {
            "Duck", "Goose", "Owl", "Flamingo", "Eagle", "Falcon", "Parrot"
        }},
        {"fish", {
            "Goldfish", "Angelfish", "Oscar", "Betta", "Tetra", "Discus", "Glass Catfish"
        }},
        {"reptile", {
            "Bearded Dragons", "Leopard Geckos", "Corn Snakes", "Ball Pythons", "Box Turtles", "Red-Eared Sliders"
        }}
    };

    if (breedMap.find(type) != breedMap.end()) {
        cout << "\nAvailable breeds:\n";
        int index = 1;
        for (const auto& b : breedMap[type]) {
            cout << "  [" << index++ << "] " << b << endl;
        }
    } else {
        cout << "No breed list found for this animal type.\n";
    }
}

int main() {
    string signIn;

    cout << "\n============================================\n";
    cout << "|     Pet Health Advisor - Vet Clinic     |\n";
    cout << "============================================\n";

    cout << "Receptionist: Please sign in to begin.\n";
    cout << "Sign in? (yes/no): ";
    getline(cin, signIn);

    if (toLower(signIn) == "") {
        cout << "Session not started. Exiting.\n";
        return 0;
    }
    if (toLower(signIn) != "yes") {
        cout << "Session not started. Exiting.\n";
        return 0;
    }

    string again = "yes";

    while (toLower(again) == "yes") {
        string owner, pet, type, breed, disease;

        cout << "\nEnter owner name: ";
        getline(cin, owner);
        while (owner.empty()) {
            cout << "Owner name cannot be empty: ";
            getline(cin, owner);
        }

        cout << "Enter pet name: ";
        getline(cin, pet);
        while (pet.empty()) {
            cout << "Pet name cannot be empty: ";
            getline(cin, pet);
        }

        cout << "What kind of animal? (dog/cat/bird/fish/reptile): ";
        getline(cin, type);
        type = toLower(type);
        while (type != "dog" && type != "cat" && type != "bird" && type != "fish" && type != "reptile") {
            cout << "Invalid type. Please enter (dog/cat/bird/fish/reptile): ";
            getline(cin, type);
            type = toLower(type);
        }

        listBreeds(type);
        cout << "Select breed from the list above: ";
        getline(cin, breed);
        while (breed.empty()) {
            cout << "Breed cannot be empty: ";
            getline(cin, breed);
        }

        cout << "Enter disease/condition: ";
        getline(cin, disease);
        while (disease.empty()) {
            cout << "Disease cannot be empty: ";
            getline(cin, disease);
        }

        cout << "\n+------------------- REGISTRATION SUMMARY ------------------+\n";
        cout << "| Owner Name  : " << owner << endl;
        cout << "| Pet Name    : " << pet << endl;
        cout << "| Animal Type : " << type << endl;
        cout << "| Breed       : " << breed << endl;
        cout << "| Disease     : " << disease << endl;
        cout << "| Timestamp   : " << getDateTimeNow() << endl;
        cout << "+------------------------------------------------------------+\n";

        cout << "\nWould you like to register another pet? (yes/no): ";
        getline(cin, again);
    }

    string signOut;
    cout << "\nReceptionist: Would you like to sign out? (yes/no): ";
    getline(cin, signOut);
    if (toLower(signOut) == "yes") {
        cout << "Session ended. Goodbye!\n";
    } else {
        cout << "Returning to main screen...\n";
    }

    return 0;
}
