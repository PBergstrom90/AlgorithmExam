#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "atm.h"

// Skapa en Bankomat med MAP
// NYCKEL: Kontonummer
// VALUE: saldo
// Skapa en meny där man kan skapa konto. Logga in på konto. Ta ut och sätta in pengar.

void createAccount(std::map<int, std::shared_ptr<ATM>>& atm){
    std::string name;
    int accountNumber;
    int balance;

    std::cout << "\nEnter your name: ";
    std::cin >> name;
    
    std::cout << "Enter your accountnumber: ";
    std::cin >> accountNumber;
    
    std::cout << "Enter your balance: ";
    std::cin >> balance;
    if (atm.find(accountNumber) != atm.end()){
        std::cout << "ERROR. Account already exists." << std::endl;
        return;
    }
    std::shared_ptr<ATM> newAccount = std::make_shared<ATM>(name, accountNumber, balance);
    
    atm.insert(std::make_pair(accountNumber, newAccount));
    std::cout << "\nAccount created successfully." << std::endl;
}
void logIn(std::map<int, std::shared_ptr<ATM>>& atm){
    int accountNumber;
    std::cout << "\nEnter your accountnumber: " << std::endl;
    std::cin >> accountNumber;
    auto it = atm.find(accountNumber);
    if (it == atm.end()) {
        std::cout << "ERROR. Account not found." << std::endl;
    } else {
        std::cout << "Welcome: " << it->second->getName() << std::endl;
        std::cout << "Your current balance is: " << it->second->getBalance() << std::endl;
    }
}
void withdraw(std::map<int, std::shared_ptr<ATM>>& atm){
    int accountNumber;
    std::cout << "\nEnter your accountnumber: " << std::endl;
    std::cin >> accountNumber;
    auto it = atm.find(accountNumber);
    if (it == atm.end()) {
        std::cout << "ERROR. Account not found." << std::endl;
    } else {
        int amount;
        std::cout << "How much money would you like to withdraw? " << std::endl;
        std::cin >> amount;
        int currentBalance = it->second->getBalance();
        it->second->setBalance(currentBalance - amount);
        std::cout << "Withdrawing... " << std::endl;
        std::cout << "Your new balance is: " << it->second->getBalance() << std::endl;
    }
}
void insert(std::map<int, std::shared_ptr<ATM>>& atm){
    int accountNumber;
    std::cout << "\nEnter your accountnumber: " << std::endl;
    std::cin >> accountNumber;
    auto it = atm.find(accountNumber);
    if (it == atm.end()) {
        std::cout << "ERROR. Account not found." << std::endl;
    } else {
        int amount;
        std::cout << "How much money would you like to insert? " << std::endl;
        std::cin >> amount;

        int currentBalance = it->second->getBalance();
        it->second->setBalance(currentBalance + amount);

        std::cout << "Your new balance is: " << it->second->getBalance() << std::endl;
    }
}

void AtmSim ()
{
    bool isRunning = true;
    std::map<int, std::shared_ptr<ATM>> atm;
    while(isRunning){
        std::cout << "\n--- Welcome to the ATM ---" << std::endl;
        std::cout << "1. Create account" << std::endl;
        std::cout << "2. Log in to account" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. Insert" << std::endl;
        std::cout << "5. Exit program" << std::endl;
        std::cout << "Enter your choice: ";
        int choice = 0;
        std::cin >> choice;
        if(!std::cin){
            std::cout << "\nERROR. Wrong input." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
        switch(choice){
            case 1:
                createAccount(atm);
                break;
            case 2:
                logIn(atm);
                break;
            case 3:
                withdraw(atm);
                break;
            case 4:
                insert(atm);
                break;
            case 5:
                std::cout << "\nProgram closing... " << std::endl;
                isRunning = false;
                break;
            default:
                std::cout << "\nERROR. Wrong input." << std::endl;
                break;
        }
    }  
};