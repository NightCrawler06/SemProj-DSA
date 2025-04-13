#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <map>

using namespace std;

struct Player {
    string name;
    int uniformNumber;
    string position;
    int blocks;
    int aces;
    int attacks;
    int errors;
    int points;
    int footFaults;
    int netTouch;
    int lift;
    int rotationFault;


    int score() const {
        return blocks + aces + attacks - errors;
    }
};

struct Team {
    string name;
    vector<Player> players;
    int setScores[3] = {0, 0, 0};
    int setsWon = 0;

    Player getTopScorer() const {
        Player top = players[0];
        for (const Player& p : players) {
            if (p.score() > top.score()) top = p;
        }
        return top;
    }
};

int getValidatedInt(string prompt, int min = 0, int max = 100) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            return value;
        }
    }
}

Player getMostBlocks(const Team& t1, const Team& t2) {
    Player top = t1.players[0];
    for (const Player& p : t1.players)
        if (p.blocks > top.blocks) top = p;
    for (const Player& p : t2.players)
        if (p.blocks > top.blocks) top = p;
    return top;
}

Player getMostErrors(const Team& t1, const Team& t2) {
    Player top = t1.players[0];
    for (const Player& p : t1.players)
        if (p.errors > top.errors) top = p;
    for (const Player& p : t2.players)
        if (p.errors > top.errors) top = p;
    return top;
}

Player getBestDefender(const Team& t1, const Team& t2) {
    Player top = t1.players[0];
    int maxDef = top.blocks + top.aces;  
    for (const Player& p : t1.players)
        if ((p.blocks + p.aces) > maxDef) {
            top = p;
            maxDef = p.blocks + p.aces;
        }
    for (const Player& p : t2.players)
        if ((p.blocks + p.aces) > maxDef) {
            top = p;
            maxDef = p.blocks + p.aces;
        }
    return top;
}

Player getServiceAceLeader(const Team& t1, const Team& t2) {
    Player top = t1.players[0];
    for (const Player& p : t1.players)
        if (p.aces > top.aces) top = p;
    for (const Player& p : t2.players)
        if (p.aces > top.aces) top = p;
    return top;
}

string teamWithMostErrors(const Team& t1, const Team& t2) {
    int errors1 = 0, errors2 = 0;
    for (const Player& p : t1.players) errors1 += p.errors;
    for (const Player& p : t2.players) errors2 += p.errors;
    return (errors1 > errors2) ? t1.name : t2.name;
}

void suggestImprovement(const Team& t1, const Team& t2) {
    Player p = getMostErrors(t1, t2);
    cout << "Most errors were committed by: " << p.name << " (" << p.errors << " errors)\n";
    cout << "Recommendation: Work on reducing unforced errors, especially under pressure.\n";

    cout << "\nTeam Mistake Breakdown:\n";
    displayTeamMistakes(t1);
    displayTeamMistakes(t2);

    cout << "\nSuggestions:\n";
    cout << "- Improve service reception and footwork to reduce rotation/foot faults.\n";
    cout << "- Focus on minimizing net touches during blocks.\n";
    cout << "- Practice clean lifts and carries to avoid unnecessary turnovers.\n";
}


void displayTeamMistakes(const Team& team) {
    int foot = 0, net = 0, liftCarry = 0, rotation = 0;
    for (const Player& p : team.players) {
        foot += p.footFaults;
        net += p.netTouch;
        liftCarry += p.lift;
        rotation += p.rotationFault;
    }
    cout << "\nMistakes for " << team.name << ":\n";
    cout << "Foot Faults: " << foot << "\n";
    cout << "Net Touches: " << net << "\n";
    cout << "Lift/Carry: " << liftCarry << "\n";
    cout << "Rotation Faults: " << rotation << "\n";
}


string toLower(string str) {
    for (char& c : str) c = tolower(c);
    return str;
}


