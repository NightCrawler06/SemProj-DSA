#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Song {
    string title, artist;
};

queue<Song> playlistQueue;    // Playlist (Queue)
stack<Song> recentlyPlayed;   // History (Stack)
vector<string> musicTips = {
    "Tip: Mix slow and fast songs for a balanced playlist.",
    "Suggestion: Add a song that always improves your mood.",
    "Try including one song from each genre you enjoy.",
    "Mood tip: A good playlist reflects your current energy.",
    "Think about songs that work well as openers or closers."
};

void say(const string& message) {
    cout << "[MusicBot] " << message << "\n";
}

void guideMessage() {
    srand(static_cast<unsigned int>(time(0)));
    int idx = rand() % musicTips.size();
    say(musicTips[idx]);
}

void addSong() {
    Song newSong;
    cout << "Enter song title: ";
    getline(cin, newSong.title);
    cout << "Enter artist name: ";
    getline(cin, newSong.artist);

    playlistQueue.push(newSong);
    say("Added: '" + newSong.title + "' by " + newSong.artist);
    guideMessage();
}

void playNext() {
    if (playlistQueue.empty()) {
        say("Playlist is empty. Please add more songs.");
        return;
    }
    Song current = playlistQueue.front();
    playlistQueue.pop();

    say("Now playing: " + current.title + " by " + current.artist);
    recentlyPlayed.push(current);
}

void showHistory() {
    if (recentlyPlayed.empty()) {
        say("No songs have been played yet.");
        return;
    }

    say("Recently played songs:");
    stack<Song> temp = recentlyPlayed;
    while (!temp.empty()) {
        Song s = temp.top();
        temp.pop();
        cout << "- " << s.title << " by " << s.artist << "\n";
    }
}

void viewUpcoming() {
    if (playlistQueue.empty()) {
        say("The playlist queue is currently empty.");
        return;
    }

    say("Upcoming songs in your playlist:");
    queue<Song> temp = playlistQueue;
    while (!temp.empty()) {
        Song s = temp.front();
        temp.pop();
        cout << "- " << s.title << " by " << s.artist << "\n";
    }
}

int main() {
    say("Welcome to Music Guide and Playlist Creator");
    string input;

    while (true) {
        cout << "\nChoose an action:\n";
        cout << "1. Add a song\n";
        cout << "2. Play next song\n";
        cout << "3. View upcoming playlist\n";
        cout << "4. View recently played\n";
        cout << "5. Exit\n";
        cout << "> ";
        getline(cin, input);

        if (input == "1") addSong();
        else if (input == "2") playNext();
        else if (input == "3") viewUpcoming();
        else if (input == "4") showHistory();
        else if (input == "5") {
            say("Exiting Music Guide and Playlist Creator.");
            break;
        } else {
            say("Invalid input. Please enter a number between 1 and 5.");
        }
    }

    return 0;
}
