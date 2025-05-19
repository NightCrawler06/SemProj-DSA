#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool isAlphabetic(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return !str.empty();
}

bool isYesOrNo(const string& input) {
    string lower = toLower(input);
    return (lower == "yes" || lower == "no");
}

void showCollection() {
    ifstream inFile("collection.txt");
    if (!inFile) {
        cout << "No saved collection found.\n";
        return;
    }

    cout << "\n--- Saved Fashion Collection ---\n";
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    cout << "--------------------------------\n";
    inFile.close();
}

void clearCollection() {
    ofstream outFile("collection.txt", ios::trunc);
    outFile.close();
    cout << "Saved collection has been cleared.\n";
}

int main() {
    string gender, style, region, native, season, bodyType;
    int age;

    cout << "Welcome to the Fashion Tips Chatbot!\n";
    cout << "Let's get started with a few questions.\n\n";

    do {
        cout << "1. What is your gender (male/female)? ";
        getline(cin, gender);
        gender = toLower(gender);
        if (!isAlphabetic(gender) || (gender != "male" && gender != "female")) {
            cout << "Please enter 'male' or 'female'.\n";
        }
    } while (!isAlphabetic(gender) || (gender != "male" && gender != "female"));

    while (true) {
        cout << "2. How old are you? ";
        cin >> age;

        if (cin.fail() || age < 1 || age > 120) {
            cout << "Please enter a valid age between 1 and 120.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            break;
        }
    }

    do {
        cout << "3. What is your preferred style (casual, formal, streetwear, minimalist)? ";
        getline(cin, style);
        style = toLower(style);
        if (!isAlphabetic(style) || 
            (style != "casual" && style != "formal" && style != "streetwear" && style != "minimalist")) {
            cout << "Please enter 'casual', 'formal', 'streetwear', or 'minimalist'.\n";
        }
    } while (!isAlphabetic(style) || 
             (style != "casual" && style != "formal" && style != "streetwear" && style != "minimalist"));

    do {
        cout << "4. Which region or place are you from? ";
        getline(cin, region);
        if (!isAlphabetic(region)) {
            cout << "Please enter a valid region or place.\n";
        }
    } while (!isAlphabetic(region));

    do {
        cout << "5. Are you a native of that region? (yes/no): ";
        getline(cin, native);
        if (!isYesOrNo(native)) {
            cout << "Please enter 'yes' or 'no'.\n";
        }
    } while (!isYesOrNo(native));

    do {
        cout << "6. What season or event are you preparing for? (summer, winter, wedding): ";
        getline(cin, season);
        season = toLower(season);
        if (!isAlphabetic(season) || (season != "summer" && season != "winter" && season != "wedding")) {
            cout << "Please enter 'summer', 'winter', or 'wedding'.\n";
        }
    } while (!isAlphabetic(season) || (season != "summer" && season != "winter" && season != "wedding"));

    do {
        cout << "7. How would you describe your body type (chubby, skinny, normal)? ";
        getline(cin, bodyType);
        bodyType = toLower(bodyType);
        if (bodyType != "chubby" && bodyType != "skinny" && bodyType != "normal") {
            cout << "Please enter 'chubby', 'skinny', or 'normal'.\n";
        }
    } while (bodyType != "chubby" && bodyType != "skinny" && bodyType != "normal");

    cout << "\nFashion Suggestion:\n";
    cout << "--------------------------------------------------\n";
    cout << "For a " << age << "-year-old " << gender << " from " << region
         << " who prefers a " << style << " style";

    if (toLower(native) == "yes") {
        cout << " and is a native of the area";
    }

    cout << ", with a " << bodyType << " body type, preparing for " << season << ", here's our recommendation:\n\n";

    if (style == "minimalist") {
        cout << "- Stick to neutral tones: white, black, beige, and gray.\n";
        cout << "- Try these combos: white + beige, black + gray, olive + cream.\n";
        cout << "- Choose clean cuts, simple lines, and no prints.\n";
    }

    if (season == "winter") {
        cout << "- Wear layered clothing: thick jackets, hoodies, or coats.\n";
        cout << "- Choose warm tones: navy, maroon, dark green.\n";
        cout << "- Accessories like scarves and boots are recommended.\n";
    } else if (season == "summer") {
        cout << "- Opt for lightweight fabrics like cotton or linen.\n";
        cout << "- Use light colors: white, pastel blue, beige.\n";
        cout << "- Sneakers or sandals are perfect.\n";
    } else if (season == "wedding") {
        cout << "- Choose formal wear: dresses or suits.\n";
        cout << "- Elegant tones like black, navy, or cream work well.\n";
        cout << "- Add minimal accessories to match the theme.\n";
    }

    cout << "--------------------------------------------------\n";

    string userCommand;
    while (true) {
        cout << "\nHow can I assist you next? (e.g., 'I want to save this attire', 'show my collection', 'clear collection', 'exit')\n> ";
        getline(cin, userCommand);
        string lowerCommand = toLower(userCommand);

        if (lowerCommand.find("save") != string::npos) {
            ofstream outFile("collection.txt", ios::app);
            outFile << "Fashion Suggestion:\n";
            outFile << "For a " << age << "-year-old " << gender << " from " << region
                    << " with a " << bodyType << " body type, who prefers a " << style
                    << " style preparing for " << season << ":\n";
            if (style == "minimalist") {
                outFile << "- Neutral tones: white, black, beige, and gray.\n";
                outFile << "- Combos: white + beige, black + gray, olive + cream.\n";
                outFile << "- Clean cuts, no prints.\n";
            }
            if (season == "winter") {
                outFile << "- Layered clothing: jackets, coats.\n";
                outFile << "- Warm tones: navy, maroon.\n";
            } else if (season == "summer") {
                outFile << "- Lightweight fabrics: cotton, linen.\n";
                outFile << "- Light colors: white, beige.\n";
            } else if (season == "wedding") {
                outFile << "- Formal wear: dresses or suits.\n";
                outFile << "- Elegant colors: black, cream.\n";
            }
            outFile << "--------------------------------------------------\n\n";
            outFile.close();
            cout << "Fashion suggestion added to your collection.\n";
        } else if (lowerCommand.find("show") != string::npos || lowerCommand.find("view") != string::npos) {
            showCollection();
        } else if (lowerCommand.find("clear") != string::npos) {
            clearCollection();
        } else if (lowerCommand.find("exit") != string::npos || lowerCommand.find("quit") != string::npos) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Sorry, I didn't understand that. Try something like 'save this', 'show my collection', or 'exit'.\n";
        }
    }

    return 0;
}
