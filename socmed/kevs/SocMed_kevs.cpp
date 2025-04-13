#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class User {
public:
    string name, profileDescription = "No description set.";
    unordered_set<string> friends;
    User(string n) : name(n) {}
};

class SocialMedia {
    unordered_map<string, User*> users;
    string currentUser;

    string toLower(const string& str) {
        string res = str;
        transform(res.begin(), res.end(), res.begin(), ::tolower);
        return res;
    }

    void initUsers() {
        if (!users.empty()) return;
        vector<string> names = {
            "alice", "bob", "carol", "dave", "eve", "frank", "grace", "heidi",
            "ivan", "judy", "karl", "lisa", "mallory", "nancy", "olivia", "peggy",
            "quincy", "ralph", "susan", "trent"
        };
        for (auto& name : names) users[name] = new User(name);

        users["alice"]->friends = {"bob", "carol", "dave"};
        users["bob"]->friends = {"alice", "eve", "heidi"};
        users["carol"]->friends = {"alice", "frank", "grace"};
        users["dave"]->friends = {"alice", "heidi", "ivan"};
        users["eve"]->friends = {"bob", "mallory", "nancy"};
        users["frank"]->friends = {"carol", "peggy", "ralph"};
        users["grace"]->friends = {"carol", "karl", "susan"};
        users["heidi"]->friends = {"alice", "dave", "peggy"};
        users["ivan"]->friends = {"dave", "judy", "trent"};
        users["judy"]->friends = {"ivan", "lisa", "susan"};
        users["karl"]->friends = {"grace", "mallory", "trent"};
        users["lisa"]->friends = {"judy", "nancy", "ralph"};
        users["mallory"]->friends = {"eve", "karl", "olivia"};
        users["nancy"]->friends = {"eve", "lisa", "ralph"};
        users["olivia"]->friends = {"mallory", "trent"};
        users["peggy"]->friends = {"frank", "heidi"};
        users["ralph"]->friends = {"frank", "lisa", "nancy"};
        users["susan"]->friends = {"grace", "judy", "trent"};
        users["trent"]->friends = {"ivan", "karl", "susan"};
    }

public:
    SocialMedia() { initUsers(); }

    void login() {
        cout << "Enter username: "; string name; cin >> name;
        name = toLower(name);
        if (users.find(name) == users.end()) {
            cout << "User not found. Create new? (y/n): "; char c; cin >> c;
            if (c == 'y' || c == 'Y') {
                users[name] = new User(name);
                currentUser = name;
                cout << "Account created. Logged in as " << name << "\n";
            } else return;
        } else {
            currentUser = name;
            cout << "Welcome back, " << currentUser << "!\n";
        }
    }

    void logout() {
        if (currentUser.empty()) cout << "Not logged in.\n";
        else { cout << "Logged out.\n"; currentUser = ""; }
    }

    void setDescription() {
        if (currentUser.empty()) return;
        cout << "Enter new description: ";
        cin.ignore(); string desc; getline(cin, desc);
        users[currentUser]->profileDescription = desc;
        cout << "Description updated.\n";
    }

    void viewProfile() {
        if (currentUser.empty()) return;
        auto* u = users[currentUser];
        cout << "\nProfile: " << u->name << "\nDescription: " << u->profileDescription << "\n";
    }

    void viewFriends() {
        if (currentUser.empty()) return;
        auto& f = users[currentUser]->friends;
        if (f.empty()) cout << "No friends yet.\n";
        else for (auto& fr : f) cout << "- " << fr << "\n";
    }

    void addFriend() {
        if (currentUser.empty()) return;
        cout << "Enter username to add: "; string name; cin >> name;
        name = toLower(name);
        if (name == currentUser || users.find(name) == users.end()) {
            cout << "Invalid user.\n"; return;
        }
        auto* u = users[currentUser];
        if (u->friends.count(name)) cout << "Already friends.\n";
        else {
            u->friends.insert(name);
            users[name]->friends.insert(currentUser);
            cout << "Now friends with " << name << "\n";
        }
    }

    void removeFriend() {
        if (currentUser.empty()) return;
        cout << "Enter username to remove: "; string name; cin >> name;
        name = toLower(name);
        auto* u = users[currentUser];
        if (!u->friends.count(name)) cout << "Not friends.\n";
        else {
            cout << "Confirm removal? (y/n): "; char c; cin >> c;
            if (c == 'y' || c == 'Y') {
                u->friends.erase(name);
                users[name]->friends.erase(currentUser);
                cout << name << " removed.\n";
            }
        }
    }

    void mutualFriends() {
        if (currentUser.empty()) return;
        cout << "Enter username: "; string name; cin >> name;
        name = toLower(name);
        if (users.find(name) == users.end()) { cout << "User not found.\n"; return; }

        cout << "Mutual friends with " << name << ":\n";
        bool any = false;
        for (auto& f : users[currentUser]->friends)
            if (users[name]->friends.count(f)) {
                cout << "- " << f << "\n"; any = true;
            }
        if (!any) cout << "None.\n";
    }

    void mainMenu() {
        while (true) {
            cout << "\n--- Menu ---\n";
            if (currentUser.empty()) {
                cout << "1. Log In\n2. Exit\nChoice: ";
                int ch; 
                cin >> ch;
                if (ch == 1) login();
                else if (ch == 2) break;
            } else {
                cout << "1. View Profile\n2. Add Friend\n3. Remove Friend\n4. Log Out\n5. Exit\nChoice: ";
                int ch; 
                cin >> ch;
                if (ch == 1) {
                    viewProfile();
                    while (true) {
                        cout << "1. View Friends\n2. View Mutual Friends\n3. Edit Description\n4. Back\nChoice: ";
                        int c; 
                        cin >> c;
                        if (c == 1) viewFriends();
                        else if (c == 2) mutualFriends();
                        else if (c == 3) setDescription();
                        else break;
                    }
                } else if (ch == 2) addFriend();
                else if (ch == 3) removeFriend();
                else if (ch == 4) logout();
                else if (ch == 5) break;
            }
        }
    }
};

int main() {
    SocialMedia app;
    app.mainMenu();
    return 0;
}
