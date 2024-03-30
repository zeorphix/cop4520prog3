// Evan Tieu
// Programming Assignment 3
// Problem 1: The Birthday Presents Party
// COP 4520, Spring 2024

#include <array>
#include <iostream>
#include <mutex>
#include <thread>

const int NUM_PRESENTS = 500000;
const int NUM_SERVANTS = 4;

struct Present {
    int tag;
    
    Present* next;
    Present(int num) : tag(num), next (nullptr) {}
};

class PresentChain {
    private:
        Present* head;
    
    public:
        void add(int tag) 
        {

        }

        void remove(int tag) 
        {

        }

        void search(int tag)
        {

        }
};

void task(int num, PresentChain& chain)
{

}

int main(void)
{
    using namespace std;
    
    PresentChain chain;
    thread servants[4];

    for (int i = 0; i < 4; ++i)
        servants[i] = thread(task, i + 1, ref(chain));
    
    for (auto& servant : servants)
        servant.join();

    return 0;
}
