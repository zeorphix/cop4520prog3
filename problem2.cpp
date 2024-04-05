// Evan Tieu
// Programming Assignment 3
// Problem 2: Atmospheric Temperature Reading Module
// COP 4520, Spring 2024

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

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

std::vector<TemperatureData> readings;

void readModule(int sensorNum)
{
    using namespace std;

    for (int i = 0; i < READINGS_PER_HOUR; ++i)
    {
        double temperature = -100 + static_cast<double>(rand()) / RAND_MAX * (70 + 100);

        mtx.lock();
        cout << "temperature reading is " << temperature << endl;

        readings.push_back({temperature, std::time(nullptr)});
        mtx.unlock();

    }
}

void compileReport(int sensorNum)
{

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
    
    return 0;
}
