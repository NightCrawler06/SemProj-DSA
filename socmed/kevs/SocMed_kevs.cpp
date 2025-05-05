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
            "kieven", "euel", "jerome", "dexter", "ezequel",
            "gianne", "mark", "nelson", "buboy", "bubski",
            "anas", "jirom", "kevs", "dex", "franc", "kiel",
            "amira", "raisen", "lee", "julius"
        };
    
        for (const string& name : defaultUserNames)
            userList.push_back(User(name));
    
        
        auto get = [&](const string& name) -> User* {
            return getUserByName(name);
        };
    
        
        get("kieven")->friends = {"euel", "jerome", "dexter"};
        get("euel")->friends = {"kieven", "gianne", "mark"};
        get("jerome")->friends = {"kieven", "nelson", "ezequel"};
        get("dexter")->friends = {"kieven", "anas", "dex"};
        get("ezequel")->friends = {"jerome", "gianne", "buboy"};
        get("gianne")->friends = {"euel", "ezequel", "bubski"};
        get("mark")->friends = {"euel", "jirom", "kevs"};
        get("nelson")->friends = {"jerome", "kevs", "franc"};
        get("buboy")->friends = {"ezequel", "kiel", "lee"};
        get("bubski")->friends = {"gianne", "amira", "raisen"};
        get("anas")->friends = {"dexter", "julius"};
        get("jirom")->friends = {"mark", "dex", "kiel"};
        get("kevs")->friends = {"mark", "nelson", "amira"};
        get("dex")->friends = {"dexter", "jirom", "franc"};
        get("franc")->friends = {"nelson", "dex", "lee"};
        get("kiel")->friends = {"buboy", "jirom", "julius"};
        get("amira")->friends = {"bubski", "kevs", "raisen"};
        get("raisen")->friends = {"bubski", "amira", "lee"};
        get("lee")->friends = {"buboy", "franc", "raisen"};
        get("julius")->friends = {"anas", "kiel"};
    
        get("kevs")->likes = {"gaming", "meme"};
        get("kevs")->favoriteMusic = {"rock", "lofi"};
        get("kevs")->favoriteSports = {"basketball"};
    
        get("jirom")->likes = {"coding", "anime"};
        get("jirom")->favoriteMusic = {"pop"};
        get("jirom")->favoriteSports = {"chess", "badminton"};
    
        get("dex")->likes = {"anime", "meme"};
        get("dex")->favoriteMusic = {"rap"};
        get("dex")->favoriteSports = {"basketball"};
    
        get("franc")->likes = {"gaming", "coding"};
        get("franc")->favoriteMusic = {"lofi"};
        get("franc")->favoriteSports = {"badminton"};
    
        get("amira")->likes = {"art", "reading"};
        get("amira")->favoriteMusic = {"classical"};
        get("amira")->favoriteSports = {"volleyball"};
    
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
        User* currentUser = getUserByName(currentLoggedInUser);
        if (!currentUser) return;
    
        cout << "\nEnter username to view (or type 'me' for your own): ";
        string target;
        cin >> target;
        target = toLower(target);
    
        User* viewed = (target == "me") ? currentUser : getUserByName(target);
    
        if (!viewed) {
            cout << "User not found.\n";
            return;
        }
    
        cout << "\n--- Viewing Profile: " << viewed->name << " ---\n";
        cout << "Description: " << viewed->description << "\n";
    
        // Show likes, music, sports
        auto showList = [](const vector<string>& items, const string& label) {
            cout << label << ": ";
            if (items.empty()) {
                cout << "None\n";
            } else {
                for (const string& item : items) cout << item << " ";
                cout << "\n";
            }
        };
    
        showList(viewed->likes, "Likes");
        showList(viewed->favoriteMusic, "Favorite Music");
        showList(viewed->favoriteSports, "Favorite Sports");
    
        // Show friends
        cout << "Friends:\n";
        if (viewed->friends.empty()) {
            cout << "  No friends yet.\n";
        } else {
            for (const string& f : viewed->friends)
                cout << "  - " << f << "\n";
        }
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
        searchName = toLower(searchName);
    
        User* currentUser = getUserByName(currentLoggedInUser);
        if (!currentUser) {
            cout << "No user is currently logged in.\n";
            return;
        }
    
        bool found = false;
        for (User& user : userList) {
            if (user.name == currentUser->name) continue; 
    
            string loweredName = toLower(user.name);
            if (loweredName.find(searchName) != string::npos) {
                found = true;
                cout << "\nFound: " << user.name << "\n";
    
                cout << "  Mutual Friends:\n";
                bool hasMutual = false;
                for (const string& f : currentUser->friends) {
                    if (user.isFriend(f)) {
                        cout << "    - " << f << "\n";
                        hasMutual = true;
                    }
                }
                if (!hasMutual) cout << "    None\n";
    
                cout << "  Shared Likes:\n";
                bool hasLikes = false;
                for (const string& like : currentUser->likes) {
                    if (find(user.likes.begin(), user.likes.end(), like) != user.likes.end()) {
                        cout << "    - " << like << "\n";
                        hasLikes = true;
                    }
                }
                if (!hasLikes) {
                    cout << "    None\n";
                    if (!user.likes.empty()) {
                        cout << "  Their Likes:\n";
                        for (const string& like : user.likes) {
                            cout << "    * " << like << "\n";
                        }
                    }
                }

                if (!hasLikes) cout << "    None\n";
    
                cout << "  Shared Music:\n";
                bool hasMusic = false;
                for (const string& music : currentUser->favoriteMusic) {
                    if (find(user.favoriteMusic.begin(), user.favoriteMusic.end(), music) != user.favoriteMusic.end()) {
                        cout << "    - " << music << "\n";
                        hasMusic = true;
                    }
                }
                if (!hasMusic) {
                    cout << "    None\n";
                    if (!user.favoriteMusic.empty()) {
                        cout << "  Their Music:\n";
                        for (const string& music : user.favoriteMusic) {
                            cout << "    * " << music << "\n";
                        }
                    }
                }
                
                if (!hasMusic) cout << "    None\n";
    
                cout << "  Shared Sports:\n";
                bool hasSports = false;
                for (const string& sport : currentUser->favoriteSports) {
                    if (find(user.favoriteSports.begin(), user.favoriteSports.end(), sport) != user.favoriteSports.end()) {
                        cout << "    - " << sport << "\n";
                        hasSports = true;
                    }
                }
                if (!hasSports) {
                    cout << "    None\n";
                    if (!user.favoriteSports.empty()) {
                        cout << "  Their Sports:\n";
                        for (const string& sport : user.favoriteSports) {
                            cout << "    * " << sport << "\n";
                        }
                    }
                }
                
                if (!hasSports) cout << "    None\n";
            }
        }
    
        if (!found) {
            cout << "No matching users found.\n";
        }
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
                cout << "1. View Profile\n2. Search User\n3. Add Friend\n4. Remove Friend\n5. Log Out\n6. Exit\nChoice: ";
                int userChoice;
                cin >> userChoice;

                if (userChoice == 1) {
                    viewProfile();
                    while (true) {
                        cout << "\n1. View Friends\n2. View Mutual Friends\n3. Edit Description\n4. Edit Likes\n5. Edit Music\n6. Edit Sports\n7. Suggest Friends\n8. Back\nChoice: ";
                        int subChoice;
                        cin >> subChoice;
                        if (subChoice == 1) viewFriends();
                        else if (subChoice == 2) viewMutualFriends();
                        else if (subChoice == 3) setDescription();
                        else if (subChoice == 4) editLikes();
                        else if (subChoice == 5) editMusic();
                        else if (subChoice == 6) editSports();
                        else if (subChoice == 7) suggestFriends();
                        else break;
                    }
                } else if (userChoice == 2) searchUser();
                else if (userChoice == 3) addFriend();
                else if (userChoice == 4) removeFriend();
                else if (userChoice == 5) logout();
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
