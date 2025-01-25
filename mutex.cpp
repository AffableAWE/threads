// Topic :- Mutex In C++ Threading | Why use Mutex? | What is race condition and how to solve it? |
//          What is crictical section.

// Mutex :- Mutual Exclusion

// Race Condition;
// 0. Race condition is a situation where 2 or more threads/processes happen to change a common data at the same time.
// 1. If there is a race condition then we have to protect it and the protected section is called the critical
//    section/region.

// Mutex;
// 0. Mutex is used to avoid race conditions.
// 1. We use lock() and unlock() on a mutex to avoid race conditions.

// ***Important Points**
// 1. A race condition occurs when you try to modify data through threads. However, if you are only accessing the data, 
//    there will be no race condition.

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int myAmount = 0;
mutex m;

// Reminder: Without `m.lock()` and `m.unlock()`, `myAmount` could unpredictably be 1 or 2 due to race conditions!
void addMoney() {
    m.lock();
    ++myAmount; // This is the race condition also the critical section/region.
    m.unlock();
}

int main() {
    thread t1(addMoney);
    thread t2(addMoney);

    t1.join();
    t2.join();

    cout << "Amount: " << myAmount << endl;
    return 0;
}

