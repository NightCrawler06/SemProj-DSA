#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <map>
#include <queue>
#include <stack>

using namespace std;

struct Movie {
    string title;
    string genre;
    float rating;
    string description;
};

vector<Movie> actionMovies = {
    {"Mad Max: Fury Road", "Action", 8.1, "In a post-apocalyptic wasteland, Max teams up with Furiosa to escape a tyrannical warlord."},
    {"The Dark Knight", "Action", 9.0, "Batman faces off against the Joker, a criminal mastermind who wants to plunge Gotham into anarchy."},
    {"John Wick", "Action", 7.4, "A retired hitman seeks revenge on the men who killed his dog, a gift from his deceased wife."},
    {"Die Hard", "Action", 8.2, "A cop tries to save hostages in a Los Angeles skyscraper from a group of terrorists."},
    {"Gladiator", "Action", 8.5, "A betrayed Roman general seeks revenge against the emperor who murdered his family."},
    {"The Avengers", "Action", 8.0, "Earth's mightiest heroes join forces to battle an alien invasion led by Loki."},
    {"The Matrix", "Action", 8.7, "A hacker learns that the world he lives in is a simulation controlled by intelligent machines."},
    {"Mission: Impossible - Fallout", "Action", 7.7, "Ethan Hunt and his IMF team must track down a group of operatives who have stolen nuclear weapons."},
    {"Spider-Man: No Way Home", "Action", 8.3, "Spider-Man faces a multiverse of threats after tampering with a spell that goes wrong."},
    {"Iron Man", "Action", 7.9, "A billionaire inventor creates an advanced suit of armor to fight against the forces of evil."},
    {"Black Panther", "Action", 7.3, "The prince of Wakanda becomes the Black Panther to fight for the future of his nation."},
    {"The Bourne Identity", "Action", 7.9, "A man with amnesia is pursued by assassins while trying to uncover his true identity."},
    {"Guardians of the Galaxy", "Action", 8.0, "A ragtag group of space criminals must work together to stop a powerful villain from destroying the galaxy."},
    {"The Punisher", "Action", 6.4, "A man seeks revenge against the criminals who killed his family and left him for dead."},
    {"Casino Royale", "Action", 8.0, "James Bond embarks on his first mission as a 00-agent to defeat a terrorist financier in a high-stakes poker game."},
    {"Aquaman", "Action", 6.9, "The half-human, half-Atlantean Arthur Curry must stop his half-brother from claiming the throne of Atlantis."},
    {"Thor: Ragnarok", "Action", 7.9, "Thor must prevent the destruction of Asgard by facing off against Hela, the Goddess of Death."},
    {"Captain America: The Winter Soldier", "Action", 7.8, "Captain America teams up with Black Widow to uncover a conspiracy within S.H.I.E.L.D."}
};

vector<Movie> dramaMovies = {
    {"The Shawshank Redemption", "Drama", 9.3, "Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency."},
    {"Forrest Gump", "Drama", 8.8, "The presidencies of Kennedy and Johnson, the Vietnam War, the civil rights movement, and other historical events unfold from the perspective of an Alabama man with an extraordinary life."},
    {"The Godfather", "Drama", 9.2, "The aging patriarch of an organized crime dynasty transfers control of his clandestine empire to his reluctant son."},
    {"A Beautiful Mind", "Drama", 8.2, "The story of John Nash, a brilliant but asocial mathematician, and his struggle with schizophrenia."},
    {"The Green Mile", "Drama", 8.6, "A man with extraordinary powers is sentenced to death for the murder of two girls, and a prison guard becomes his friend."},
    {"Gladiator", "Drama", 8.5, "A betrayed Roman general seeks revenge against the emperor who murdered his family."},
    {"The Pursuit of Happyness", "Drama", 8.0, "A struggling salesman takes custody of his son as he battles to stay afloat and fulfill his dreams."},
    {"12 Angry Men", "Drama", 8.9, "A jury of 12 men must deliberate the guilt or innocence of a defendant on the basis of reasonable doubt."},
    {"Schindler's List", "Drama", 9.0, "In Nazi-occupied Poland, Oskar Schindler gradually becomes concerned for his Jewish workforce after witnessing their persecution by the Nazis."},
    {"The Pianist", "Drama", 8.5, "A Jewish pianist struggles to survive the destruction of the Warsaw ghetto during World War II."},
    {"Good Will Hunting", "Drama", 8.3, "A young janitor at MIT has a gift for mathematics but needs help from a psychologist to find direction in his life."},
    {"The Social Network", "Drama", 8.0, "The story of the founding of Facebook and the lawsuits that followed its creation."},
    {"The Revenant", "Drama", 8.0, "In the 1820s, a frontiersman is left for dead after being attacked by a bear and must survive to get revenge on those who abandoned him."},
    {"Spotlight", "Drama", 8.1, "The Boston Globe uncovers a massive scandal of child abuse within the Catholic Church."},
    {"La La Land", "Drama", 8.0, "A jazz musician and an aspiring actress fall in love but struggle to balance their dreams and relationship."}
};

