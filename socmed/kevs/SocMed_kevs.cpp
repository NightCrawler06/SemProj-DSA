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
    "kieven", "euel", "jerome", "dexter", "ezequel", "gianne", "mark", "nelson", 
    "buboy", "bubski", "anas", "jirom", "kevs", "dex", "franc", "kiel", 
    "amira", "raisen", "lee", "julius"
};
        for (auto& name : names) users[name] = new User(name);

       users["kieven"]->friends = {"euel", "jerome", "dexter"};
	   users["euel"]->friends = {"kieven", "gianne", "mark"};
users["jerome"]->friends = {"kieven", "nelson", "ezequel"};
users["dexter"]->friends = {"kieven", "anas", "dex"};
users["ezequel"]->friends = {"jerome", "gianne", "buboy"};
users["gianne"]->friends = {"euel", "ezequel", "bubski"};
users["mark"]->friends = {"euel", "jirom", "kevs"};
users["nelson"]->friends = {"jerome", "kevs", "franc"};
users["buboy"]->friends = {"ezequel", "kiel", "lee"};
users["bubski"]->friends = {"gianne", "amira", "raisen"};
users["anas"]->friends = {"dexter", "julius"};
users["jirom"]->friends = {"mark", "dex", "kiel"};
users["kevs"]->friends = {"mark", "nelson", "amira"};
users["dex"]->friends = {"dexter", "jirom", "franc"};
users["franc"]->friends = {"nelson", "dex", "lee"};
users["kiel"]->friends = {"buboy", "jirom", "julius"};
users["amira"]->friends = {"bubski", "kevs", "raisen"};
users["raisen"]->friends = {"bubski", "amira", "lee"};
users["lee"]->friends = {"buboy", "franc", "raisen"};
users["julius"]->friends = {"anas", "kiel"};
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