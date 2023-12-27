// PONTUS B. EXAM.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

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


void FillData(vector<SensorData> &v);
void SortAllData(vector<SensorData> &v);
void PrintAllData(vector<SensorData> &v);
void CheckSensorData(vector<SensorData> &v);
void CheckTopSpeed(vector<SensorData> &v);
void AdjustFuelConsumption(vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);

int main()
{
	vector<SensorData> sensorData;
	// Datahandling
	FillData(sensorData);
	SortAllData(sensorData);

    // Part 1 
	cout << "\nPart 1 - Check sensor data for altitude measurements: \n" << endl;
 	CheckSensorData(sensorData);	

    // Part 2
	cout << "\nPart 2 - Check top speed at 99.9: \n" << endl;	
	CheckTopSpeed(sensorData);

    // Part 3
	cout << "\nPart 3 - Adjust fuel consumption: \n" << endl;
	AdjustFuelConsumption(sensorData);

	

    return 0;
}

void SortAllData(vector<SensorData> &v){
	// Sort by timestamp:
	sort(v.begin(), v.end(), [](SensorData& a, SensorData& b) { return a.GetTime() < b.GetTime(); });
}

void PrintAllData(vector<SensorData> &v){
	// Print all data:

}

void CheckSensorData(vector<SensorData> &v) {
    int count = 0;
    time_t targetDate = CreateTime(2012, 1, 2, 0, 0, 0);

    // Format the target date for better readability
    struct tm* targetDateStruct = localtime(&targetDate);
    stringstream formattedTargetDate;
    formattedTargetDate << std::put_time(targetDateStruct, "%Y-%m-%d");

    for(auto& data : v) {
        if(data.GetSensorType() == SensorType::Altitude &&
           data.GetTime() >= targetDate &&
		   // Check if the timestamp falls within the target date
           data.GetTime() < targetDate + 24 * 3600) {
            // For printout:
			// cout << "Altitude: " << data.GetValue() << " meters." << endl;
            count++;
        }
    }
	cout << "Date: " << formattedTargetDate.str() << endl;
    cout << "Found " << count << " entries of altitude data." << endl;
}




void CheckTopSpeed(vector<SensorData> &v){
	
}	

void AdjustFuelConsumption(vector<SensorData> &v){
	
}

void FillData(vector<SensorData>& v)
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