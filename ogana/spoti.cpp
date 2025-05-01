#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random> 

using namespace std;

struct Song {
    string title, artist;
    string genre; 
};

queue<Song> playlistQueue;        
stack<Song> recentlyPlayed;       
vector<Song> allSongsArray;       
list<Song> favoritesList;          

vector<string> musicTips = {
    "Tip: Mix slow and fast OPM songs for a balanced playlist.",
    "Suggestion: OPM ballads can create a nostalgic mood.",
    "Try exploring both classic and new OPM artists.",
    "Mood tip: Filipino songs have unique emotional depth.",
    "Think about mixing Tagalog and English OPM tracks for variety."
};

void say(const string& message) {
    cout << "[PinoyMusicBot] " << message << "\n";
}

void guideMessage() {
    srand(static_cast<unsigned int>(time(0)));
    int idx = rand() % musicTips.size();
    say(musicTips[idx]);
}

void populateDataStructures() {

    allSongsArray = {
        
        {"Pahina", "Cup of Joe", "Alternative Rock"},
        {"Suntok sa Buwan", "Cup of Joe", "Alternative Rock"},
        {"Sugod", "Cup of Joe", "Alternative Rock"},
        {"As Love Fades", "Cup of Joe", "Alternative Rock"},
        {"Dying Hour", "Cup of Joe", "Alternative Rock"},
        {"Ikaw Pa Rin Pala", "Cup of Joe", "Alternative Rock"},
        {"Umagang Kay Ganda", "Cup of Joe", "Alternative Rock"},
        {"Awit Para Sa'yo", "Cup of Joe", "Alternative Rock"},
        {"Dahan Dahan", "Cup of Joe", "Alternative Rock"},
        {"Hanggang Sa Muli", "Cup of Joe", "Alternative Rock"},
        {"Tingin", "Cup of Joe", "Alternative Rock"},
        {"Patutunguhan", "Cup of Joe", "Alternative Rock"},
        {"Ikaw Pa Rin Ang Pipiliin Ko", "Cup of Joe", "Alternative Rock"},
        {"Estranghero", "Cup of Joe", "Alternative Rock"},
        {"Tatlong Buwan", "Cup of Joe", "Alternative Rock"},
        {"Huwag Na Lang Ituloy", "Cup of Joe", "Alternative Rock"},
        {"Mananatili", "Cup of Joe", "Alternative Rock"},
        {"Solusyon", "Cup of Joe", "Alternative Rock"},
        {"Araw-Araw (Cup of Joe version)", "Cup of Joe", "Alternative Rock"},
        {"Kwentuhan", "Cup of Joe", "Alternative Rock"},
        {"Multo", "Cup of Joe", "Alternative Rock"},      
        
        {"Ang Huling El Bimbo", "Eraserheads", "Rock"},
        {"Magasin", "Eraserheads", "Rock"},
        {"Alapaap", "Eraserheads", "Rock"},
        {"With A Smile", "Eraserheads", "Rock"},
        {"Toyang", "Eraserheads", "Rock"},
        {"Pare Ko", "Eraserheads", "Rock"},
        {"Ligaya", "Eraserheads", "Rock"},
        {"Minsan", "Eraserheads", "Rock"},
        {"Sembreak", "Eraserheads", "Rock"},
        {"Kaliwete", "Eraserheads", "Rock"},
        {"Overdrive", "Eraserheads", "Rock"},
        {"Spolarium", "Eraserheads", "Rock"},
        {"Huwag Mo Nang Itanong", "Eraserheads", "Rock"},
        {"Torpedo", "Eraserheads", "Rock"},
        {"Kailan", "Eraserheads", "Rock"},
        
        
        {"214", "Rivermaya", "Rock"},
        {"Hinahanap-Hanap Kita", "Rivermaya", "Rock"},
        {"Babalik Ka Rin", "Rivermaya", "Rock"},
        {"Himala", "Rivermaya", "Rock"},
        {"Kisapmata", "Rivermaya", "Rock"},
        {"Balisong", "Rivermaya", "Rock"},
        {"You'll Be Safe Here", "Rivermaya", "Rock"},
        {"Elesi", "Rivermaya", "Rock"},
        {"Liwanag sa Dilim", "Rivermaya", "Rock"},
        {"Umaaraw, Umuulan", "Rivermaya", "Rock"},
        
        
        {"Harana", "Parokya ni Edgar", "Rock"},
        {"Halaga", "Parokya ni Edgar", "Rock"},
        {"Your Song", "Parokya ni Edgar", "Rock"},
        {"Buloy", "Parokya ni Edgar", "Rock"},
        {"Bagsakan", "Parokya ni Edgar", "Hip-hop/Rock"},
        {"Silvertoes", "Parokya ni Edgar", "Rock"},
        {"The Yes Yes Show", "Parokya ni Edgar", "Rock"},
        {"Para Sa'yo", "Parokya ni Edgar", "Rock"},
        {"Pangarap Lang Kita", "Parokya ni Edgar ft. Happee", "Rock"},
        {"Inuman Na", "Parokya ni Edgar", "Rock"},
        
        
        {"Kathang Isip", "Ben&Ben", "Folk Pop"},
        {"Maybe the Night", "Ben&Ben", "Folk Pop"},
        {"Lifetime", "Ben&Ben", "Folk Pop"},
        {"Pagtingin", "Ben&Ben", "Folk Pop"},
        {"Araw-Araw", "Ben&Ben", "Folk Pop"},
        {"Ride Home", "Ben&Ben", "Folk Pop"},
        {"Leaves", "Ben&Ben", "Folk Pop"},
        {"Sentimiento", "Ben&Ben", "Folk Pop"},
        {"Masyado Pang Maaga", "Ben&Ben", "Folk Pop"},
        {"Nakikinig Ka Ba Sa Akin", "Ben&Ben", "Folk Pop"},
        {"Doors", "Ben&Ben", "Folk Pop"},
        {"Bibingka", "Ben&Ben", "Folk Pop"},
        
        
        {"Paubaya", "Moira Dela Torre", "Pop Ballad"},
        {"Paraluman", "Adie", "Pop Ballad"},
        {"Tahanan", "Adie", "Pop Ballad"},
        {"Pagsamo", "Arthur Nery", "R&B"},
        {"Habang Buhay", "Zack Tabudlo", "Pop"},
        {"Habang Buhay", "December Avenue", "Alternative Rock"},
        {"Mahika", "Adie & Janine Berdin", "Pop"},
        {"Dati", "Ben&Ben & Moira Dela Torre", "Folk Pop"},
        {"Binibini", "Zack Tabudlo", "Pop"},
        {"Sana", "I Belong to the Zoo", "Pop Rock"},
        {"Lunod", "Ben&Ben, Zild, Juan Karlos", "Alternative"},
        
        
        {"Tadhana", "UDD", "Alternative"},
        {"Oo", "UDD", "Alternative"},
        {"Feelings", "UDD", "Alternative"},
        {"Luna", "UDD", "Alternative"},
        {"Indak", "UDD", "Alternative"},
        {"Anino", "UDD", "Alternative"},
        {"Sigurado", "UDD", "Alternative"},
        {"Parks", "UDD", "Alternative"},
        
        
        {"Sa Ngalan ng Pag-ibig", "December Avenue", "Alternative Rock"},
        {"Kung 'Di Rin Lang Ikaw", "December Avenue", "Alternative Rock"},
        {"Huling Sandali", "December Avenue", "Alternative Rock"},
        {"Dahan", "December Avenue", "Alternative Rock"},
        {"Bulong", "December Avenue", "Alternative Rock"},
        {"Sleep Tonight", "December Avenue", "Alternative Rock"},
        
        
        {"Ikaw Lamang", "Silent Sanctuary", "Rock"},
        {"Pasensya Ka Na", "Silent Sanctuary", "Rock"},
        {"Meron Nang Iba", "Silent Sanctuary", "Rock"},
        {"Sa'yo", "Silent Sanctuary", "Rock"},
        {"Binaribad ang Pagsisisi", "Silent Sanctuary", "Rock"},
        {"Summer Song", "Silent Sanctuary", "Rock"},
        {"Bumalik Ka Na Sa'kin", "Silent Sanctuary", "Rock"},
        
        
        {"Malaya", "Moira Dela Torre", "Pop Ballad"},
        {"Tagpuan", "Moira Dela Torre", "Pop Ballad"},
        {"Torete", "Moira Dela Torre", "Pop Ballad"},
        {"Ikaw at Ako", "Moira Dela Torre & Jason Marvin", "Pop Ballad"},
        {"Tagu-taguan", "Moira Dela Torre", "Pop Ballad"},
        {"Titibo-tibo", "Moira Dela Torre", "Pop Ballad"},
        {"Sundo", "Moira Dela Torre", "Pop Ballad"},
        
        
        {"Bazinga", "SB19", "P-Pop"},
        {"What?", "SB19", "P-Pop"},
        {"Alab", "SB19", "P-Pop"},
        {"Go Up", "SB19", "P-Pop"},
        {"Mapa", "SB19", "P-Pop"},
        {"SLMT", "SB19", "P-Pop"},
        {"Tilaluha", "SB19", "P-Pop"},
        {"Love Goes", "SB19", "P-Pop"},
        
        
        {"Handog", "Florante", "Folk"},
        {"Kahit Maputi Na Ang Buhok Ko", "Rey Valera", "OPM Classic"},
        {"Forevermore", "Side A", "Pop Ballad"},
        {"Rainbow", "South Border", "R&B"},
        {"Muntik Nang Maabot Ang Langit", "South Border", "R&B"},
        {"Kung Ako Na Lang Sana", "Bituin Escalante", "Pop Ballad"},
        {"Emotions", "Regine Velasquez", "Pop Ballad"},
        {"Narda", "Kamikazee", "Rock"},
        {"Nobela", "Join The Club", "Alternative"},
        {"Hawak Kamay", "Yeng Constantino", "Pop"},
        {"Ikaw", "Yeng Constantino", "Pop"},
        {"Hari ng Sablay", "Sugarfree", "Rock"},
        {"Burnout", "Sugarfree", "Rock"},
        {"Makita Kang Muli", "Sugarfree", "Rock"},
        {"Kung Ayaw Mo Na Sa Akin", "Sugarfree", "Rock"},
        {"Mariposa", "Sugarfree", "Rock"},
        
        
        {"Nakikinig", "Juan Karlos", "Alternative"},
        {"Buwan", "Juan Karlos", "Alternative"},
        {"Bestiny", "Zack Tabudlo", "Pop"},
        {"Give Me Your Forever", "Zack Tabudlo", "Pop"},
        {"Nangangamba", "Zack Tabudlo", "Pop"},
        {"Ginto", "Adie", "Pop Ballad"},
        {"Sawa Na", "Adie", "Pop Ballad"},
        {"Dungaw", "Arthur Nery", "R&B"},
        {"Pelikula", "Arthur Nery", "R&B"},
        {"Take All The Love", "Arthur Nery", "R&B"},
        
        
        {"Born To Win", "BINI", "P-Pop"},
        {"Na Na Na", "BINI", "P-Pop"},
        {"Kapit Lang", "BINI", "P-Pop"},
        {"The Light", "BGYO", "P-Pop"},
        {"He's Into Her", "BGYO", "P-Pop"},
        {"Kundiman", "BGYO", "P-Pop"},
        
        
        {"Dalaga", "I Belong to the Zoo", "Pop Rock"},
        {"Balang Araw", "I Belong to the Zoo", "Pop Rock"},
        {"Patawad, Paalam", "Moira Dela Torre & I Belong to the Zoo", "Pop"},
        {"Patawad", "Moira Dela Torre", "Pop Ballad"},
        {"Dulo", "Zild", "Alternative"},
        {"Sinungaling", "Zild", "Alternative"},
        {"Kyusi", "Zild", "Alternative"},
        {"Huminga", "Zild", "Alternative"},
        {"Duyan", "Lola Amour", "Alternative"},
        {"Raining In Manila", "Lola Amour", "Alternative"},
        {"Pwede Ba", "Lola Amour", "Alternative"},
        {"Fallen", "Lola Amour", "Alternative"},
        
        
        {"Pinoy Ako", "Orange and Lemons", "Rock"},
        {"Yakap sa Dilim", "Orange and Lemons", "Rock"},
        {"Heaven Knows", "Orange and Lemons", "Rock"},
        {"Prinsesa", "The Teeth", "Alternative Rock"},
        {"Laklak", "Teeth", "Alternative Rock"},
        {"Jeepney", "Sponge Cola", "Rock"},
        {"KLSP", "Sponge Cola", "Rock"},
        {"Bitiw", "Sponge Cola", "Rock"},
        {"Di Na Mababawi", "Sponge Cola", "Rock"},
        {"Tuliro", "Sponge Cola", "Rock"},
        {"Gemini", "Sponge Cola", "Rock"},
        {"Kay Tagal Kitang Hinintay", "Sponge Cola", "Rock"},
        {"Maselang Bahaghari", "Eraserheads", "Rock"},
        {"Maskara", "Eraserheads", "Rock"},
        {"Julie Tearjerky", "Eraserheads", "Rock"},
        {"Pop Machine", "Eraserheads", "Rock"},
        {"Tikman", "Eraserheads", "Rock"},
        {"Di Na Ako Aasa Pa", "Introvoys", "Rock"},
        {"Will You Ever Learn", "Typecast", "Rock"},
        {"Boston Drama", "Typecast", "Rock"},
        {"Ang Pag-ibig", "Johnoy Danao", "Folk"},
        {"Bakuran", "Johnoy Danao", "Folk"},
        {"Salubong", "Johnoy Danao", "Folk"},
        {"Tulad ng Dati", "The Dawn", "Rock"},
        {"Salamat", "The Dawn", "Rock"},
        {"Enveloped Ideas", "The Dawn", "Rock"},
        {"Sunshine", "The Dawn", "Rock"},
        {"Iisang Bangka", "The Dawn", "Rock"},
        {"Maglakad Ka", "Sandwich", "Rock"},
        {"Betamax", "Sandwich", "Rock"},
        {"Sugod", "Sandwich", "Rock"},
        {"Butterfly Carnival", "Sandwich", "Rock"},
        {"Two Trick Pony", "Sandwich", "Rock"},
        {"Manila", "Sandwich", "Rock"}
    };
    

    vector<Song> tempSongs = allSongsArray;
    

    random_device rd;
    mt19937 g(rd());
    

    shuffle(tempSongs.begin(), tempSongs.end(), g);
    

    for (int i = 0; i < 20 && i < tempSongs.size(); i++) {
        playlistQueue.push(tempSongs[i]);
    }
    




}

