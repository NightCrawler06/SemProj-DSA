#include <iostream>
#include <vector>
#include <algorithm>
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


vector<Movie> likedMovies;
vector<Movie> watchHistory;
vector<Movie> watchLater;

vector<Movie>* getGenreList(int choice) {
    switch (choice) {
        case 1: return &actionMovies;
        case 2: return &dramaMovies;
        case 3: return &comedyMovies;
        case 4: return &horrorMovies;
        case 5: return &sciFiMovies;
        default: return nullptr;
    }
}

void displayMovie(const Movie& m) {
    cout << "Title: " << m.title << "\nGenre: " << m.genre
         << "\nRating: " << m.rating << "\nDescription: " << m.description << "\n";
}

void showMovieList(const vector<Movie>& list, string header) {
    if (list.empty()) {
        cout << "No movies in " << header << ".\n";
        return;
    }
    cout << "\n--- " << header << " ---\n";
    for (const Movie& m : list) {
        displayMovie(m);
        cout << "-------------------\n";
    }
}

void recommendMovie() {
    cout << "Choose a genre:\n";
    cout << "1. Action\n2. Drama\n3. Comedy\n4. Horror\n5. Sci-Fi\nChoice: ";
    int choice;
    cin >> choice;

    vector<Movie>* genreList = getGenreList(choice);
    if (!genreList || genreList->empty()) {
        cout << "Invalid genre.\n";
        return;
    }

    for (Movie& m : *genreList) {
        cout << "\nRecommended Movie:\n";
        displayMovie(m);

        cout << "Have you watched this? (y/n): ";
        char seen;
        cin >> seen;

        if (seen == 'y' || seen == 'Y') {
            watchHistory.push_back(m);
            cout << "Added to Watch History.\n";

            cout << "Did you like it? (y/n): ";
            char liked;
            cin >> liked;
            if (liked == 'y' || liked == 'Y') {
                likedMovies.push_back(m);
                cout << "Added to Liked Movies.\n";
            }
            break;
        } else {
            cout << "Add to Watch Later? (y/n): ";
            char later;
            cin >> later;
            if (later == 'y' || later == 'Y') {
                watchLater.push_back(m);
                cout << "Added to Watch Later list.\n";
            }
            break;
        }
    }
}

void showBestMovie() {
    if (likedMovies.empty() && watchHistory.empty()) {
        cout << "You haven't liked or watched any movies yet.\n";
        return;
    }

    Movie best = {"", "", 0.0, ""};

    for (const Movie& m : likedMovies)
        if (m.rating > best.rating)
            best = m;

    for (const Movie& m : watchHistory)
        if (m.rating > best.rating)
            best = m;

    cout << "\nBest Movie You've Seen:\n";
    displayMovie(best);
}

int main() {
    while (true) {
        cout << "\n=== Movie Recommender Menu ===\n";
        cout << "1. Recommend Movie\n";
        cout << "2. View Liked Movies\n";
        cout << "3. View Watch History\n";
        cout << "4. View Watch Later List\n";
        cout << "5. Show Best Movie\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int menuChoice;
        cin >> menuChoice;

        switch (menuChoice) {
            case 1: recommendMovie(); break;
            case 2: showMovieList(likedMovies, "Liked Movies"); break;
            case 3: showMovieList(watchHistory, "Watch History"); break;
            case 4: showMovieList(watchLater, "Watch Later List"); break;
            case 5: showBestMovie(); break;
            case 6: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }

    return 0;
}
