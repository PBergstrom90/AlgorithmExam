#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "hockey.h"

void HockeyChacher(){
    bool isRunning = true;
    std::cout << "\nHockey LRU-Cache" << std::endl;
    std::random_device rd;
    int amountOfPlayers = 10000;
    LRUCache cache(10, std::vector<HockeyPlayer>());
    FileStorage fileStorage("hockeyplayers.txt");

    // Add players to the file, with random jersey- and team numbers.
    for (int i = 1; i <= amountOfPlayers; i++) {
        std::uniform_int_distribution<int> jerseyDistribution(1, 100);
        std::uniform_int_distribution<int> teamDistribution(1, 50);
        uint16_t randomJerseyNumber = jerseyDistribution(rd);
        uint16_t randomTeamNumber = teamDistribution(rd);
        fileStorage.addPlayer(HockeyPlayer(i, "Player" + std::to_string(i), randomJerseyNumber, "Team" + std::to_string(randomTeamNumber)));
    } 

    // Write players to file and read them back to the cache.
    fileStorage.writeToFile();
    fileStorage.readFromFile();

    // Fill cache with 10 players from file.
    for (int i = 1; i <= 10; i++) {
        HockeyPlayer player = fileStorage.getPlayer(i);
        if (!cache.isPlayerInCache(player.getId())) {
            cache.addPlayer(player);
        }
    }

    // Allow user to search for player ID from cache or file.
    while (isRunning){
        std::cout << "LRU-Cache printout: " << "\n" << std::endl;
        cache.printCache();
        int id = 0;
        std::cout << "\nPlease enter a player ID: ";
        std::cin >> id;
        HockeyPlayer player = cache.getPlayer(id);
        if (player.getId() != 0) {
            std::cout << "Player ID found in cache: " << player.getId() << std::endl;
        } else {
            std::cout << "Player not found in cache, searching in file..." << std::endl;
            player = fileStorage.getPlayer(id);
            if (player.getId() != 0) {
                std::cout << "Player ID found in file: " << player.getId() << std::endl;
                cache.addPlayer(player);
            } else {
                std::cout << "Player not found in file." << std::endl;
            }
        }
        std::cout << "Try again? (y/n): ";
        char answer;
        std::cin >> answer;
        if (answer == 'n' || answer == 'N') {
            isRunning = false;
        }  
    }
};