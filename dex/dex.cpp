#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

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
    cout << "Thank you for using the Fashion Tips Chatbot!\n";

    return 0;
}