vector<Movie> comedyMovies = {
    {"The Hangover", "Comedy", 7.7, "Three friends wake up after a bachelor party in Las Vegas and must piece together what happened the night before."},
    {"Superbad", "Comedy", 7.6, "Two high school friends try to buy alcohol for a party, but things quickly spiral out of control."},
    {"Step Brothers", "Comedy", 6.9, "Two middle-aged men become stepbrothers when their parents marry, leading to a rivalry."},
    {"Anchorman: The Legend of Ron Burgundy", "Comedy", 7.2, "The adventures of Ron Burgundy, a popular news anchor in 1970s San Diego."},
    {"21 Jump Street", "Comedy", 7.2, "Two undercover cops infiltrate a high school to bust a drug ring."},
    {"Dumb and Dumber", "Comedy", 7.3, "Two well-meaning but dim-witted friends embark on a cross-country trip to return a briefcase to its owner."},
    {"Tropic Thunder", "Comedy",  7.0, "A group of actors filming a war movie end up in a real conflict in Southeast Asia."},
    {"The Grand Budapest Hotel", "Comedy",  8.1, "A young concierge becomes involved in a robbery and murder plot at a famous European hotel."},
    {"Borat", "Comedy",  7.3, "A journalist from Kazakhstan travels to America to make a documentary about the people and culture."},
    {"Ferris Bueller's Day Off", "Comedy",  7.8, "A high school student skips school for a day of fun in Chicago, while trying to avoid getting caught."},
    {"Shaun of the Dead", "Comedy",  7.9, "A group of friends try to survive a zombie apocalypse in their local pub."},
    {"Ghostbusters", "Comedy",  7.8, "Three scientists in New York City start a ghost-catching business after they discover ghosts are real."}
};

vector<Movie> horrorMovies = {
    {"The Conjuring", "Horror" , 7.5, "Paranormal investigators work to help a family terrorized by dark spirits."},
    {"A Nightmare on Elm Street", "Horror", 7.5, "A group of teenagers is stalked and killed by Freddy Krueger, a burned man who appears in their dreams."},
    {"The Shining", "Horror", 8.4, "A man becomes increasingly unhinged while serving as the winter caretaker of a remote hotel."},
    {"It", "Horror", 7.3, "A group of children face their fears when a shape-shifting clown starts terrorizing their town."},
    {"Get Out", "Horror", 7.7, "A young African-American man uncovers disturbing secrets when he visits his girlfriend's family."},
    {"The Exorcist", "Horror", 8.0, "A young girl is possessed by a demonic entity, and a priest must perform an exorcism to save her."},
    {"Hereditary", "Horror", 7.3, "A family is haunted by dark secrets and a tragic loss that threatens their survival."},
    {"Psycho", "Horror", 8.5, "A woman steals money and ends up at a secluded motel, where she meets a mysterious man."},
    {"The Ring", "Horror", 7.1, "A journalist investigates a videotape that causes anyone who watches it to die seven days later."},
    {"Paranormal Activity", "Horror", 6.3, "A couple sets up a camera to record strange occurrences in their house, which soon turn deadly."},
    {"Texas Chainsaw Massacre", "Horror", 7.5, "A group of friends encounters a family of cannibals, including the terrifying Leatherface."},
    {"The Babadook", "Horror", 6.8, "A mother and her son are haunted by a sinister entity from a children's book."},
    {"Saw", "Horror", 7.6, "Two men wake up in a grimy bathroom, trapped by a twisted serial killer who forces them into a life-or-death game."},
    {"The Witch", "Horror", 6.9, "A family in 1630s New England faces paranoia and horror after being exiled from their Puritan settlement."}
};

