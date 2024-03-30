// Evan Tieu
// Programming Assignment 3
// Problem 2: Atmospheric Temperature Reading Module
// COP 4520, Spring 2024

#include <iostream>
#include <thread>
#include <mutex>

const int NUM_SENSORS = 8;
const int NUM_READINGS_PER_HOUR = 60;
const int NUM_MINUTES_PER_HOUR = 60;

std::mutex mtx;

int main(void)
{
    using namespace std;

    vector<thread> sensorThreads;

    for (int i = 0; i < NUM_SENSORS; ++i)
        sensorThreads.push_back(thread(generateTemp), i + 1));

    for (auto& sensor : sensors)
        sensor.join();
    
    return 0;
}