void playNext() {
    if (playlistQueue.empty()) {
        say("Playlist is empty. Adding more songs...");

        random_device rd;
        mt19937 g(rd());
        
        for (int i = 0; i < 5 && i < allSongsArray.size(); i++) {
            int idx = g() % allSongsArray.size();
            playlistQueue.push(allSongsArray[idx]);
        }
    }
    
    Song current = playlistQueue.front();
    playlistQueue.pop();

    say("Now playing: " + current.title + " by " + current.artist + " (" + current.genre + ")");
    recentlyPlayed.push(current);
    guideMessage();
}

void showHistory() {
    if (recentlyPlayed.empty()) {
        say("No songs have been played yet.");
        return;
    }

    say("Recently played songs (most recent first):");
    stack<Song> temp = recentlyPlayed;
    int count = 0;
    while (!temp.empty() && count < 10) {
        Song s = temp.top();
        temp.pop();
        cout << "- " << s.title << " by " << s.artist << " (" << s.genre << ")\n";
        count++;
    }
}

void viewUpcoming() {
    if (playlistQueue.empty()) {
        say("The playlist queue is currently empty.");
        return;
    }

    say("Upcoming songs in your playlist:");
    queue<Song> temp = playlistQueue;
    int count = 0;
    while (!temp.empty() && count < 10) {
        Song s = temp.front();
        temp.pop();
        cout << "- " << s.title << " by " << s.artist << " (" << s.genre << ")\n";
        count++;
    }
    
    int remaining = playlistQueue.size() - count;
    if (remaining > 0) {
        cout << "... and " << remaining << " more songs\n";
    }
}

