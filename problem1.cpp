// Evan Tieu
// Programming Assignment 3
// Problem 1: The Birthday Presents Party
// COP 4520, Spring 2024

#include <iostream>
#include <mutex>
#include <unordered_set>
#include <thread>

const int NUM_PRESENTS = 500000;
const int BATCH_SIZE = 1000;
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

        void add(int tag, int batchSize) 
        {
            using namespace std;
            
            mtx.lock();

            Present* prev = nullptr;
            Present* current = head;

            cout << "add" << endl;

            for (int i = 0; i < batchSize; ++i)
            {
                // cout << i << endl;
                
                Present* newPresent = new Present(tag + i);

                while (current && current->tag < tag + i)
                {
                    prev = current;
                    current = current->next;
                }

                if (!prev)
                {
                    newPresent->next = head;
                    head = newPresent;
                }

                else
                {
                    prev->next = newPresent;
                    newPresent->next = current;
                }

                prev = newPresent;
            }

            mtx.unlock();
        }

        void remove(int tag, int batchSize) 
        {
            using namespace std;

            mtx.lock();

            cout << "remove" << endl;
            
            Present* current = head;
            Present* prev = nullptr;

            while (current)
            {
                if (current->tag >= tag && current->tag < tag + batchSize)
                {
                    if (prev)
                        prev->next = current->next;
                   
                    else
                        head = current->next;
                    
                    Present* temp = current;
                    current = current->next;
                    delete temp;
                }

                else
                {
                    prev = current;
                    current = current->next;
                }
            }

            mtx.unlock();
        }

        bool search(int tag)
        {
            using namespace std;
            
            mtx.lock();
            
            cout << "search" << endl;

            Present* current = head;

            while (current)
            {
                if (current->tag == tag)
                {
                    mtx.unlock();
                    cout << "tag found" << endl;
                    return true;
                }

                current = current->next;
            }

            cout << "tag not found" << endl;
            mtx.unlock();

            return false;
        }
};

void task(int num, PresentChain& chain, std::unordered_set<int>& tags)
{
    using namespace std;

    for (int i = 0; i < NUM_PRESENTS; i += BATCH_SIZE)
    {
        // cout << i << endl;

        if (i % 3 == 0)
        {
            int tagToRemove = i % 1000;

            chain.remove(tagToRemove, BATCH_SIZE);

            for (int j = 0; j < BATCH_SIZE; ++j)
                tags.erase(tagToRemove + j);
        }
        else if (i % 3 == 1)
        {
            int tagToAdd = i % 1000;
            chain.add(tagToAdd, BATCH_SIZE);

            for (int j = 0; j < BATCH_SIZE; ++j)
                tags.insert(tagToAdd + j);
        }
        else
        {
            int tagToSearch = i % 1000;

            chain.search(tagToSearch);
        }
    }

}

int main(void)
{
    using namespace std;
    
    PresentChain chain;
    unordered_set<int> tags;
    thread servants[NUM_SERVANTS];

    for (int i = 0; i < 4; ++i)
        servants[i] = thread(task, i + 1, ref(chain), ref(tags));

    for (auto& servant : servants)
        servant.join();
    
    cout << "all presents have thank you notes written" << endl;

    return 0;
}
