#ifndef __HOSPITAL_H__
#define __HOSPITAL_H__

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <chrono>

class Patient {
public:
    Patient(std::string name, int queueNumber);
      std::string getName() {
        return name;
    }
    int getQueueNumber() {
        return queueNumber;
    }
    int getWaitingTime() {
        auto endTime = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    }

private:
    std::string name;
    int queueNumber;
    std::chrono::time_point<std::chrono::system_clock> startTime;
};

#endif // __HOSPITAL_H__