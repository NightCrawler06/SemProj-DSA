//version 2

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class User {
public:
    string handle;
    string description;
    unordered_set<string> friends;

    User(const string& handle) : handle(handle), description("No description set.") {}
};

class SocialNetwork {
private:
    unordered_map<string, User*> userDatabase;

    string standardizeText(string input) {
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        return input;
    }

public:
    string activeUser;

    SocialNetwork() : activeUser("") {
        setupDemoUsers();
    }

    void setupDemoUsers() {
        if (!userDatabase.empty()) return;

        vector<string> demoUsers = {"jack", "olivia", "mason", "lucy", "liam", "sophia", "noah", "emma", 
                                    "elijah", "ava", "william", "mia", "james", "ella", "henry", "amelia", 
                                    "alex", "grace", "jackson", "scarlett"};

        for (const string& handle : demoUsers) {
            userDatabase[standardizeText(handle)] = new User(handle);
        }

        userDatabase["jack"]->friends = {"olivia", "mason", "lucy"};
        userDatabase["olivia"]->friends = {"jack", "liam", "sophia"};
        userDatabase["mason"]->friends = {"jack", "noah", "emma"};
        userDatabase["lucy"]->friends = {"jack", "elijah", "ava"};
        userDatabase["liam"]->friends = {"olivia", "william", "mia"};
        userDatabase["sophia"]->friends = {"olivia", "james", "ella"};
        userDatabase["noah"]->friends = {"mason", "henry", "amelia"};
        userDatabase["emma"]->friends = {"mason", "ava", "jackson"};
        userDatabase["elijah"]->friends = {"lucy", "grace", "scarlett"};
        userDatabase["ava"]->friends = {"liam", "mia", "james"};
        userDatabase["william"]->friends = {"liam", "james", "ella"};
        userDatabase["mia"]->friends = {"liam", "noah", "amelia"};
        userDatabase["james"]->friends = {"sophia", "william", "grace"};
        userDatabase["ella"]->friends = {"sophia", "james", "scarlett"};
        userDatabase["henry"]->friends = {"noah", "amelia", "jackson"};
        userDatabase["amelia"]->friends = {"noah", "mia", "jackson"};
        userDatabase["alex"]->friends = {}; 
        userDatabase["grace"]->friends = {"james", "ella", "amelia"};
        userDatabase["jackson"]->friends = {"elijah", "henry", "grace"};
        userDatabase["scarlett"]->friends = {"elijah", "ella", "amelia"};
    }

    void authenticate() {
        string handle;
        cout << "Enter your handle: ";
        cin >> handle;
        string standardHandle = standardizeText(handle);
        if (userDatabase.find(standardHandle) == userDatabase.end()) {
            cout << "Handle not found. Create new account? (y/n): ";
            char response;
            cin >> response;
            if (response == 'y' || response == 'Y') {
                registerUser(handle);
            } else {
                cout << "Authentication cancelled.\n";
            }
        } else {
            activeUser = standardHandle;
            cout << "Welcome back, " << standardHandle << "!\n";
        }
    }

    void registerUser(const string& handle) {
        string standardHandle = standardizeText(handle);
        if (userDatabase.find(standardHandle) != userDatabase.end()) {
            cout << "Handle already taken. Choose another.\n";
        } else if (handle.empty()) {
            cout << "Handle cannot be empty.\n";
        } else {
            userDatabase[standardHandle] = new User(handle);
            cout << "Account created for " << handle << ". Logged in successfully!\n";
            activeUser = standardHandle;
        }
    }

    void updateDescription() {
        if (activeUser.empty()) {
            cout << "Authentication required.\n";
            return;
        }
        string description;
        cout << "Enter new description: ";
        cin.ignore();
        getline(cin, description);
        userDatabase[activeUser]->description = description;
        cout << "Description updated for " << activeUser << ".\n";
    }

    void displayProfile() {
        if (activeUser.empty()) {
            cout << "Authentication required.\n";
            return;
        }
        cout << "Profile for " << activeUser << ":\n";
        cout << "Description: " << userDatabase[activeUser]->description << "\n";
    }