vector<Movie> sciFiMovies = {
    {"Interstellar", "Sci-Fi", 8.6, "A team of astronauts travels through a wormhole to find a new home for humanity as Earth faces extinction."},
    {"Inception", "Sci-Fi", 8.8, "A skilled thief is given a chance to have his criminal record erased if he can perform inception on a target."},
    {"The Matrix", "Sci-Fi", 8.7, "A hacker learns that the world he lives in is a simulation controlled by intelligent machines."},
    {"Blade Runner 2049", "Sci-Fi", 8.0, "A blade runner uncovers a secret that could reshape the future of humanity."},
    {"The Terminator", "Sci-Fi", 8.0, "A cyborg assassin is sent back in time to kill the mother of the leader of a resistance movement."},
    {"Star Wars: Episode IV - A New Hope", "Sci-Fi", 8.6, "A young farmer joins a rebel alliance to defeat the Empire and restore peace to the galaxy."},
    {"Back to the Future", "Sci-Fi", 8.5, "A teenager travels back in time and risks changing the course of history."},
    {"Minority Report", "Sci-Fi", 7.6, "A cop in a future society is accused of a crime he hasn't committed yet, thanks to a system that can predict crimes before they happen."},
    {"E.T. the Extra-Terrestrial", "Sci-Fi", 7.8, "A young boy befriends an alien stranded on Earth and tries to help him return home."},
    {"The Martian", "Sci-Fi", 8.0, "An astronaut must survive alone on Mars after being mistakenly left behind by his crew."},
    {"Avatar", "Sci-Fi", 7.8, "A paraplegic marine is sent to a distant planet and becomes involved in a battle between humans and the indigenous species."},
    {"2001: A Space Odyssey", "Sci-Fi", 8.3, "A journey through space to uncover the secrets behind a mysterious monolith."},
    {"A Clockwork Orange", "Sci-Fi", 8.3, "In a dystopian future, a young delinquent undergoes behavioral modification in an attempt to be cured of his violent tendencies."}
};

vector<Movie> kidsMovies = {
    {"Finding Nemo", "Kids", 8.1, "A clownfish sets out on a journey to find his missing son."},
    {"Toy Story", "Kids", 8.3, "Toys come to life and go on adventures when humans aren't around."},
    {"The Lion King", "Kids", 8.5, "A lion cub must embrace his destiny as king of the savannah."},
    {"Zootopia", "Kids", 8.0, "A bunny cop and a fox con artist uncover a conspiracy in the city of Zootopia."},
    {"Frozen", "Kids", 7.4, "Two royal sisters learn about love, family, and self-discovery through magical ice powers."},
    {"Moana", "Kids", 7.6, "A young girl sails across the ocean to save her island with the help of a demigod."},
    {"Shrek", "Kids", 7.9, "An ogre goes on a quest to rescue a princess and ends up finding love and friendship."},
    {"Coco", "Kids", 8.4, "A boy journeys to the Land of the Dead to unlock his family's history through music."},
    {"Inside Out", "Kids", 8.1, "A young girl's emotions come to life as she navigates a difficult move to a new city."},
    {"Despicable Me", "Kids", 7.6, "A supervillain adopts three girls as part of a plan but ends up loving them."},
    {"Ratatouille", "Kids", 8.1, "A rat with culinary talent tries to become a chef in a Paris restaurant."},
    {"Up", "Kids", 8.2, "A grumpy old man and a young boy scout go on a flying house adventure."},
    {"The Incredibles", "Kids", 8.0, "A family of superheroes must come out of hiding to save the world."},
    {"Luca", "Kids", 7.4, "Two sea monster boys explore the human world above the ocean in a small Italian town."},
    {"Turning Red", "Kids", 7.0, "A 13-year-old girl starts transforming into a red panda whenever she gets too excited."}
};


vector<Movie> likedMovies;
vector<Movie> watchHistory;
vector<Movie> watchLater;
vector<Movie> currentlyWatching;
vector<Movie> customMovies;
vector<pair<Movie, float>> userRatedMovies;
queue<Movie> playbackQueue;
stack<Movie> likedUndoStack;


map<string, vector<Movie>> userCollections;

vector<Movie>* getGenreListByName(const string& genre) {
    if (genre == "action") return &actionMovies;
    if (genre == "drama") return &dramaMovies;
    if (genre == "comedy") return &comedyMovies;
    if (genre == "horror") return &horrorMovies;
    if (genre == "kids") return &kidsMovies;

    if (genre == "sci-fi" || genre == "scifi") return &sciFiMovies;
    return nullptr;
}

