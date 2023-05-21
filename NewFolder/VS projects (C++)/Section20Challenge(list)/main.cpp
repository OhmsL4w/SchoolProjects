// Section 20
// Challenge 2
//  Lists

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
            : name{name}, artist{artist}, rating{rating} {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }
    
    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    
    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
       << std::setw(30) << std::left << s.artist
       << std::setw(2) << std::left << s.rating;
       return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
    std::cout << "Playing: " << std::endl;
    std::cout << song << std::endl << std::endl;
}

void display_playlist(const std::list<Song> &playlist, const Song &current_song) {
    // This function should display the current playlist 
    // and then the current song playing.
    for (auto const& s : playlist) {
        std::cout << s << std::endl; 
    }
    std::cout << std::endl;
    play_current_song(current_song);
}

int main() {

    std::list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}          
    };
    
    std::list<Song>::iterator current_song = playlist.begin();
    //play_current_song(*current_song);
    //display_playlist(playlist,*current_song);
    bool Qispressed{ false };

    do {
        display_menu();
        char userSelection{};
        std::cin >> userSelection;
        if (userSelection == 'f' || userSelection == 'F') {
            current_song = playlist.begin();
            play_current_song(*current_song);
            continue;
        }
        else if(userSelection == 'n' || userSelection =='N') {
            current_song++;
            if (current_song == playlist.end() ) 
                current_song = playlist.begin();
            std::cout << "playing next song" << std::endl;
            play_current_song(*current_song);
            continue;
        }
        else if (userSelection == 'p' || userSelection == 'P') {
            if (current_song == playlist.begin()) 
                current_song = playlist.end();
            current_song--;
            std::cout << "playing previous song" << std::endl;
            play_current_song(*current_song);
            continue;
        }
        else if(userSelection == 'a'||userSelection =='A'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string name{}, artist{};
            int rating{};
            std::cout << "Enter the songs name : ";
            std::getline(std::cin, name);
            std::cout << "Enter the songs artist : ";
            std::getline(std::cin, artist);
            std::cout << "Enter the songs rating : ";
            std::cin >> rating;
            std::cout << std::endl;
            Song songToAdd(name, artist, rating);
            playlist.insert(current_song, songToAdd);
            current_song--;
            display_playlist(playlist, *current_song);
            continue;
        }
        else if (userSelection == 'l' || userSelection == 'L') {
            display_playlist(playlist, *current_song);
            continue;
        }
        else if (userSelection == 'q' || userSelection == 'Q') {
            Qispressed = true;
        }
        else {
            std::cout << "You entered an invalid character please try again" << std::endl;
            continue;
        }
    } while (Qispressed != true);
    //std::cout << "To be implemented" << std::endl;
    // Your program logic goes here

    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}