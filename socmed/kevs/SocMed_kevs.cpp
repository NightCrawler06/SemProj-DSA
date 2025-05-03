#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class User {
public:
    string name;
    string description = "No description set.";
    vector<string> friends;
    vector<string> likes;
    vector<string> favoriteMusic;
    vector<string> favoriteSports;

    User(string userName) {
        name = userName;
    }

    bool isFriend(string otherUserName) {
        return find(friends.begin(), friends.end(), otherUserName) != friends.end();
    }

    void addFriend(string otherUserName) {
        if (!isFriend(otherUserName))
            friends.push_back(otherUserName);
    }

    void removeFriend(string otherUserName) {
        friends.erase(remove(friends.begin(), friends.end(), otherUserName), friends.end());
    }

    void viewFriends() {
        if (friends.empty()) {
            cout << "No friends yet.\n";
        } else {
            for (string friendName : friends)
                cout << "- " << friendName << "\n";
        }
    }
};

class SocialMedia {
    vector<User> userList;
    string currentLoggedInUser;

    string toLower(string inputString) {
        transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
        return inputString;
    }

    User* getUserByName(string userName) {
        for (auto& user : userList)
            if (user.name == userName)
                return &user;
        return nullptr;
    }

    void addInitialUsers() {
        vector<string> defaultUserNames = {
            "kevs", "dex", "franc", "amira", "raisen", "lee"
        };
        for (string name : defaultUserNames)
            userList.push_back(User(name));
    }

public:
    SocialMedia() {
        addInitialUsers();
    }

    void login() {
        cout << "Enter username: ";
        string enteredName;
        cin >> enteredName;
        enteredName = toLower(enteredName);

        User* userPointer = getUserByName(enteredName);
        if (!userPointer) {
            cout << "User not found. Create new? (y/n): ";
            char createChoice;
            cin >> createChoice;
            if (createChoice == 'y' || createChoice == 'Y') {
                userList.push_back(User(enteredName));
                cout << "User created.\n";
            } else {
                return;
            }
        }
        currentLoggedInUser = enteredName;
        cout << "Logged in as " << enteredName << "\n";
    }

    void logout() {
        currentLoggedInUser = "";
        cout << "Logged out.\n";
    }

    void viewProfile() {
        User* user = getUserByName(currentLoggedInUser);
        cout << "\nProfile: " << user->name << "\n";
        cout << "Description: " << user->description << "\n";
    }

    void setDescription() {
        User* user = getUserByName(currentLoggedInUser);
        cout << "Enter new description: ";
        cin.ignore();
        getline(cin, user->description);
        cout << "Description updated.\n";
    }

    void viewFriends() {
        getUserByName(currentLoggedInUser)->viewFriends();
    }

    void viewMutualFriends() {
        cout << "Enter username to compare: ";
        string otherName;
        cin >> otherName;
        otherName = toLower(otherName);

        User* userA = getUserByName(currentLoggedInUser);
        User* userB = getUserByName(otherName);

        if (!userB) {
            cout << "User not found.\n";
            return;
        }

        cout << "Mutual friends with " << otherName << ":\n";
        bool found = false;
        for (string f : userA->friends)
            if (userB->isFriend(f)) {
                cout << "- " << f << "\n";
                found = true;
            }
        if (!found) cout << "None.\n";
    }

    void addFriend() {
        cout << "Enter username to add: ";
        string friendName;
        cin >> friendName;
        friendName = toLower(friendName);

        if (friendName == currentLoggedInUser || !getUserByName(friendName)) {
            cout << "Invalid user.\n";
            return;
        }

        User* u = getUserByName(currentLoggedInUser);
        if (u->isFriend(friendName)) {
            cout << "Already friends.\n";
        } else {
            u->addFriend(friendName);
            getUserByName(friendName)->addFriend(currentLoggedInUser);
            cout << "You are now friends.\n";
        }
    }