void chatbotSay(const string& message) {
    cout << "[MoviBot] " << message << endl;
}


void trim(string& s) {
    s.erase(0, s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t") + 1);
}


string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}




bool isInList(const vector<Movie>& list, const Movie& movie) {
    return any_of(list.begin(), list.end(), [&](const Movie& m) {
        return m.title == movie.title;
    });
}



void saveData() {
    ofstream liked("liked.txt"), history("history.txt"), later("later.txt");
    for (const auto& m : likedMovies) liked << m.title << '\n';
    for (const auto& m : watchHistory) history << m.title << '\n';
    for (const auto& m : watchLater) later << m.title << '\n';
}


void displayMovie(const Movie& m) {
    cout << "Title: " << m.title << "\nGenre: " << m.genre
         << "\nRating: " << m.rating << "\nDescription: " << m.description << "\n";
}

void showMovieList(const vector<Movie>& list, const string& header) {
    cout << "\nHere are your " << header << ":\n";
    if (list.empty()) {
        cout << "This list is currently empty.\n";
        return;
    }
    for (const Movie& m : list) {
        displayMovie(m);
        cout << "--------------------------\n";
    }
}




void recommendMovie(const string& genreName) {
    vector<Movie>* genreList = getGenreListByName(genreName);
    if (!genreList) {
        cout << "I couldn't recognize that genre. Try: action, drama, comedy, horror, or sci-fi.\n";
        return;
    }

    chatbotSay("Awesome choice! Let's find some " + genreName + " movies you might enjoy...");


    int index = 0;
    while (true) {
        int shown = 0;
        for (; index < genreList->size() && shown < 3; ++index) {
            const Movie& m = (*genreList)[index];
            if (isInList(watchHistory, m) || isInList(likedMovies, m)) continue;

            chatbotSay("How about this one?");
            displayMovie(m);

            chatbotSay("Seen this one already? Just say yes or no.");

            string seen;
            getline(cin, seen);


            if (seen.find('y') != string::npos) {
                if (!isInList(watchHistory, m)) watchHistory.push_back(m);
                cout << "Added to your watch history.\n";
                saveData();
                cout << "Did you enjoy it? (y/n): ";
                string likedInput;
                getline(cin, likedInput);
                if (!likedInput.empty() && tolower(likedInput[0]) == 'y') {

                    likedMovies.push_back(m);
                    cout << "Added to your liked movies.\n";
                    likedMovies.push_back(m);
                    likedUndoStack.push(m);

                    saveData();
                }
                cout << "Would you like to rate this movie yourself? (y/n): ";
                string rateInput;
                getline(cin, rateInput);
                if (!rateInput.empty() && tolower(rateInput[0]) == 'y') {

                    cout << "Enter your rating (1-10): ";
                    float userRating;
                    cin >> userRating;
                    cin.ignore();
                    cout << "Thanks! You rated this " << userRating << "/10\n";

                    userRatedMovies.push_back({m, userRating});
                }

            } else {
                chatbotSay("Want me to add this to your Watch Later list? (y/n): ");
                string laterInput;
                getline(cin, laterInput);
                if (!laterInput.empty() && tolower(laterInput[0]) == 'y') {
                    watchLater.push_back(m);
                    cout << "Added to your watch later list.\n";
                    saveData();
                }
            }

            shown++;
        }

        if (shown == 0) {
            cout << "\nLooks like you've seen or saved all the movies in this genre.\n";
            break;
        }

        cout << "\nWould you like to see 3 more suggestions? (y/n): ";
        string again;
        getline(cin, again);
        transform(again.begin(), again.end(), again.begin(), ::tolower);
        if (again != "y") break;

    }
}



void removeMovieFromList(vector<Movie>& list, const string& title, const string& listName) {
    string loweredTitle = toLower(title);
    auto it = remove_if(list.begin(), list.end(), [&](const Movie& m) {
        return toLower(m.title) == loweredTitle;
    });

    if (it != list.end()) {
        list.erase(it, list.end());
        chatbotSay("Got it! I removed \"" + title + "\" from your " + listName + " list.");
        saveData(); 
    } else {
        chatbotSay("Sorry, I can't find \"" + title + "\" in your " + listName + " list.");
    }
}

