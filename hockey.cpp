#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "hockey.h"

void HockeyChacher(){
    std::cout << "\nHockey LRU-Cache" << std::endl;
    std::random_device rd;
    int amountOfPlayers = 1000;
    LRUCache cache(10);
    FileStorage fileStorage("hockeyplayers.txt");

    // Add players to the storage
    for (int i = 1; i < amountOfPlayers; i++) {
        fileStorage.addPlayer(HockeyPlayer(i, "Player" + std::to_string(i), i, "Team" + std::to_string(i)));
    }   

    fileStorage.writeToFile();
    fileStorage.readFromFile();
};