#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
// For formatting the date.
#include <iomanip>

#include "hospital.h"
#include "atm.h"
#include "hockey.h"

enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData
{
	float value;
	SensorType sensorType;
	time_t time;
public:
	SensorType GetSensorType() { return sensorType; }
	float GetValue() { return value; }
	void SetValue(float v) { value = v; }
	time_t GetTime() { return time; }
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
};

void HospitalSim();
void AtmSim();
void HockeyChacher();
void FillData(std::vector<SensorData> &v);
void CheckSensorData(std::vector<SensorData> &v);
void CheckTopSpeed(std::vector<SensorData> &v);
void AdjustFuelConsumption(std::vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);

// DRIVER CODE
int main()
{
	std::vector<SensorData> sensorData;
	// Initialize the vector with random data.
	FillData(sensorData);

	std::cout << "\nPART 1 - Check sensor data for altitude measurements: \n" << std::endl;
	CheckSensorData(sensorData);	

	std::cout << "\nPART 2 - Check top speed above 99.9 km/h: \n" << std::endl;	
	CheckTopSpeed(sensorData);

	std::cout << "\nPART 3 - Increase fuel consumption by 75%: \n" << std::endl;
	AdjustFuelConsumption(sensorData);

	// Hospital - QUEUE
	HospitalSim();

	// ATM - MAP
	AtmSim();

	// HockeyPlayer - LRU-CACHE
	HockeyChacher();

    return 0;
}

void CheckSensorData(std::vector<SensorData> &v) {
    time_t targetDate = CreateTime(2012, 1, 2, 0, 0, 0);
    // Format the target date for better readability.
    struct tm* targetDateStruct = localtime(&targetDate);
    std::stringstream formattedTargetDate;
    formattedTargetDate << std::put_time(targetDateStruct, "%Y-%m-%d");

	int count = count_if(v.begin(), v.end(), [targetDate](SensorData& data) {
		return (data.GetSensorType() == SensorType::Altitude && 
			data.GetTime() >= targetDate && 
			data.GetTime() < targetDate + 24 * 3600);
		});
	std::cout << "Date: " << formattedTargetDate.str() << std::endl;
    std::cout << "Found " << count << " entries of altitude data." << std::endl;
}

void CheckTopSpeed(std::vector<SensorData> &v){
    int count = count_if(v.begin(), v.end(), [](SensorData& data) { 
        return data.GetSensorType() == SensorType::SpeedInKmh; 
    });
    auto aboveSpeedLimit = find_if(v.begin(), v.end(), [](SensorData& data) { 
        return data.GetSensorType() == SensorType::SpeedInKmh && data.GetValue() > 99.9f; 
    });

    std::cout << "Found " << count << " entries of 'Speed in Kilometers'." << std::endl;
    if (aboveSpeedLimit != v.end()) {
        std::cout << "Found an entry above max speed (99.9 km/h): " << aboveSpeedLimit->GetValue() << " km/h." << std::endl;
    } else {
        std::cout << "No entries above max speed (99.9 km/h) found." << std::endl;
    }
}


void AdjustFuelConsumption(std::vector<SensorData> &v){
	bool success = false;
	int count = std::count_if(v.begin(), v.end(), [](SensorData& data) { 
		return data.GetSensorType() == SensorType::FuelConsumption; 
		});
	std::cout << "Found " << count << " entries of 'Fuel Consumption'." << std::endl;	
	std::cout << "\nAdjusting fuel consumption to increase by 75%." << std::endl;
	std::for_each(v.begin(), v.end(), [&success](SensorData& data) {
		if(data.GetSensorType() == SensorType::FuelConsumption) {
			data.SetValue(data.GetValue() * 1.75f);
			// DEBUG-Printout
			// cout << "Fuel Consumption: " << data.GetValue() << endl;
			success = true;	
		}
	});
	if(success == true){
		std::cout << "Adjusted " << count << " entries of 'Fuel Consumption' successfully." << std::endl;
	} else {
		std::cout << "Failed to adjust 'Fuel Consumption'." << std::endl;
	}
}

void FillData(std::vector<SensorData>& v)
{
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1;
	}
}

time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);
}