// Evan Tieu
// Programming Assignment 3
// Problem 2: Atmospheric Temperature Reading Module
// COP 4520, Spring 2024

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const int TEMPERATURE_LIST_LENGTH = 5;
const int NUM_SENSORS = 8;
const int READINGS_PER_HOUR = 60;
const int MAX_TEMPERATURE = 70;
const int MIN_TEMPERATURE = -100;

struct TemperatureData {
    double temperature;
    time_t timestamp;
};

std::vector<TemperatureData> readings;
std::mutex mtx;

void readModule(int sensorNum)
{
    using namespace std;

    for (int i = 0; i < READINGS_PER_HOUR; ++i)
    {
        double temperature = MIN_TEMPERATURE + static_cast<double>(rand()) / RAND_MAX * (MAX_TEMPERATURE + MIN_TEMPERATURE);

        mtx.lock();
        // cout << "temperature reading is " << temperature << endl;

        readings.push_back({temperature, std::time(nullptr)});
        mtx.unlock();

    }
}

void compileReport(void)
{
    using namespace std;

    mtx.lock();
    
    vector<double> temperatures;

    for (const auto& reading : readings)
        temperatures.push_back(reading.temperature);
    
    mtx.unlock();

    sort(temperatures.begin(), temperatures.end());

    cout << "highest 5 temperatures" << endl;
    
    for (int i = temperatures.size() - 1; i >= temperatures.size() - 5; --i)
        cout << temperatures[i] << " F ";
    
    cout << endl;
    cout << "lowest 5 temperatures" << endl;
    
    for (int i = 0; i < TEMPERATURE_LIST_LENGTH; ++i)
        cout << temperatures[i] << " F ";
    
    double maxdifference = 0;
    
    for (int i = 1; i < temperatures.size(); ++i)
    {
        double difference = temperatures[i] - temperatures[i- 1];

        if (difference > maxdifference)
            maxdifference = difference;
    }

    cout << endl;
    cout << "maximum temperature difference" << endl;
    cout << maxdifference << " F" << endl;
}

int main(void)
{
    using namespace std;

    srand(time(nullptr));

    vector<thread> sensors;

    for (int i = 0; i < NUM_SENSORS; ++i)
        sensors.push_back(thread(readModule, i + 1));

    for (auto& sensor : sensors)
        sensor.join();
    
    compileReport();

    return 0;
}
