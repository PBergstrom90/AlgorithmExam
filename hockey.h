#ifndef __HOCKEY_H
#define __HOCKEY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

class HockeyPlayer {
public:
    HockeyPlayer(int id, std::string name, int jersey, std::string teamName);
    HockeyPlayer();
    int getId() const;
    std::string getName() const;
    int getJersey() const;
    std::string getTeamName() const;

    friend std::istream& operator>>(std::istream& is, HockeyPlayer& player);
    friend std::ostream& operator<<(std::ostream& os, const HockeyPlayer& player);

private:
    int id;
    std::string name;
    int jersey;
    std::string teamName;
};

class LRUCache {
public:
    LRUCache(int capacity, std::vector<HockeyPlayer> cache);
    bool isPlayerInCache(int playerId);
    HockeyPlayer getPlayerFromCache(int id);
    void printCache() const;
    void addPlayer(HockeyPlayer& player);

private:
    int capacity;
    std::vector<HockeyPlayer> cache;
};

class FileStorage {
public:
    FileStorage(std::string fileName);
    void addPlayer(const HockeyPlayer& player);
    HockeyPlayer getPlayerFromTextFile(int id);
    void writeToFile();

private:
    std::vector<HockeyPlayer> playerStorage;
    std::string fileName;
};

#endif // __HOCKEY_H
