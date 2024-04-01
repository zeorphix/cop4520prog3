// Evan Tieu
// Programming Assignment 3
// Problem 2: Atmospheric Temperature Reading Module
// COP 4520, Spring 2024

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

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

void readModule(int sensorNum)
{

}

void compileReport(int sensorNum)
{

}

int main(void)
{
    using namespace std;

    vector<thread> sensorThreads;

    for (int i = 0; i < NUM_SENSORS; ++i)
        sensorThreads.push_back(thread(readModule), i + 1));

    for (auto& sensor : sensors)
        sensor.join();
    
    return 0;
}