    void removeFriend() {
        cout << "Enter username to remove: ";
        string friendName;
        cin >> friendName;
        friendName = toLower(friendName);

        User* u = getUserByName(currentLoggedInUser);
        if (!u->isFriend(friendName)) {
            cout << "Not friends.\n";
            return;
        }

        u->removeFriend(friendName);
        getUserByName(friendName)->removeFriend(currentLoggedInUser);
        cout << friendName << " removed.\n";
    }

    void inputSimpleList(vector<string>& list, const string& label) {
        cout << "Enter " << label << " separated by space (type 'done' to finish): ";
        list.clear();
        string item;
        while (cin >> item && item != "done") {
            list.push_back(toLower(item));
        }
    }

    void editLikes() {
        inputSimpleList(getUserByName(currentLoggedInUser)->likes, "likes");
    }

    void editMusic() {
        inputSimpleList(getUserByName(currentLoggedInUser)->favoriteMusic, "favorite music");
    }

    void editSports() {
        inputSimpleList(getUserByName(currentLoggedInUser)->favoriteSports, "favorite sports");
    }

    void suggestFriends() {
        User* user = getUserByName(currentLoggedInUser);
        if (!user) return;

        vector<pair<string, int>> suggestions;

        for (User& other : userList) {
            if (other.name == user->name || user->isFriend(other.name)) continue;

            int score = 0;
            for (string& like : user->likes)
                if (find(other.likes.begin(), other.likes.end(), like) != other.likes.end()) score++;
            for (string& music : user->favoriteMusic)
                if (find(other.favoriteMusic.begin(), other.favoriteMusic.end(), music) != other.favoriteMusic.end()) score++;
            for (string& sport : user->favoriteSports)
                if (find(other.favoriteSports.begin(), other.favoriteSports.end(), sport) != other.favoriteSports.end()) score++;
            for (string& f : user->friends)
                if (other.isFriend(f)) score++;

            if (score > 0)
                suggestions.push_back(make_pair(other.name, score));
        }

        sort(suggestions.begin(), suggestions.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        cout << "\nFriend Suggestions:\n";
        if (suggestions.empty()) {
            cout << "No suggestions.\n";
        } else {
            for (auto& suggestion : suggestions)
                cout << "- " << suggestion.first << " (score: " << suggestion.second << ")\n";
        }
    }

    void searchUser() {
        cout << "Enter name to search: ";
        string searchName;
        cin >> searchName;

        bool found = false;
        for (User& user : userList) {
            if (user.name.find(searchName) != string::npos) {
                cout << "- " << user.name << "\n";
                found = true;
            }
        }
        if (!found) cout << "No matching users.\n";
    }

    void mainMenu() {
        while (true) {
            cout << "\n--- Menu ---\n";
            if (currentLoggedInUser.empty()) {
                cout << "1. Log In\n2. Exit\nChoice: ";
                int userChoice;
                cin >> userChoice;
                if (userChoice == 1) login();
                else break;
            } else {
                cout << "1. View Profile\n2. Add Friend\n3. Remove Friend\n4. Log Out\n5. Exit\nChoice: ";
                int userChoice;
                cin >> userChoice;

                if (userChoice == 1) {
                    viewProfile();
                    while (true) {
                        cout << "\n1. View Friends\n2. View Mutual Friends\n3. Edit Description\n4. Edit Likes\n5. Edit Music\n6. Edit Sports\n7. Suggest Friends\n8. Search User\n9. Back\nChoice: ";
                        int subChoice;
                        cin >> subChoice;
                        if (subChoice == 1) viewFriends();
                        else if (subChoice == 2) viewMutualFriends();
                        else if (subChoice == 3) setDescription();
                        else if (subChoice == 4) editLikes();
                        else if (subChoice == 5) editMusic();
                        else if (subChoice == 6) editSports();
                        else if (subChoice == 7) suggestFriends();
                        else if (subChoice == 8) searchUser();
                        else break;
                    }
                } else if (userChoice == 2) addFriend();
                else if (userChoice == 3) removeFriend();
                else if (userChoice == 4) logout();
                else break;
            }
        }
    }
};

int main() {
    SocialMedia app;
    app.mainMenu();
    return 0;
}
