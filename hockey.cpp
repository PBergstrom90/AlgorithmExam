#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "hockey.h"

// HockeyPlayer-Class methods

HockeyPlayer::HockeyPlayer(int id, std::string name, int jersey, std::string teamName) : id(id), name(name), jersey(jersey), teamName(teamName) {
}
HockeyPlayer::HockeyPlayer() : id(0), name("NULL"), jersey(0), teamName("NULL") {
}
int HockeyPlayer::getId() const {
    return id;
}
std::string HockeyPlayer::getName() const {
    return name;
}
int HockeyPlayer::getJersey() const {
    return jersey;
}
std::string HockeyPlayer::getTeamName() const {
    return teamName;
}
 // For reading from file.
std::istream& operator>>(std::istream& is, HockeyPlayer& player) {
    is >> player.id >> player.name >> player.jersey >> player.teamName;
    return is;
}
// For writing to file.
std::ostream& operator<<(std::ostream& os, const HockeyPlayer& player) {
    os << player.id << ' ' << player.name << ' ' << player.jersey << ' ' << player.teamName;
    return os;
}

// LRU-Class methods

LRUCache::LRUCache(int capacity, std::vector<HockeyPlayer> cache) : capacity(capacity), cache(cache) {
}

bool LRUCache::isPlayerInCache(int playerId) {
    return std::any_of(cache.begin(), cache.end(), [playerId](HockeyPlayer& player) {
        return player.getId() == playerId;
    });
}

HockeyPlayer LRUCache::getPlayerFromCache(int id) {
    auto it = std::find_if(cache.begin(), cache.end(), [id](HockeyPlayer& player) {
        return player.getId() == id;
    });
    if (it != cache.end()) {
        HockeyPlayer player = *it;
        cache.erase(it);
        cache.push_back(player);
        return player;
    } else {
        return HockeyPlayer();
    }
}

void LRUCache::printCache() const {
    for (const auto& player : cache) {
        std::cout << "ID: " << player.getId() << '\n'
                << "Name: " << player.getName() << '\n'
                << "Jersey: " << player.getJersey() << '\n'
                << "Team: " << player.getTeamName() << '\n'
                << "--------------------------\n" << std::endl;
    }
}

void LRUCache::addPlayer(HockeyPlayer& player) {
    auto it = std::find_if(cache.begin(), cache.end(), [&player](HockeyPlayer& p) {
        return p.getId() == player.getId();
    });
    // If Player is already in the cache, move it to the most recently used position.
    if (it != cache.end()) {
        cache.erase(it);
        cache.push_back(player);
    } else {
        if (cache.size() >= capacity) {
            // If the cache is full, remove the least recently used player
            std::cout << "Removing least recently used player: " << cache.front().getId() << std::endl;
            cache.erase(cache.begin());
        }
        // Player is not in the cache, add it.
        cache.push_back(player);
        std::cout << "Hockeyplayer added to cache: " << player.getId() << std::endl;
    }
}

// FileStorage-class methods

FileStorage::FileStorage(std::string fileName) : fileName(fileName) {
}

void FileStorage::addPlayer(const HockeyPlayer& player) {
    playerStorage.push_back(player);
}

HockeyPlayer FileStorage::getPlayerFromTextFile(int id) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        HockeyPlayer player;
        while (file >> player) {
            if (player.getId() == id) {
                // Close the file once the player is found.
                file.close();
                return player;
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << fileName << std::endl;
    }
    return HockeyPlayer();
}

void FileStorage::writeToFile() {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& player : playerStorage) {
            file << player << '\n';
        }
        file.close();
        std::cout << "Players written to file: " << fileName << std::endl;
    } else {
        std::cout << "Unable to open file: " << fileName << std::endl;
    }
}

// DRIVER CODE
void HockeyChacher(){
    bool isRunning = true;
    std::cout << "\n--- Hockey LRU-Cache ---\n" << std::endl;
    std::random_device rd;
    int amountOfPlayers = 1000000;
    LRUCache cache(10, std::vector<HockeyPlayer>());
    FileStorage fileStorage("hockeyplayers.txt");

    // Add players to the file, with random jersey- and teamnumbers.
    for (int i = 1; i <= amountOfPlayers; i++) {
        std::uniform_int_distribution<int> jerseyDistribution(1, 100);
        std::uniform_int_distribution<int> teamDistribution(1, 50);
        uint16_t randomJerseyNumber = jerseyDistribution(rd);
        uint16_t randomTeamNumber = teamDistribution(rd);
        fileStorage.addPlayer(HockeyPlayer(i, "Player" + std::to_string(i), randomJerseyNumber, "Team" + std::to_string(randomTeamNumber)));
    } 

    // Write players to text file.
    fileStorage.writeToFile();
    
    // Fill cache with 10 players from file.
    for (int i = 1; i <= 10; i++) {
        HockeyPlayer player = fileStorage.getPlayerFromTextFile(i);
        if (!cache.isPlayerInCache(player.getId())) {
            cache.addPlayer(player);
        }
    }

    // Allow user to search for player ID from cache or file.
    while (isRunning){
        std::cout << "\nLRU-Cache printout: " << "\n" << std::endl;
        cache.printCache();
        int searchId = 0;
        std::cout << "\nPlease enter a player ID: ";
        std::cin >> searchId;
        HockeyPlayer player = cache.getPlayerFromCache(searchId);
        if (player.getId() != 0) {
            std::cout << "Player ID found in cache: " << player.getId() << std::endl;
        } else {
            std::cout << "Player not found in cache, searching in file..." << std::endl;
            player = fileStorage.getPlayerFromTextFile(searchId);
            if (player.getId() > 0 && player.getId() <= amountOfPlayers) {
                std::cout << "Player ID found in file: " << player.getId() << std::endl;
                cache.addPlayer(player);
            } else {
                std::cout << "Player not found in file." << std::endl;
            }
        }
        std::cout << "Try again? (y/n): ";
        char answer;
        std::cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            continue;
        } else {
            std::cout << "Program closing... " << std::endl;
            isRunning = false;
        }
    }
};