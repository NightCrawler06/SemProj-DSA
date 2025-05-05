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
    string gender, style, region, native, season;
    int age;

    cout << "Welcome to the Fashion Tips Chatbot!\n";
    cout << "Let's get started with a few questions.\n\n";

    do {
        cout << "1. What is your gender (male/female)? ";
        getline(cin, gender);
        toLower(gender);
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
        cout << "3. What is your preferred style (casual, formal, streetwear)? ";
        getline(cin, style);
        toLower(style);
        if (!isAlphabetic(style) || (style != "casual" && style != "formal" && style != "streetwear")) {
            cout << "Please enter 'casual', 'formal', or 'streetwear'.\n";
        }
    } while (!isAlphabetic(style) || (style != "casual" && style != "formal" && style != "streetwear"));

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
        toLower(season);
        if (!isAlphabetic(season) || (season != "summer" && season != "winter" && season != "wedding")) {
            cout << "Please enter 'summer', 'winter', or 'wedding'.\n";
        }
    } while (!isAlphabetic(season) || (season != "summer" && season != "winter" && season != "wedding"));

    cout << "\nFashion Suggestion:\n";
    cout << "--------------------------------------------------\n";
    cout << "For a " << age << "-year-old " << gender << " from " << region
         << " who prefers a " << style << " style";

    if (toLower(native) == "yes") {
        cout << " and is a native of the area";
    }

    cout << ", preparing for " << season << ", here's our recommendation:\n\n";

    string seasonLower = toLower(season);
    if (seasonLower == "winter" || seasonLower == "cold") {
        cout << "- Wear layered clothing: thick jackets, hoodies, or coats.\n";
        cout << "- Choose warm tones: navy, maroon, dark green.\n";
        cout << "- Accessories like scarves and boots are recommended.\n";
    } else if (seasonLower == "summer") {
        cout << "- Opt for lightweight fabrics like cotton or linen.\n";
        cout << "- Use light colors: white, pastel blue, beige.\n";
        cout << "- Sneakers or sandals are perfect.\n";
    } else if (seasonLower == "wedding" || seasonLower == "formal event") {
        cout << "- Choose formal wear: dresses or suits.\n";
        cout << "- Elegant tones like black, navy, or cream work well.\n";
        cout << "- Add minimal accessories to match the theme.\n";
    } else {
        cout << "- Stick to your personal style with thoughtful layering.\n";
        cout << "- Try color combinations like olive + white or black + denim.\n";
        cout << "- Wear what makes you confident and comfortable.\n";
    }

    cout << "--------------------------------------------------\n";

    string menuChoice;
    do {
        cout << "\nWhat would you like to do next?\n";
        cout << "1. Save this suggestion to your collection\n";
        cout << "2. View saved collection\n";
        cout << "3. Clear saved collection\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        getline(cin, menuChoice);

        if (menuChoice == "1") {
            ofstream outFile("collection.txt", ios::app);
            if (outFile.is_open()) {
                outFile << "--------------------------------------------------\n";
                outFile << "Fashion Suggestion:\n";
                outFile << "For a " << age << "-year-old " << gender << " from " << region
                        << " who prefers a " << style << " style";
                if (toLower(native) == "yes") {
                    outFile << " and is a native of the area";
                }
                outFile << ", preparing for " << season << ":\n";

                if (seasonLower == "winter" || seasonLower == "cold") {
                    outFile << "- Layered clothing: thick jackets, hoodies, or coats.\n";
                    outFile << "- Warm tones: navy, maroon, dark green.\n";
                    outFile << "- Accessories like scarves and boots.\n";
                } else if (seasonLower == "summer") {
                    outFile << "- Lightweight fabrics like cotton or linen.\n";
                    outFile << "- Light colors: white, pastel blue, beige.\n";
                    outFile << "- Sneakers or sandals.\n";
                } else if (seasonLower == "wedding" || seasonLower == "formal event") {
                    outFile << "- Formal wear: dresses or suits.\n";
                    outFile << "- Elegant tones: black, navy, cream.\n";
                    outFile << "- Minimal accessories.\n";
                } else {
                    outFile << "- Personal style with thoughtful layering.\n";
                    outFile << "- Colors like olive + white or black + denim.\n";
                    outFile << "- Confidence and comfort first.\n";
                }

                outFile << "--------------------------------------------------\n\n";
                outFile.close();
                cout << "Fashion suggestion added to your collection.\n";
            } else {
                cout << "Error saving the suggestion.\n";
            }

        } else if (menuChoice == "2") {
            showCollection();
        } else if (menuChoice == "3") {
            clearCollection();
        } else if (menuChoice == "4") {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid choice. Please enter 1-4.\n";
        }

    } while (menuChoice != "4");

    return 0;
}
