#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include "hospital.h"

    Patient::Patient(std::string name, int queueNumber) : name(name), queueNumber(queueNumber) {
        startTime = std::chrono::system_clock::now();
    };

void HospitalSim() {
    std::queue<Patient> patientQueue;
    bool isRunning = true;
    auto timeNow = std::chrono::system_clock::now();
    while (isRunning) {
        std::cout << "\n--- WELCOME TO THE HOSPITAL ---" << std::endl;
        std::cout << "1. Enter a patient to the queue." << std::endl;
        std::cout << "2. Call on the next patient." << std::endl;
        std::cout << "3. Show the queue." << std::endl;
        std::cout << "4. Exit the program." << std::endl;
        std::cout << "Enter your choice: ";
        int choice = 0;
        std::cin >> choice;
        if(!std::cin){
            std::cout << "\nERROR. Wrong input." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
        std::string name;
        auto timeNow = std::chrono::system_clock::now();    
        switch (choice) {
        case 1:
            std::cout << "\nEnter the name of the patient: ";
            std::cin >> name;
            timeNow = std::chrono::system_clock::now();
            std::cout << "Patient " << name << " added to the queue at: " << timeNow << std::endl;
            patientQueue.push(Patient(name, patientQueue.size() + 1));
            break;
        case 2: 
            if (!patientQueue.empty()) {
                Patient& patient = patientQueue.front();
                std::cout << "\nPatient '" << patient.getName() << "' with queue number " << patient.getQueueNumber() << " is now being called." << std::endl;
                std::cout << "Patient waiting time: " << patient.getWaitingTime() << " seconds." << std::endl;
                patientQueue.pop();
            } else {
                std::cout << "\nThere are no patients in the queue." << std::endl;
            }
            break;
        case 3:
            if (!patientQueue.empty()){
                // Create a temporary copy of the queue, for printing purposes.
                std::queue<Patient> tempQueue = patientQueue;
                std::cout << "\n--- PATIENT QUEUE ---" << std::endl;
                while (!tempQueue.empty()) {
                    Patient patient = tempQueue.front();
                    tempQueue.pop();
                    std::cout << patient.getQueueNumber() << ". " << patient.getName() << std::endl;
                }
            } else {
                std::cout << "\nThere are no patients in the queue." << std::endl;
            }
            break;
        case 4:
            std::cout << "\nProgram closing... " << std::endl;
            isRunning = false;
            break;
        default:
            std::cout << "\nINVALID CHOICE. Please try again." << std::endl;
            break;
    }
    }
};