void viewFavorites() {
    if (favoritesList.empty()) {
        say("You haven't added any favorites yet.");
        return;
    }
    
    say("Your favorite songs:");
    for (const Song& song : favoritesList) {
        cout << "- " << song.title << " by " << song.artist << " (" << song.genre << ")\n";
    }
}

void addToFavorites() {
    if (recentlyPlayed.empty()) {
        say("Play some songs first before adding to favorites.");
        return;
    }
    
    Song lastPlayed = recentlyPlayed.top();
    favoritesList.push_back(lastPlayed);
    say("Added to favorites: " + lastPlayed.title + " by " + lastPlayed.artist);
}

void searchSongs() {
    string term;
    cout << "Enter search term: ";
    getline(cin, term);
    
    say("Search results for '" + term + "':");
    bool found = false;
    
    for (const Song& song : allSongsArray) {
        if (song.title.find(term) != string::npos || 
            song.artist.find(term) != string::npos ||
            song.genre.find(term) != string::npos) {
            cout << "- " << song.title << " by " << song.artist << " (" << song.genre << ")\n";
            found = true;
        }
    }
    
    if (!found) {
        say("No songs found matching '" + term + "'");
    }
}

int main() {

    random_device rd;
    mt19937 rng(rd());
    
    say("Welcome to OPM Music Player 2025");
    say("Loading 200 OPM songs...");
    
    populateDataStructures();
    
    string input;
    say("Your playlist is ready with 200 OPM songs! Use the menu to control playback.");

    while (true) {
        cout << "\nChoose an action:\n";
        cout << "1. Play next song\n";
        cout << "2. View upcoming playlist\n";
        cout << "3. View recently played\n";
        cout << "4. View favorites\n";
        cout << "5. Add current song to favorites\n";
        cout << "6. Search songs\n";
        cout << "7. Exit\n";
        cout << "> ";
        getline(cin, input);

        if (input == "1") playNext();
        else if (input == "2") viewUpcoming();
        else if (input == "3") showHistory();
        else if (input == "4") viewFavorites();
        else if (input == "5") addToFavorites();
        else if (input == "6") searchSongs();
        else if (input == "7") {
            say("Exiting OPM Music Player. Salamat!");
            break;
        } else {
            say("Invalid input. Please enter a number between 1 and 7.");
        }
    }

    return 0;
}