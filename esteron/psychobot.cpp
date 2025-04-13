#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <map>

using namespace std;

string getDateTimeNow() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", now);
    return string(buf);
}


void showMotivation() {
    string quotes[] = {
        "Believe in yourself and all that you are.",
        "Every day is a second chance.",
        "You are stronger than you think.",
        "Progress, not perfection.",
        "You matter. Your story matters.",
        "This too shall pass.",
        "Even the darkest night will end and the sun will rise.",
        "Don't be afraid to slow down. Healing takes time.",
        "You don't need to have it all figured out to move forward.",
        "Small steps every day lead to big changes.",
        "You've made it through 100% of your worst days.",
        "Be proud of how far you've come, not just how far you have to go.",
        "You're allowed to rest. You're not a machine.",
        "Your feelings are valid. Your presence matters.",
        "Some days you just survive. And that's okay."
    };

    int totalQuotes = sizeof(quotes) / sizeof(quotes[0]);
    int index = rand() % totalQuotes;
    cout << "\n+-------------------- Inspiration --------------------------+\n";
    cout << "| " << quotes[index] << "\n";
    cout << "+-----------------------------------------------------------+\n";

}

void saveEntry(const string& mood, const string& thoughts, const string& date) {
    ofstream file("previous_day.txt");
    if (file.is_open()) {
        file << date << endl;
        file << mood << endl;
        file << thoughts << endl;
        file.close();
    }
    ofstream log("mood_history.txt", ios::app);
    if (log.is_open()) {
        log << date << " | Mood: " << mood << " | Thoughts: " << thoughts << "\n";
        log.close();
    }


}

bool loadPreviousEntry(string& prevDate, string& prevMood, string& prevThoughts) {
    ifstream file("previous_day.txt");
    if (!file.is_open()) return false;

    getline(file, prevDate);
    getline(file, prevMood);
    getline(file, prevThoughts);
    file.close();
    return true;
}

void showMoodStats() {
    ifstream log("mood_history.txt");
    if (!log.is_open()) return;

    map<string, int> moodCount;
    string line;
    while (getline(log, line)) {
        size_t moodPos = line.find("Mood: ");
        if (moodPos != string::npos) {
            size_t endPos = line.find(" |", moodPos);
            string mood = line.substr(moodPos + 6, endPos - (moodPos + 6));
            moodCount[mood]++;
        }
    }
    log.close();

    cout << "\n+-------------------- Mood Summary -------------------------+\n";
    for (const auto& pair : moodCount) {
        cout << "- " << pair.first << ": " << pair.second << " time(s)\n";
    }
    cout << "+-----------------------------------------------------------+\n";
}



int main() {
    srand(time(0)); // Seed random for motivational quote

    cout << "\n===========================================================\n";
    cout << "|         PSYCHOBOT - Daily Emotional Wellness Chat        |\n";
    cout << "===========================================================\n";


    string prevDate, prevMood, prevThoughts;
    if (loadPreviousEntry(prevDate, prevMood, prevThoughts)) {
        cout << "\n+-------------------- Previous Check-In --------------------+\n";
        cout << "| Last session date : " << prevDate << "\n";   
        cout << "| Mood               : " << prevMood << "\n";
        cout << "| Thoughts           : " << prevThoughts << "\n";
        cout << "+-----------------------------------------------------------+\n";  

        cout << "\nHow are you feeling today compared to yesterday? (better/same/worse): ";
        string comparison;
        getline(cin, comparison);
        cout << "Thanks for sharing. Let's reflect on today now.\n\n";
    } else {
        cout << "+-----------------------------------------------------------+\n";
        cout << "|           Looks like this is your first session!          |\n";  
        cout << "|                Welcome to Psychobot !                     |\n";
        cout << "+-----------------------------------------------------------+\n\n";

    }

    string date = getDateTimeNow();
    string mood, thoughts;

    cout << "\n+-------------------- Today's Check-In ---------------------+\n";
    cout << "| How are you feeling today?                               |\n";
    cout << "+-----------------------------------------------------------+\n";
    cout << "Mood (happy/sad/stressed/etc): ";

    getline(cin, mood);

    cout << "Would you like to share a bit more about your day?: ";
    getline(cin, thoughts);

    saveEntry(mood, thoughts, date);

    showMotivation();
    showMoodStats();

    cout << "\n===========================================================\n";
    cout << "|   Thank you for checking in with Psychobot. Stay kind!   |\n";
    cout << "===========================================================\n";
        return 0;
}