void startWatching(const string& title) {
    vector<Movie>* allGenres[] = {&actionMovies, &dramaMovies, &comedyMovies, &horrorMovies, &sciFiMovies, &kidsMovies};
    for (auto* genre : allGenres) {
        for (const Movie& m : *genre) {
            if (toLower(m.title) == toLower(title)) {
                currentlyWatching.push_back(m);
                chatbotSay("You're now watching \"" + m.title + "\".");
                return;
            }
        }
    }
    chatbotSay("Couldn't find that title to start watching.");
}

void finishWatching(const string& title) {
    auto it = find_if(currentlyWatching.begin(), currentlyWatching.end(), [&](const Movie& m) {
        return toLower(m.title) == toLower(title);
    });

    if (it != currentlyWatching.end()) {
        watchHistory.push_back(*it);
        currentlyWatching.erase(it);
        chatbotSay("Marked \"" + title + "\" as finished and moved to history.");
        saveData();


        if (!playbackQueue.empty()) {
            chatbotSay("Do you want to start the next movie in your queue? (y/n)");
            string response;
            getline(cin, response);
            if (!response.empty() && tolower(response[0]) == 'y') {
                Movie next = playbackQueue.front();
                playbackQueue.pop();
                currentlyWatching.push_back(next);
                chatbotSay("Now watching from your queue:");
                displayMovie(next);
            } else {
                chatbotSay("Okay, taking a break from watching.");
            }
        } else {
            chatbotSay("Your queue is empty.");
        }

    } else {
        chatbotSay("You're not currently watching \"" + title + "\".");
    }
}




void addToCollection(const string& title, const string& collection) {
    vector<Movie>* allSources[] = {&actionMovies, &dramaMovies, &comedyMovies, &horrorMovies, &sciFiMovies, &kidsMovies, &customMovies};


    for (auto* source : allSources) {
        for (const Movie& m : *source) {
            if (toLower(m.title) == toLower(title)) {
                userCollections[collection].push_back(m);
                chatbotSay("Added \"" + m.title + "\" to your \"" + collection + "\" collection.");
                return;
            }
        }
    }

    chatbotSay("Sorry, I couldn't find that movie.");
}


void showCollection(const string& name) {
    if (userCollections.find(name) == userCollections.end()) {
        chatbotSay("No collection named \"" + name + "\" found.");
        return;
    }
    showMovieList(userCollections[name], name + " Collection");
}


void showBestMovie() {
    Movie best = {"", "", 0.0, ""};
    for (const Movie& m : likedMovies)
        if (m.rating > best.rating) best = m;
    for (const Movie& m : watchHistory)
        if (m.rating > best.rating) best = m;

    if (best.title.empty()) {
        cout << "You haven't watched or liked any movies yet.\n";
        return;
    }

    chatbotSay("Here's the best-rated movie you've liked or watched!");
    displayMovie(best);
}

void loadData() {
    auto load = [](const string& filename, vector<Movie>& list) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            for (auto& group : {actionMovies, dramaMovies, comedyMovies, horrorMovies, sciFiMovies}) {
                for (auto& m : group) {
                    if (m.title == line) list.push_back(m);
                }
            }
        }
    };
    load("liked.txt", likedMovies);
    load("history.txt", watchHistory);
    load("later.txt", watchLater);
}

void suggestSimilarMovie(const string& title) {
    for (const Movie& liked : likedMovies) {
        if (toLower(liked.title) == toLower(title)) {
            vector<Movie>* genreList = getGenreListByName(toLower(liked.genre));
            chatbotSay("Here are similar movies in the same genre:");
            for (const Movie& m : *genreList) {
                if (m.title != liked.title && abs(m.rating - liked.rating) <= 0.5)
                    displayMovie(m);
            }
            return;
        }
    }
    chatbotSay("You haven't liked that movie yet.");
}