void inputPlayers(Team& team) {
    cout << "\nEntering players for " << team.name << ":\n";
    map<string, int> positionCount;

    for (int i = 0; i < 12; ++i) {
        Player p;
        cout << "\nPlayer #" << (i + 1) << ":\n";
        cout << "Name: ";
        getline(cin, p.name);
        do {
            p.uniformNumber = getValidatedInt("Uniform Number: ", 1, 99);
            bool duplicate = false;
            for (const Player& existing : team.players) {
                if (existing.uniformNumber == p.uniformNumber) {
                    cout << "Uniform number already used. Please enter a unique number.\n";
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) break;
        } while (true);
        
        while (true) {
            cout << "Position (Setter, Libero, Outside Hitter, Opposite Hitter, Middle Blocker): ";
            getline(cin, p.position);
            p.position = toLower(p.position);
        
            if (p.position != "setter" && p.position != "libero" &&
                p.position != "outside hitter" && p.position != "opposite hitter" &&
                p.position != "middle blocker") {
                cout << "Invalid input. Please choose from the given choices.\n";
            } else if ((p.position == "outside hitter" && positionCount[p.position] >= 4) ||
                       (p.position != "outside hitter" && positionCount[p.position] >= 2)) {
                cout << "Maximum allowed players for that position reached.\n";
            } else {
                positionCount[p.position]++;
                break;
            }
        }
        
        p.position = toLower(p.position); 
        p.blocks = getValidatedInt("Blocks: ");
        p.aces = getValidatedInt("Aces: ");
        p.attacks = getValidatedInt("Attacks: ");
        p.errors = getValidatedInt("Errors: ");
        p.points = p.blocks + p.aces + p.attacks - p.errors;
        team.players.push_back(p);
        p.footFaults = getValidatedInt("Foot Faults: ");
        p.netTouch = getValidatedInt("Net Touches: ");
        p.lift = getValidatedInt("Lift/Carry: ");
        p.rotationFault = getValidatedInt("Rotation Faults: ");

    }
}

void inputSetScores(Team& t1, Team& t2, int& setsPlayed) {
    cout << "\nEnter set scores (Max 25 points):\n";
    for (int i = 0; i < 3; ++i) {
        cout << "\nSet " << i + 1 << ":\n";
        t1.setScores[i] = getValidatedInt(t1.name + " score: ", 0, 25);
        t2.setScores[i] = getValidatedInt(t2.name + " score: ", 0, 25);
        if (t1.setScores[i] > t2.setScores[i]) t1.setsWon++;
        else if (t2.setScores[i] > t1.setScores[i]) t2.setsWon++;
        setsPlayed++;
        if (t1.setsWon == 2 || t2.setsWon == 2) break;
    }
}

void printMatchSummary(const Team& t1, const Team& t2, int setsPlayed) {
    cout << "\n=== MATCH SUMMARY ===\n";
    cout << "Sets Played: " << setsPlayed << "\n";
    cout << t1.name << " - Set Scores: ";
    for (int i = 0; i < setsPlayed; ++i) cout << t1.setScores[i] << " ";
    cout << " | Sets Won: " << t1.setsWon << "\n";

    cout << t2.name << " - Set Scores: ";
    for (int i = 0; i < setsPlayed; ++i) cout << t2.setScores[i] << " ";
    cout << " | Sets Won: " << t2.setsWon << "\n";

    cout << "Winner: ";
    if (t1.setsWon > t2.setsWon) cout << t1.name << "\n";
    else if (t2.setsWon > t1.setsWon) cout << t2.name << "\n";
    else cout << "Draw\n";
}


Player getBestSetter(const Team& t1, const Team& t2) {
    Player bestSetter;
    bestSetter.name = "";
    int maxImpact = -1;

    for (const Player& p : t1.players) {
        if (toLower(p.position) == "setter") {
            int impact = p.points + p.aces;
            if (impact > maxImpact) {
                bestSetter = p;
                maxImpact = impact;
            }
        }
    }

    for (const Player& p : t2.players) {
        if (toLower(p.position) == "setter") {
            int impact = p.points + p.aces;
            if (impact > maxImpact) {
                bestSetter = p;
                maxImpact = impact;
            }
        }
    }

    if (bestSetter.name == "") {
        bestSetter.name = "No setter found";
        bestSetter.points = 0;
        bestSetter.aces = 0;
    }

    return bestSetter;
}




void startChat(const Team& t1, const Team& t2, int setsPlayed) {
    string input;
    cout << "\n--- You may now ask questions (type 'exit' to end) ---\n";

    while (true) {
        cout << "\nAsk: ";
        getline(cin, input);
        string q = toLower(input);

        if (q == "exit") break;
        else if (q.find("who won") != string::npos) {
            if (t1.setsWon > t2.setsWon) cout << "Winner: " << t1.name << "\n";
            else if (t2.setsWon > t1.setsWon) cout << "Winner: " << t2.name << "\n";
            else cout << "The match was a draw.\n";
        }
        else if (q.find("score") != string::npos) {
            for (int i = 0; i < setsPlayed; ++i)
                cout << "Set " << (i + 1) << ": " << t1.name << " " << t1.setScores[i]
                     << " - " << t2.name << " " << t2.setScores[i] << "\n";
        }
        else if (q.find("highest scoring") != string::npos || q.find("top scorer") != string::npos) {
            Player top1 = t1.getTopScorer();
            Player top2 = t2.getTopScorer();
            cout << t1.name << " Top Scorer: " << top1.name << " (Score: " << top1.score() << ")\n";
            cout << t2.name << " Top Scorer: " << top2.name << " (Score: " << top2.score() << ")\n";
        }
        else if (q.find("position") != string::npos) {
            string teamName;
            cout << "Which team? (" << t1.name << "/" << t2.name << "): ";
            getline(cin, teamName);
            const Team* team = (toLower(teamName) == toLower(t1.name)) ? &t1 : &t2;
            for (const auto& p : team->players) {
                cout << "#" << p.uniformNumber << " " << p.name << " - " << p.position << "\n";
            }
        }
        else if (q.find("mvp") != string::npos) {
            Player topMVP = t1.getTopScorer();
            Player top2 = t2.getTopScorer();
            if (top2.score() > topMVP.score()) topMVP = top2;
            cout << "MVP: " << topMVP.name << " (" << topMVP.position << ") - Score: " << topMVP.score() << "\n";
        }
        else if (q.find("best setter") != string::npos) {
            Player p = getBestSetter(t1, t2);
            if (p.name == "No setter found")
                cout << "No setter found in player data.\n";
            else
                cout << "Best Setter: " << p.name << " with " << (p.points + p.aces) << " setter impact points.\n";
        }
        else if (q.find("mythical") != string::npos || q.find("mythical 6") != string::npos) {
            vector<string> positions = {"setter", "libero", "outside hitter", "opposite hitter", "middle blocker"};
            for (const string& pos : positions) {
                Player best = {"", 0, "", 0, 0, 0, 0, 1000};
                for (const Player& p : t1.players) {
                    if (toLower(p.position) == pos && p.score() > best.score()) best = p;
                }
                for (const Player& p : t2.players) {
                    if (toLower(p.position) == pos && p.score() > best.score()) best = p;
                }
                if (best.name != "") {
                    cout << "Best " << pos << ": " << best.name << " - Score: " << best.score() << "\n";
                }
            }
        }
        else if (q.find("most blocks") != string::npos) {
            Player p = getMostBlocks(t1, t2);
            cout << "Most blocks: " << p.name << " with " << p.blocks << " blocks.\n";
        }
        else if (q.find("most errors") != string::npos) {
            Player p = getMostErrors(t1, t2);
            cout << "Most errors: " << p.name << " with " << p.errors << " errors.\n";
        }
        else if (q.find("best defender") != string::npos) {
            Player p = getBestDefender(t1, t2);
            cout << "Best defender: " << p.name << " with total defensive impact of " << (p.blocks + p.aces) << ".\n";
        }
        else if (q.find("most service aces") != string::npos || q.find("service ace leader") != string::npos) {
            Player p = getServiceAceLeader(t1, t2);
            cout << "Service Ace Leader: " << p.name << " with " << p.aces << " aces.\n";
        }
        else if (q.find("team with most errors") != string::npos) {
            string team = teamWithMostErrors(t1, t2);
            cout << "Team with most errors: " << team << ".\n";
        }
        else if (q.find("what needs improvement") != string::npos || q.find("recommendation") != string::npos) {
            suggestImprovement(t1, t2);
        }
        else if (q.find("common mistakes") != string::npos) {
            displayTeamMistakes(t1);
            displayTeamMistakes(t2);
        }
        
        
        else {
            cout << "I didn't understand. Try asking: Who won? What's the score? Top scorer? Positions?\n";
        }
    }
}

int main() {
    Team team1, team2;
    int setsPlayed = 0;
    string gender;
    cout << "----------------------------------------------------\n";
    cout << "Welcome to GameAnalystBot - Volleyball Game Analyzer\n";
    cout << "----------------------------------------------------\n";
    cout << "Enter division (Male/Female): ";
    getline(cin, gender);
    cout << "Enter Team 1 Name: ";
    getline(cin, team1.name);
    cout << "Enter Team 2 Name: ";
    getline(cin, team2.name);

    inputPlayers(team1);
    inputPlayers(team2);
    inputSetScores(team1, team2, setsPlayed);
    printMatchSummary(team1, team2, setsPlayed);
    startChat(team1, team2, setsPlayed);

    cout << "\nThank you for using GameAnalystBot!\n";

    

    return 0;
}
