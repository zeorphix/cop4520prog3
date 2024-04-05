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
        cout << "temperature reading is " << temperature << endl;

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

    cout << "hourly report" << endl;
    cout << "top 5" << endl;
    
    for (int i = temperatures.size() - 1; i >= temperatures.size() - 5; --i)
        cout << temperatures[i] << " F ";
    
    cout << endl;
    cout << "low 5" << endl;
    
    for (int i = 0; i < 5; ++i)
        cout << temperatures[i] << " F ";

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