void showTopRatedMovies() {
    vector<Movie> allMovies;
    allMovies.insert(allMovies.end(), actionMovies.begin(), actionMovies.end());
    allMovies.insert(allMovies.end(), dramaMovies.begin(), dramaMovies.end());
    allMovies.insert(allMovies.end(), comedyMovies.begin(), comedyMovies.end());
    allMovies.insert(allMovies.end(), horrorMovies.begin(), horrorMovies.end());
    allMovies.insert(allMovies.end(), sciFiMovies.begin(), sciFiMovies.end());
    allMovies.insert(allMovies.end(), kidsMovies.begin(), kidsMovies.end());

    sort(allMovies.begin(), allMovies.end(), [](const Movie& a, const Movie& b) {
        return a.rating > b.rating;
    });

    cout << "\nTop 5 Rated Movies:\n";
    for (int i = 0; i < min(5, (int)allMovies.size()); ++i) {
        displayMovie(allMovies[i]);
        cout << "--------------------------\n";
    }
}

void showLowestRatedMovies() {
    vector<Movie> allMovies;
    allMovies.insert(allMovies.end(), actionMovies.begin(), actionMovies.end());
    allMovies.insert(allMovies.end(), dramaMovies.begin(), dramaMovies.end());
    allMovies.insert(allMovies.end(), comedyMovies.begin(), comedyMovies.end());
    allMovies.insert(allMovies.end(), horrorMovies.begin(), horrorMovies.end());
    allMovies.insert(allMovies.end(), sciFiMovies.begin(), sciFiMovies.end());
    allMovies.insert(allMovies.end(), kidsMovies.begin(), kidsMovies.end());

    sort(allMovies.begin(), allMovies.end(), [](const Movie& a, const Movie& b) {
        return a.rating < b.rating;
    });

    cout << "\nLowest 5 Rated Movies:\n";
    for (int i = 0; i < min(5, (int)allMovies.size()); ++i) {
        displayMovie(allMovies[i]);
        cout << "--------------------------\n";
    }
}

void deleteCollection(const string& name) {
    if (userCollections.erase(name)) {
        chatbotSay("Collection \"" + name + "\" has been deleted.");
    } else {
        chatbotSay("No collection named \"" + name + "\" was found.");
    }
}

void removeFromCollection(const string& title, const string& collection) {
    auto it = userCollections.find(collection);
    if (it == userCollections.end()) {
        chatbotSay("Collection \"" + collection + "\" not found.");
        return;
    }

    auto& movies = it->second;
    string loweredTitle = toLower(title);
    auto movieIt = remove_if(movies.begin(), movies.end(), [&](const Movie& m) {
        return toLower(m.title) == loweredTitle;
    });

    if (movieIt != movies.end()) {
        movies.erase(movieIt, movies.end());
        chatbotSay("Removed \"" + title + "\" from the \"" + collection + "\" collection.");
    } else {
        chatbotSay("Movie not found in that collection.");
    }
}

void showUserBestRatings() {
    if (userRatedMovies.empty()) {
        chatbotSay("You haven't rated any movies yet.");
        return;
    }
    sort(userRatedMovies.begin(), userRatedMovies.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });
    chatbotSay("Your Top 3 Rated Movies:");
    for (int i = 0; i < min(3, (int)userRatedMovies.size()); ++i) {
        cout << "- " << userRatedMovies[i].first.title << " (" << userRatedMovies[i].second << "/10)\n";
    }
}

