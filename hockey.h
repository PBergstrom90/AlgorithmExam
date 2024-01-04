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

    friend std::istream& operator>>(std::istream& is, HockeyPlayer& player) {
        is >> player.id >> player.name >> player.jersey >> player.teamName;
        return is;
    }

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
        LRUCache(int capacity) : capacity(capacity) {
        };

    private:
        int capacity;
};

class FileStorage {
    std::vector<HockeyPlayer> playerStorage;
    std::string fileName;

public:
    FileStorage(std::string fileName) : fileName(fileName) {}

    void addPlayer(const HockeyPlayer& player) {
        playerStorage.push_back(player);
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
            }
            file.close();
            std::cout << "Players read from file: " << fileName << std::endl;
        } else {
            std::cerr << "Unable to open file: " << fileName << std::endl;
        }
    }
};

#endif // __HOCKEY_H