// Topic: std::mutex::try_lock() in C++ Threading
//
// 0. try_lock() attempts to lock the mutex and returns immediately. 
//    If the lock is successfully acquired, it returns true; otherwise, it returns false.
// 1. If try_lock() cannot lock the mutex, it does not block, which is why it is called non-blocking.
// 2. Double try_lock() on the same mutex by the same thread is not allowed. 
//    This leads to a deadlock situation with undefined behavior. 
//    (If you need to lock the same mutex multiple times by the same thread, use recursive_mutex.)

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int counter = 0;
mutex mtx;

// Reminder: Using `mtx.try_lock()` means some increments may be skipped if the mutex is not available, 
// leading to a `counter` value less than 200,000. This is expected behavior!
void increaseTheCounterFor100000Times() {
    for (int i = 0; i < 100000; ++i) {
        if (mtx.try_lock()) {
            ++counter;
            mtx.unlock();
        }
    }
}

int main() {
    thread t1(increaseTheCounterFor100000Times);
    thread t2(increaseTheCounterFor100000Times);

    t1.join();
    t2.join();

    cout<< "Counter increased till: " << counter << endl;
    return 0;
}



// List of other try_lock functions in C++:

// 1. std::mutex::try_lock()
// 2. std::recursive_mutex::try_lock()
// 3. std::timed_mutex::try_lock()
// 4. std::timed_mutex::try_lock_for()
// 5. std::timed_mutex::try_lock_until()
// 6. std::recursive_timed_mutex::try_lock()
// 7. std::recursive_timed_mutex::try_lock_for()
// 8. std::recursive_timed_mutex::try_lock_until()
