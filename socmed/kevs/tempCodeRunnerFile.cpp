#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Forward declarations
class NetworkNode;
class SocialGraph;
class CommandProcessor;

class NetworkNode {
private:
    string identifier;
    string bio;
    set<shared_ptr<NetworkNode>> connections;
    
public:
    NetworkNode(const string& id) : identifier(id), bio("Hey there! I'm new here.") {}
    
    void setBio(const string& newBio) { bio = newBio; }
    string getBio() const { return bio; }
    string getIdentifier() const { return identifier; }
    
    bool addConnection(shared_ptr<NetworkNode> node) {
        return connections.insert(node).second;
    }
    
    bool removeConnection(shared_ptr<NetworkNode> node) {
        return connections.erase(node) > 0;
    }
    
    const set<shared_ptr<NetworkNode>>& getConnections() const {
        return connections;
    }
};

class SocialGraph {
private:
    map<string, shared_ptr<NetworkNode>> nodes;
    shared_ptr<NetworkNode> activeNode;
    
    void seedNetwork() {
        vector<string> seedUsers = {
            "emma_smith", "liam_brown", "olivia_jones", "noah_wilson",
            "ava_taylor", "lucas_davis", "sophia_miller", "mason_moore",
            "isabella_white", "ethan_clark", "mia_hall", "james_lee",
            "charlotte_king", "william_wright", "amelia_lopez", "oliver_hill",
            "harper_scott", "henry_green", "evelyn_adams", "alexander_baker"
        };
        
        // Create nodes
        for (const auto& id : seedUsers) {
            nodes[id] = make_shared<NetworkNode>(id);
        }
        
        // Create connections based on social circles
        // magkaka school mate
        connectNodes("emma_smith", {"liam_brown", "olivia_jones", "noah_wilson"});
        connectNodes("liam_brown", {"ava_taylor", "lucas_davis", "emma_smith"});
        connectNodes("olivia_jones", {"sophia_miller", "mason_moore", "emma_smith"});
        
        // magkaka trabaho
        connectNodes("mason_moore", {"isabella_white", "ethan_clark", "mia_hall"});
        connectNodes("isabella_white", {"james_lee", "charlotte_king", "william_wright"});
        connectNodes("ethan_clark", {"amelia_lopez", "oliver_hill", "harper_scott"});
        
        // mga player
        connectNodes("james_lee", {"henry_green", "evelyn_adams", "alexander_baker"});
        connectNodes("william_wright", {"oliver_hill", "harper_scott", "henry_green"});
        connectNodes("amelia_lopez", {"alexander_baker", "evelyn_adams", "charlotte_king"});
        
        // mga reader
        connectNodes("sophia_miller", {"mia_hall", "charlotte_king", "harper_scott"});
        connectNodes("lucas_davis", {"oliver_hill", "evelyn_adams", "henry_green"});
        connectNodes("ava_taylor", {"alexander_baker", "william_wright", "isabella_white"});
        
        // mga ewan
        connectNodes("noah_wilson", {"mia_hall", "oliver_hill", "harper_scott"});
        connectNodes("henry_green", {"sophia_miller", "mason_moore", "emma_smith"});
        connectNodes("evelyn_adams", {"liam_brown", "olivia_jones", "lucas_davis"});
        connectNodes("alexander_baker", {"ava_taylor", "ethan_clark", "james_lee"});
        connectNodes("charlotte_king", {"noah_wilson", "isabella_white", "amelia_lopez"});
        connectNodes("harper_scott", {"william_wright", "mason_moore", "sophia_miller"});
        connectNodes("oliver_hill", {"lucas_davis", "ethan_clark", "william_wright"});
    }
    
    void connectNodes(const string& source, const vector<string>& targets) {
        for (const auto& target : targets) {
            nodes[source]->addConnection(nodes[target]);
            nodes[target]->addConnection(nodes[source]);
        }
    }

public:
    SocialGraph() {
        seedNetwork();
    }

    bool authenticate(const string& id) {
        auto it = nodes.find(id);
        if (it != nodes.end()) {
            activeNode = it->second;
            return true;
        }
        return false;
    }

    bool registerNode(const string& id) {
        if (nodes.find(id) != nodes.end()) return false;
        nodes[id] = make_shared<NetworkNode>(id);
        activeNode = nodes[id];
        return true;
    }

