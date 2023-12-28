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
