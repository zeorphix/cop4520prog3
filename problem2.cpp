// Evan Tieu
// Programming Assignment 3
// Problem 2: Atmospheric Temperature Reading Module
// COP 4520, Spring 2024

#include <iostream>
#include <thread>
#include <mutex>

const int NUM_SENSORS = 8;
const int READINGS_PER_HOUR = 60;
const int MINUTES_PER_HOUR = 60;
const int MAX_TEMPERATURE = 70;
const int MIN_TEMPERATURE = -100;

std::mutex mtx;

struct TemperatureData {
    double temperature;
    time_t timestamp;
};

void operation(int sensor_num)
{

}

int main(void)
{
    using namespace std;

    vector<thread> sensorThreads;

    for (int i = 0; i < NUM_SENSORS; ++i)
        sensorThreads.push_back(thread(operation), i + 1));

    for (auto& sensor : sensors)
        sensor.join();
    
    return 0;
}
