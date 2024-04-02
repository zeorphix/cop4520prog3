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

    while (true)
    {
        double temperature = -100 + static_cast<double>(rand()) / RAND_MAX * (70 + 100);

        cout << "temperature reading is " << temperature << endl;

        mtx.lock();
        readings.push_back({temperature, std::time(nullptr)});
        mtx.unlock();

        this_thread::sleep_for(chrono::seconds(3));
    }
}

void compileReport(int sensorNum)
{

}

int main(void)
{
    using namespace std;

    vector<thread> sensors;

    for (int i = 0; i < NUM_SENSORS; ++i)
        sensors.push_back(thread(readModule, i + 1));

    for (auto& sensor : sensors)
        sensor.join();
    
    return 0;
}