    vector<string> findShortestPath(const string& target) {
        if (!activeNode || nodes.find(target) == nodes.end()) return {};
        
        map<shared_ptr<NetworkNode>, shared_ptr<NetworkNode>> predecessor;
        queue<shared_ptr<NetworkNode>> q;
        set<shared_ptr<NetworkNode>> visited;
        
        q.push(activeNode);
        visited.insert(activeNode);
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            
            if (current->getIdentifier() == target) {
                vector<string> path;
                auto node = current;
                while (node != activeNode) {
                    path.push_back(node->getIdentifier());
                    node = predecessor[node];
                }
                path.push_back(activeNode->getIdentifier());
                reverse(path.begin(), path.end());
                return path;
            }
            
            for (const auto& neighbor : current->getConnections()) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    predecessor[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
        return {};
    }

    set<string> suggestConnections() {
        set<string> suggestions;
        if (!activeNode) return suggestions;
        
        // Get connections of connections (2nd degree)
        for (const auto& connection : activeNode->getConnections()) {
            for (const auto& secondDegree : connection->getConnections()) {
                if (secondDegree != activeNode && 
                    !activeNode->getConnections().count(secondDegree)) {
                    suggestions.insert(secondDegree->getIdentifier());
                }
            }
        }
        return suggestions;
    }

    double calculateNetworkDensity() {
        size_t n = nodes.size();
        if (n <= 1) return 0.0;
        
        size_t totalConnections = 0;
        for (const auto& [_, node] : nodes) {
            totalConnections += node->getConnections().size();
        }
        return static_cast<double>(totalConnections) / (n * (n - 1));
    }

    bool isAuthenticated() const {
        return activeNode != nullptr;
    }
};

class CommandProcessor {
private:
    unique_ptr<SocialGraph> network;
    
public:
    CommandProcessor() : network(make_unique<SocialGraph>()) {}
    
    void processCommand(const string& command) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;
        
        if (cmd == "help") {
            cout << "\nSocial Network Commands\n";
            if (!network->isAuthenticated()) {
                cout << "1. Login <username>    - Sign in to existing account\n";
                cout << "2. Register <username> - Create new account\n";
                cout << "3. Exit               - Quit the program\n";
            } else {
                cout << "1. View Profile       - Display your profile\n";
                cout << "2. Add Connection     - Connect with another user\n";
                cout << "3. Remove Connection  - Remove an existing connection\n";
                cout << "4. List Connections   - Show all your connections\n";
                cout << "5. Suggestions        - View suggested connections\n";
                cout << "6. Update Bio         - Change your profile bio\n";
                cout << "7. Find Path          - Find shortest path to user\n";
                cout << "8. Network Stats      - View network density\n";
                cout << "9. Sign Out          - End current session\n";
                cout << "10. Exit             - Quit the program\n";
            }
        }
        else if (cmd == "1" || cmd == "login") {
            if (!network->isAuthenticated()) {
                string username;
                iss >> username;
                if (network->authenticate(username)) {
                    cout << "Logged in as " << username << "\n";
                } else {
                    cout << "User not found\n";
                }
            } else {
                // View Profile
                cout << "Profile viewing not yet implemented\n";
            }
        }
        else if (cmd == "2" || cmd == "register") {
            if (!network->isAuthenticated()) {
                string username;
                iss >> username;
                if (network->registerNode(username)) {
                    cout << "Account created and logged in as " << username << "\n";
                } else {
                    cout << "Username already exists\n";
                }
            } else {
                // Add Connection
                string username;
                iss >> username;
                cout << "Connection request sent to " << username << "\n";
            }
        }
        else if (cmd == "3") {
            if (!network->isAuthenticated()) {
                // Exit
                cout << "Goodbye!\n";
                exit(0);
            } else {
                // Remove Connection
                cout << "Remove connection feature not yet implemented\n";
            }
        }
        else if (cmd == "4" && network->isAuthenticated()) {
            // List Connections
            cout << "List connections feature not yet implemented\n";
        }
        else if (cmd == "5" && network->isAuthenticated()) {
            // Show suggestions
            auto suggestions = network->suggestConnections();
            cout << "Suggested connections:\n";
            for (const auto& suggestion : suggestions) {
                cout << "- " << suggestion << "\n";
            }
        }
        else if (cmd == "6" && network->isAuthenticated()) {
            // Update Bio
            cout << "Update bio feature not yet implemented\n";
        }
        else if (cmd == "7" && network->isAuthenticated()) {
            // Find Path
            string target;
            iss >> target;
            auto path = network->findShortestPath(target);
            if (!path.empty()) {
                cout << "Path to " << target << ":\n";
                for (size_t i = 0; i < path.size(); ++i) {
                    cout << path[i];
                    if (i < path.size() - 1) cout << " -> ";
                }
                cout << "\n";
            } else {
                cout << "No path found to " << target << "\n";
            }
        }
        else if (cmd == "8" && network->isAuthenticated()) {
            // Network Stats
            double density = network->calculateNetworkDensity();
            cout << "Network density: " << fixed << setprecision(3) << density << "\n";
        }
        else if (cmd == "9" && network->isAuthenticated()) {
            // Sign Out
            cout << "Sign out feature not yet implemented\n";
        }
        else if (cmd == "10" && network->isAuthenticated()) {
            // Exit
            cout << "Goodbye!\n";
            exit(0);
        }
        else if (cmd == "exit") {
            cout << "Goodbye!\n";
            exit(0);
        }
        else {
            cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
};

int main() {
    CommandProcessor processor;
    string command;
    
    cout << "Welcome to Social Network v2.0\n";
    cout << "Enter commands (type 'help' for options, 'exit' to quit):\n";
    
    while (getline(cin, command) && command != "exit") {
        processor.processCommand(command);
    }
    
 