#ifndef __ATM_H__
#define __ATM_H__

#include <iostream>
#include <string>
#include <map>
#include <memory>

class ATM {
public: 
    ATM(std::string name, int accountNumber, int balance) : name(name), accountNumber(accountNumber), balance(balance) {
    };
    std::string getName(){
        return name;
    }
    int getAccountNumber(){
        return accountNumber;
    }
    int getBalance(){
        return balance;
    }
    void setBalance(int newBalance){
        balance = newBalance;
    }
private:
    std::string name;
    int accountNumber;
    int balance;
};

#endif // __ATM_H__