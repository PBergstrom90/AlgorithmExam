# Algorithm Exam

## Author
- Pontus Bergström

## Sensor Data Analysis
This C++ program analyzes sensor data related to altitude, speed, and fuel consumption. It performs various operations on the data, such as sorting, checking altitude measurements, identifying top speed occurrences, and adjusting fuel consumption.

## Overview
The program utilizes a SensorData class to store information about sensor readings, including altitude, speed, and fuel consumption. It generates random data for analysis and performs operations on the dataset.

## Prerequisites
- C++ Compiler
- Standard Template Library (STL)
- iostream, string, vector, algorithm, ctime, and cstdlib headers

## Functions

### FillData
Generates random sensor data for analysis.

### SortAllData
Sorts the sensor data based on timestamp.

### CheckSensorData
Checks and prints altitude data for a specific date.

### CheckTopSpeed
Identifies entries of speed data above a specified limit.

### AdjustFuelConsumption
Increases fuel consumption values by 75%.

### Additional Files
- **hospital.cpp & hospital.h**: Implements a hospital simulation with a patient queue algorithm. The program manages a queue of patients, allowing users to add new patients, call the next patient, view the current queue, and exit the simulation.

- **atm.cpp & atm.h**: Introduces a basic ATM simulation using a map algorithm to store account information. Users can create accounts, log in, withdraw and deposit money. The map efficiently associates account numbers with account details.

- **hockey.cpp & hockey.h**: Introduces a hockey player class, an LRU (Least Recently Used) cache algorithm, and file storage for a hockey player simulation. The LRU cache efficiently manages a limited number of hockey player records in memory, providing quick access to frequently accessed players while optimizing space usage. The file storage component reads and writes player data to a text file.

## How to Run
1. Compile the main program using a C++ compiler.
2. Run the compiled executable.