    void connectWith() {
        if (activeUser.empty()) {
            cout << "Authentication required.\n";
            return;
        }
        string friendHandle;
        cout << "Enter handle to connect with: ";
        cin >> friendHandle;
        string standardFriend = standardizeText(friendHandle);
        if (userDatabase.find(standardFriend) == userDatabase.end()) {
            cout << "User not found.\n";
            return;
        }
        if (standardFriend == activeUser) {
            cout << "Cannot connect with yourself.\n";
            return;
        }
        if (userDatabase[activeUser]->friends.find(standardFriend) != userDatabase[activeUser]->friends.end()) {
            cout << "Already connected with " << standardFriend << ".\n";
            return;
        }
        userDatabase[activeUser]->friends.insert(standardFriend);
        userDatabase[standardFriend]->friends.insert(activeUser);
        cout << "Connected with " << standardFriend << " successfully.\n";
    }

    void disconnect() {
        if (activeUser.empty()) {
            cout << "Authentication required.\n";
            return;
        }
        string friendHandle;
        cout << "Enter handle to disconnect: ";
        cin >> friendHandle;
        string standardFriend = standardizeText(friendHandle);
        if (userDatabase.find(standardFriend) == userDatabase.end()) {
            cout << "User not found.\n";
            return;
        }
        if (userDatabase[activeUser]->friends.find(standardFriend) == userDatabase[activeUser]->friends.end()) {
            cout << "Not connected with " << standardFriend << ".\n";
            return;
        }
        cout << "Confirm disconnection from " << standardFriend << "? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            userDatabase[activeUser]->friends.erase(standardFriend);
            userDatabase[standardFriend]->friends.erase(activeUser);
            cout << "Disconnected from " << standardFriend << ".\n";
        } else {
            cout << "Disconnection cancelled.\n";
        }
    }

    void listConnections() {
        if (activeUser.empty()) {
            cout << "Authentication required.\n";
            return;
        }
        cout << "Connections for " << activeUser << ":\n";
        if (userDatabase[activeUser]->friends.empty()) {
            cout << "No connections yet.\n";
        } else {
            for (const string& friend_ : userDatabase[activeUser]->friends) {
                cout << friend_ << "\n";
            }
        }
    }

    void findMutualConnections() {
        if (activeUser.empty()) {
            cout << "Authentication required.\n";
            return;
        }
        string friendHandle;
        cout << "Enter handle to find mutual connections: ";
        cin >> friendHandle;
        string standardFriend = standardizeText(friendHandle);
        if (userDatabase.find(standardFriend) == userDatabase.end()) {
            cout << "User not found.\n";
            return;
        }
        cout << "Mutual connections with " << standardFriend << ":\n";
        bool hasMutual = false;
        for (const string& userFriend : userDatabase[activeUser]->friends) {
            if (userDatabase[standardFriend]->friends.find(userFriend) != userDatabase[standardFriend]->friends.end()) {
                cout << userFriend << "\n";
                hasMutual = true;
            }
        }
        if (!hasMutual) {
            cout << "No mutual connections found.\n";
        }
    }

    void showInterface() {
        cout << "\nSocial Network Interface\n";
        if (activeUser.empty()) {
            cout << "1. Sign In\n";
            cout << "2. Exit\n";
        } else {
            cout << "1. View Profile\n";
            cout << "2. Add Connection\n";
            cout << "3. Remove Connection\n";
            cout << "4. List Connections\n";
            cout << "5. Find Mutual Connections\n";
            cout << "6. Update Description\n";
            cout << "7. Sign Out\n";
            cout << "8. Exit\n";
        }
    }

    void signOut() {
        if (activeUser.empty()) {
            cout << "No active session.\n";
            return;
        }
        activeUser = "";
        cout << "Signed out successfully.\n";
    }

    void shutdown() {
        cout << "Shutting down...\n";
    }
};

int main() {
    SocialNetwork network;
    int option;

    while (true) {
        network.showInterface();
        cout << "Select option: ";
        cin >> option;

        switch (option) {
            case 1:
                if (network.activeUser.empty()) network.authenticate();
                else network.displayProfile();
                break;
            case 2:
                if (network.activeUser.empty()) network.shutdown();
                else network.connectWith();
                break;
            case 3:
                network.disconnect();
                break;
            case 4:
                network.listConnections();
                break;
            case 5:
                network.findMutualConnections();
                break;
            case 6:
                network.updateDescription();
                break;
            case 7:
                network.signOut();
                break;
            case 8:
                network.shutdown();
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
        
    }
    return 0;
}
