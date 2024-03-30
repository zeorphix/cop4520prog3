// Evan Tieu
// Programming Assignment 3
// Problem 1: The Birthday Presents Party
// COP 4520, Spring 2024

#include <iostream>
#include <mutex>
#include <thread>

const int NUM_PRESENTS = 500000;
const int NUM_SERVANTS = 4;

std::mutex mtx;

struct Present {
    int tag;
    
    Present* next;
    Present(int num) : tag(num), next (nullptr) {}
};

class PresentChain {
    private:
        Present* head;
    
    public:
        PresentChain() : head(nullptr) {}

        void add(int tag) 
        {
            Present* newPresent = new Present(tag);

            mtx.lock()

            if (!head || head->tag > tag)
            {
                newPresent->next = head;
                head = newPresent;
            }

            else
            {
                Present* current = head;
                
                while (current->next && current->next->tag < tag)
                    current = current->next;

                newPresent->next = current->next;
                current->next = newPresent;   
            }

            mtx.unlock();
        }

        void remove(int tag) 
        {
            mtx.lock();

            if (!head)
            {

            }

            if (!head->tag == tag)
            {

            }

            mtx.unlock();
        }

        bool search(int tag)
        {
            mtx.lock();
            Present* current = head;

            while (current)
            {
                if (current->tag == tag)
                {
                    mtx.unlock();
                    return true;
                }

                current = current->next;
            }

            mtx.unlock();
            return false;
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
