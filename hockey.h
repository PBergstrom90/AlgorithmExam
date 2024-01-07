#ifndef __HOCKEY_H
#define __HOCKEY_H  

#include <iostream>
#include <fstream>
#include <vector>

class HockeyPlayer {
    public:
        HockeyPlayer() {
        };
        HockeyPlayer(int id, std::string name, int jersey, std::string teamName) : id(id), name(name), jersey(jersey), teamName(teamName) {
        };
    int getId() {
        return id;
    }   
    std::string getName() {
        return name;
    }
    int getJersey() {
        return jersey;
    }
    std::string getTeamName() {
        return teamName;
    }

    // For reading from file.
    friend std::istream& operator>>(std::istream& is, HockeyPlayer& player) {
        is >> player.id >> player.name >> player.jersey >> player.teamName;
        return is;
    }
    // For writing to file.
    friend std::ostream& operator<<(std::ostream& os, const HockeyPlayer& player) {
        os << player.id << ' ' << player.name << ' ' << player.jersey << ' ' << player.teamName;
        return os;
    }

    private:
        int id;
        std::string name;
        int jersey;
        std::string teamName;
};

class LRUCache {
    public:
        LRUCache(int capacity, std::vector<HockeyPlayer> cache) : capacity(capacity), cache(cache){
        };

    bool isPlayerInCache(int playerId) {
        return std::any_of(cache.begin(), cache.end(), [playerId](HockeyPlayer& player) {
            return player.getId() == playerId;
        });
    }

    HockeyPlayer getPlayer(int id) {
        auto it = std::find_if(cache.begin(), cache.end(), [id](HockeyPlayer& player) {
            return player.getId() == id;
        });
        if (it != cache.end()) {
            HockeyPlayer player = *it;
            cache.erase(it);
            cache.push_back(player);
            return player;
        } else {
            return HockeyPlayer(0, " ", 0, " ");
        }
    }

    void printCache() {
    for (auto& player : cache) {
    std::cout << "ID: " << player.getId() << '\n'
            << "Name: " << player.getName() << '\n'
            << "Jersey: " << player.getJersey() << '\n'
            << "Team: " << player.getTeamName() << '\n'
            << "--------------------------\n" << std::endl;
        }
    }

    void addPlayer(HockeyPlayer& player) {
    auto it = std::find_if(cache.begin(), cache.end(), [&player](HockeyPlayer& p) {
        return p.getId() == player.getId();
    });
    if (it != cache.end()) {
        // If Player is already in the cache, move it to the most recently used position
        cache.erase(it);
        cache.push_back(player);
    } else {
        // Player is not in the cache, add it
        if (cache.size() >= capacity) {
            // If the cache is full, remove the least recently used player
            std::cout << "Removing least recently used player: " << cache.front().getId() << std::endl;
            cache.erase(cache.begin());
        }
        cache.push_back(player);
        std::cout << "Hockeyplayer added to cache: " << player.getId() << std::endl;
    }
}

    private:
        int capacity;
        std::vector<HockeyPlayer> cache;
};

class FileStorage {
    std::vector<HockeyPlayer> playerStorage;
    std::string fileName;

public:
    FileStorage(std::string fileName) : fileName(fileName) {}

    void addPlayer(const HockeyPlayer& player) {
        playerStorage.push_back(player);
    }

HockeyPlayer getPlayer(int id) {
    auto it = std::find_if(playerStorage.begin(), playerStorage.end(), [id](HockeyPlayer& player) {
       return player.getId() == id;
    });

    if (it != playerStorage.end()) {
        return *it;
    } else {
        return HockeyPlayer();
    }
 }

    std::vector<HockeyPlayer>& getPlayerStorage() {
        return playerStorage;
    }

void writeToFile() {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (auto& player : playerStorage) {
            file << "ID: " << player.getId() << '\n'
                 << "Name: " << player.getName() << '\n'
                 << "Jersey: " << player.getJersey() << '\n'
                 << "Team: " << player.getTeamName() << '\n'
                 << "--------------------------\n";
        }
        file.close();
        std::cout << "Players written to file: " << fileName << std::endl;
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

    void readFromFile() {
        std::ifstream file(fileName);
        if (file.is_open()) {
            HockeyPlayer player;
            while (file >> player) {
                playerStorage.push_back(player);
                // Clear the player object to avoid carrying over values
                player = HockeyPlayer();
            }
            file.close();
            std::cout << "Players read from file: " << fileName << std::endl;
        } else {
            std::cerr << "Unable to open file: " << fileName << std::endl;
        }
    }
};
#endif // __HOCKEY_H