void showUserWorstRatings() {
    if (userRatedMovies.empty()) {
        chatbotSay("You haven't rated any movies yet.");
        return;
    }
    sort(userRatedMovies.begin(), userRatedMovies.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
    chatbotSay("Your Lowest 3 Rated Movies:");
    for (int i = 0; i < min(3, (int)userRatedMovies.size()); ++i) {
        cout << "- " << userRatedMovies[i].first.title << " (" << userRatedMovies[i].second << "/10)\n";
    }
}

void addToPlaybackQueue(const string& title) {
    vector<Movie>* allGenres[] = {&actionMovies, &dramaMovies, &comedyMovies, &horrorMovies, &sciFiMovies, &kidsMovies, &customMovies};
    for (auto* genre : allGenres) {
        for (const Movie& m : *genre) {
            if (toLower(m.title) == toLower(title)) {
                playbackQueue.push(m);
                chatbotSay("Added \"" + m.title + "\" to your playback queue.");
                return;
            }
        }
    }
    chatbotSay("Sorry, couldn't find that movie.");
}

void showPlaybackQueue() {
    if (playbackQueue.empty()) {
        chatbotSay("Your playback queue is empty.");
        return;
    }

    chatbotSay("Here are the movies in your playback queue:");
    std::queue<Movie> temp = playbackQueue;
    while (!temp.empty()) {
        displayMovie(temp.front());
        cout << "--------------------------\n";
        temp.pop();
    }
}


void undoLastLike() {
    if (likedUndoStack.empty()) {
        chatbotSay("Nothing to undo.");
        return;
    }

    Movie last = likedUndoStack.top();
    likedUndoStack.pop();


    auto it = remove_if(likedMovies.begin(), likedMovies.end(), [&](const Movie& m) {
        return toLower(m.title) == toLower(last.title);
    });

    if (it != likedMovies.end()) {
        likedMovies.erase(it, likedMovies.end());
        chatbotSay("Undo successful: \"" + last.title + "\" was removed from liked movies.");
        saveData();
    } else {
        chatbotSay("Movie was not found in liked movies.");
    }
}




int main() {
    chatbotSay("Hey there! I'm Movibot, your movie buddy.");
    chatbotSay("I can help you find what to watch, save your favorites, and even track what you've seen.");
    chatbotSay("Ready to discover something fun?");

    loadData();

    string input;
    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "Type 'help' to see available commands.\n";
        chatbotSay("Your input: ");
        cin.clear();
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);


        vector<string> genres = {"action", "drama", "comedy", "horror", "sci-fi", "scifi", "kids"};



        bool matched = false;
        for (const string& g : genres) {
            if (input.find(g) != string::npos) {
                recommendMovie(g);
                matched = true;
                break;
            }
        }
        if (matched) continue; 


        if (input.find("suggest similar") != string::npos) {
            string title = input.substr(input.find("to") + 2);
            trim(title);
            suggestSimilarMovie(title);
        } else if (input.find("start watching") != string::npos) {
            string title = input.substr(input.find("start watching") + 14);
            trim(title);
            startWatching(title);
        } else if (input.find("mark finished") != string::npos) {
            string title = input.substr(input.find("mark finished") + 13);
            trim(title);
            finishWatching(title);
        } else if (input.find("show currently watching") != string::npos) {
            showMovieList(currentlyWatching, "Currently Watching");
        } else if (input.find("custom movie") != string::npos) {
            Movie m;
            cout << "Enter title: ";
            getline(cin, m.title);
            cout << "Enter genre: ";
            getline(cin, m.genre);
            cout << "Enter rating (e.g., 7.5): ";
            cin >> m.rating;
            cin.ignore();
            cout << "Enter description: ";
            getline(cin, m.description);

            customMovies.push_back(m);
            chatbotSay("Got it! Your custom movie was added.");

            cout << "Would you like to add it to a collection? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'y') {
                cout << "Enter collection name: ";
                string collection;
                getline(cin, collection);
                userCollections[collection].push_back(m);
                chatbotSay("Added to your \"" + collection + "\" collection.");
            }
        } else if (input.find("liked") != string::npos && input.find("show") != string::npos) {
            showMovieList(likedMovies, "Liked Movies");
        } else if ((input.find("history") != string::npos && input.find("show") != string::npos) || input.find("what have I watched") != string::npos) {
            showMovieList(watchHistory, "Watch History");
        } else if ((input.find("watch later") != string::npos && input.find("show") != string::npos) || input.find("saved for later") != string::npos) {
            showMovieList(watchLater, "Watch Later");
        } else if (input.find("best movie") != string::npos || input.find("show best") != string::npos) {
            showBestMovie();
        } else if (input.find("remove") != string::npos && input.find("from collection") != string::npos) {
            size_t removePos = input.find("remove") + 6;
            size_t fromPos = input.find("from collection");
            string title = input.substr(removePos, fromPos - removePos);
            string collection = input.substr(fromPos + 15);
            trim(title);
            trim(collection);
            removeFromCollection(title, collection);
        } else if (input.find("remove") != string::npos && input.find("from") != string::npos) {
            size_t removePos = input.find("remove") + 6;
            size_t fromPos = input.find("from");

            if (fromPos == string::npos || fromPos <= removePos) {
                cout << "Invalid remove format. Use: remove [title] from [liked/history/later]\n";
            } else {
                string rawTitle = input.substr(removePos, fromPos - removePos);
                string listName = input.substr(fromPos + 5); 


                auto trim = [](string& s) {
                    s.erase(0, s.find_first_not_of(" \t"));
                    s.erase(s.find_last_not_of(" \t") + 1);
                };
                trim(rawTitle);
                trim(listName);

                if (listName == "liked") removeMovieFromList(likedMovies, rawTitle, "liked");
                else if (listName == "history") removeMovieFromList(watchHistory, rawTitle, "history");
                else if (listName == "later") removeMovieFromList(watchLater, rawTitle, "later");

                else cout << "List name should be liked, history, or later.\n";
            }
        } else if (input.find("add to queue") != string::npos) {
            string title = input.substr(input.find("add to queue") + 12);
            trim(title);            addToPlaybackQueue(title);
        } else if (input.find("show queue") != string::npos) {
            showPlaybackQueue();
        } else if (input.find("add") != string::npos && input.find("to") != string::npos) {
            size_t addPos = input.find("add") + 3;
            size_t toPos = input.find("to");
            string rawTitle = input.substr(addPos, toPos - addPos);
            string collection = input.substr(toPos + 2);
            trim(rawTitle);
            trim(collection);
            addToCollection(rawTitle, collection);
        } 
        else if (input.find("show") != string::npos && input.find("collection") != string::npos) {
            string name = input;
            name.erase(0, input.find("show") + 4);
            name.erase(name.find("collection"), string::npos);
            trim(name);
            showCollection(name);
        } else if (input.find("delete collection") != string::npos) {
            string name = input.substr(input.find("delete collection") + 17);
            trim(name);
            deleteCollection(name);
        } else if (input.find("most rated") != string::npos || input.find("top rated") != string::npos) {
            showTopRatedMovies();
        } else if (input.find("low rated") != string::npos || input.find("worst rated") != string::npos) {
            showLowestRatedMovies();
        }else if (input.find("my top ratings") != string::npos || input.find("my best ratings") != string::npos) {
            showUserBestRatings();
        } else if (input.find("my worst ratings") != string::npos || input.find("my low ratings") != string::npos) {
            showUserWorstRatings();
        } else if (input == "undo like" || input == "undo liked") {
            undoLastLike();
        } else if (!matched && (
            input.find("recommend") != string::npos ||
            input.find("suggest") != string::npos ||
            input.find("watch") != string::npos ||
            input.find("movie") != string::npos ||
            input.find("i want") != string::npos ||
            input.find("mood") != string::npos
        )) {
            chatbotSay("Got it! But please mention the genre too — like 'comedy' or 'drama'.");
        } else if (input == "exit" || input == "quit") {
            saveData();
            cout << "Thanks for using the chatbot! Your data has been saved.\n";
            break;
        } else if (input == "help") {
            chatbotSay("Need a hand? Here's what I can help you with:");
            cout << "       Keywords                                  What can it do \n";
            cout << "- recommend [genre]                         : Get up to 3 movie suggestions (e.g., recommend action)\n";
            cout << "- show liked                                : View your liked movies\n";
            cout << "- show history                              : See what you've watched\n";
            cout << "- show watch later                          : View your Watch Later list\n";
            cout << "- remove [title] from [liked/history/later] : Remove a movie from a list\n";
            cout << "- add [movie title] to [collection name]    : Add a movie to a named collection\n";
            cout << "- show [collection name] collection         : View all movies in a collection\n";
            cout << "- delete collection [name]                  : Delete an entire collection\n";
            cout << "- remove [title] from collection [name]     : Remove a movie from a collection\n";    
            cout << "- suggest similar to [title]                : Find similar movies to ones you liked\n";
            cout << "- start watching [title]                    : Mark a movie as currently watching\n";
            cout << "- mark finished [title]                     : Mark a movie as finished and move to history\n";
            cout << "- show currently watching                   : View all movies you're currently watching\n";
            cout << "- best movie                                : Show the highest-rated movie you've liked or watched\n";
            cout << "- worst rated / low rated                   : Show the lowest-rated movies from the system\n";
            cout << "- my top ratings                            : Show your top 3 rated movies\n";
            cout << "- my worst ratings                          : Show your lowest 3 rated movies\n";
            cout << "- custom movie                              : Create and save your own movie\n";
            cout << "- undo like                                 : Undo the last movie you liked\n";
            cout << "- add to queue [title]                      : Add a movie to your playback queue\n";
            cout << "- show queue                                : View the movies in your playback queue\n";
            cout << "- exit                                      : Save your progress and leave the chatbot\n";
        } else {
            chatbotSay("Oops! I didn't quite catch that.");
            chatbotSay("Try something like: 'recommend action', or type 'help' if you're lost.");
        }

    skip:;
    }

    return 0;
}
