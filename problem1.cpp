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

            // cout << "add" << endl;

            Present* newPresent = new Present(tag);

            mtx.lock();

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

        void remove(int tag, int batchSize) 
        {
            using namespace std;

            mtx.lock();

            // cout << "remove" << endl;
            
            if (!head)
            {
                cout << "nothing to remove" << endl;
                
                mtx.unlock();
                return;
            }

            if (head->tag == tag)
            {
                Present* temp = head;
                head = head->next;
                delete temp;
                
                mtx.unlock();
                return;
            }

            Present* current = head;

            while (current->next && current->next->tag != tag)
            {
                current = current->next;
            }

            if (current->next)
            {
                Present* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }

            else
            {
                // cout << "present with tag number " << tag << " not found" << endl;
            }

            mtx.unlock();
        }

        bool search(int tag, int batchSize)
        {
            using namespace std;
            
            mtx.lock();
            
            // cout << "search" << endl;

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

void task(int num, PresentChain& chain, std::unordered_set<int>& tags)
{
    using namespace std;

    for (int i = 1; i <= NUM_PRESENTS; ++i)
    {
        if (i % 3 == 0)
        {
            int tagToRemove = i % 1000;

            chain.remove(tagToRemove, BATCH_SIZE);
            tags.erase(tagToRemove);
        }
        else if (i % 3 == 1)
        {
            int tagToAdd = i % 1000;
            chain.add(tagToAdd, BATCH_SIZE);
            tags.insert(tagToAdd);
        }
        else
        {
            int tagToSearch = i % 1000;

            if (chain.search(tagToSearch, BATCH_SIZE))
                cout << "servant " << num << "found present with tag " << tagToSearch << endl;
            else
                cout << "servant " << num << "did not find present with tag " << tagToSearch << endl;
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
