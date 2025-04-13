#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

struct Gadget {
    string name;
    string specs;
    string price;
    vector<string> suggestions;
    vector<string> tools;
    vector<string> software;
};

void showOptions() {
    cout << "\n+-------------------------+\n";
    cout << "|     Gadget Options      |\n";
    cout << "+-------------------------+\n";
    cout << "[1] View Specifications\n";
    cout << "[2] View Price\n";
    cout << "[3] Suggested Uses/Alternatives\n";
    cout << "[4] Recommended Tools\n";
    cout << "[5] Recommended Software\n";
    cout << "[0] Exit Gadget Info\n";
}

void displayVector(const vector<string>& list) {
    for (const auto& item : list) {
        cout << "- " << item << endl;
    }
}

int main() {
    map<string, vector<Gadget>> catalog;

    catalog["phone"] = {
        {
            "iPhone 13",
            "Display: 6.1-inch OLED\nProcessor: A15 Bionic\nRAM: 4GB\nStorage: 128/256/512GB\nBattery: 3240mAh",
            "PHP45,000 - PHP55,000",
            {"Great for photography", "Ideal for students", "Long iOS support"},
            {"Magsafe Charger", "Tempered Glass", "Lightning Cable"},
            {"iMovie", "GarageBand", "Widgetsmith"}
        },
        {
            "iPhone 14",
            "Display: 6.1-inch OLED\nProcessor: A15 Bionic (5-core GPU)\nRAM: 6GB\nStorage: 128/256/512GB\nBattery: 3279mAh",
            "PHP55,000 - PHP65,000",
            {"Upgraded camera", "Emergency SOS", "Long-term use"},
            {"Magsafe Battery Pack", "Silicone Case", "Lightning EarPods"},
            {"Apple Maps", "ProCam", "Health App"}
        },
        {
            "Samsung Galaxy S22",
            "Display: 6.1-inch Dynamic AMOLED\nProcessor: Snapdragon 8 Gen 1\nRAM: 8GB\nStorage: 128/256GB\nBattery: 3700mAh",
            "PHP39,000 - PHP48,000",
            {"Great display quality", "Ideal for multitasking", "Compact flagship"},
            {"Wireless Charger", "Smart Clear View Cover", "Screen Protector"},
            {"Samsung Notes", "Dex", "Good Lock"}
        },
        {
            "Samsung Galaxy A54",
            "Display: 6.4-inch Super AMOLED\nProcessor: Exynos 1380\nRAM: 6/8GB\nStorage: 128/256GB\nBattery: 5000mAh",
            "PHP20,000 - PHP25,000",
            {"Value for money", "Long battery life", "Solid build"},
            {"USB-C Charger", "Protective Case", "Bluetooth Earbuds"},
            {"One UI", "Samsung Health", "Google Assistant"}
        },
        {
            "Samsung Galaxy Z Flip4",
            "Display: 6.7-inch Foldable AMOLED\nProcessor: Snapdragon 8+ Gen 1\nRAM: 8GB\nStorage: 128/256/512GB\nBattery: 3700mAh",
            "PHP55,000 - PHP70,000",
            {"Unique foldable design", "Best for casual users", "Compact form"},
            {"Clear Cover with Ring", "Wireless Charger Duo", "Flip Mirror Film"},
            {"FlexCam", "Multi Window", "Google Duo"}
        }
    };

    catalog["laptop"] = {
        {
            "Acer Aspire 5",
            "Display: 15.6-inch FHD\nProcessor: Ryzen 5 5500U\nRAM: 8GB\nStorage: 512GB SSD\nBattery: 10 hrs",
            "PHP32,000 - PHP38,000",
            {"Budget productivity", "School & office use", "Basic editing"},
            {"Cooling Pad", "USB Mouse", "Laptop Sleeve"},
            {"MS Office", "Zoom", "LibreOffice"}
        },
        {
            "Acer Swift 3",
            "Display: 14-inch FHD\nProcessor: Intel i5 12th Gen\nRAM: 8GB\nStorage: 512GB SSD\nBattery: 13 hrs",
            "PHP38,000 - PHP45,000",
            {"Lightweight design", "Ideal for students", "Travel friendly"},
            {"USB-C Hub", "Laptop Stand", "Webcam Cover"},
            {"Evernote", "Notion", "Edge"}
        },
        {
            "Lenovo IdeaPad Slim 3",
            "Display: 15.6-inch FHD\nProcessor: Ryzen 5 5500U\nRAM: 8GB\nStorage: 512GB SSD\nBattery: 9 hrs",
            "PHP28,000 - PHP34,000",
            {"Best for online class", "Office-ready", "Affordable"},
            {"USB Keyboard", "HDMI Cable", "Mousepad"},
            {"Chrome", "Google Docs", "Microsoft Teams"}
        },
        {
            "Lenovo Legion 5",
            "Display: 15.6-inch 165Hz IPS\nProcessor: Ryzen 7 5800H\nRAM: 16GB\nStorage: 1TB SSD\nBattery: 6 hrs",
            "PHP60,000 - PHP75,000",
            {"Gaming and performance", "Heavy workloads", "Great cooling"},
            {"Gaming Mouse", "Mechanical Keyboard", "Headset"},
            {"Steam", "OBS Studio", "Discord"}
        },
        {
            "ASUS VivoBook 15",
            "Display: 15.6-inch FHD\nProcessor: Intel i3/i5\nRAM: 8GB\nStorage: 512GB SSD\nBattery: 8 hrs",
            "PHP26,000 - PHP32,000",
            {"Everyday use", "Good battery", "Nice keyboard"},
            {"USB Dock", "Portable SSD", "Backpack"},
            {"Spotify", "Chrome", "WPS Office"}
        }
    };

    string again = "yes";
    while (again == "yes") {
        string type;
        cout << "\n+=============================================+\n";
        cout << "|         TECHNICAL ADVISOR CHATBOT           |\n";
        cout << "|     Choose a gadget type to get started     |\n";
        cout << "+=============================================+\n";
        cout << "Available types: phone, laptop\n";
        cout << "Enter gadget type: ";
        getline(cin, type);
        for (char& c : type) c = tolower(c);

        if (catalog.find(type) != catalog.end()) {
            const auto& list = catalog[type];
            cout << "\nAvailable " << type << "s:\n";
            for (size_t i = 0; i < list.size(); ++i) {
                cout << "[" << i + 1 << "] " << list[i].name << "\n";
            }

            int choice;
            cout << "Enter your choice (1-" << list.size() << "): ";
            cin >> choice;
            cin.ignore();

            if (choice < 1 || choice > list.size()) {
                cout << "Invalid gadget choice.\n";
                continue;
            }

            const Gadget& g = list[choice - 1];
            int option = -1;
            while (option != 0) {
                showOptions();
                cout << "Enter option: ";
                cin >> option;
                cin.ignore();

                switch (option) {
                    case 1:
                        cout << "\n[Specifications for " << g.name << "]\n" << g.specs << "\n";
                        break;
                    case 2:
                        cout << "\n[Price for " << g.name << "]\n" << g.price << "\n";
                        break;
                    case 3:
                        cout << "\n[Suggestions / Alternatives]\n";
                        displayVector(g.suggestions);
                        break;
                    case 4:
                        cout << "\n[Recommended Tools]\n";
                        displayVector(g.tools);
                        break;
                    case 5:
                        cout << "\n[Recommended Software]\n";
                        displayVector(g.software);
                        break;
                    case 0:
                        cout << "Returning to main menu...\n";
                        break;
                    default:
                        cout << "Invalid option.\n";
                }
            }
        } else {
            cout << "Gadget type not available.\n";
        }

        cout << "\nCheck another gadget? (yes/no): ";
        getline(cin, again);
        for (char& c : again) c = tolower(c);
    }

    cout << "\n+===========================================+\n";
    cout << "|     Thank you for using TechAdvisorBot!   |\n";
    cout << "|         Stay informed. Stay smart.        |\n";
    cout << "+===========================================+\n";

    return 0;
}
