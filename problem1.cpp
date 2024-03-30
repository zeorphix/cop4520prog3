// Evan Tieu
// Programming Assignment 3
// Problem 1: The Birthday Presents Party
// COP 4520, Spring 2024

#include <iostream>
#include <thread>
#include <mutex>

const int NUM_PRESENTS = 500000;
const int NUM_SERVANTS = 4;

struct Present {
    int tag;
    
    Present* next;
    Present(int num) : tag(num), next (nullptr) {}
};

int main(void)
{

    return 0;
}
