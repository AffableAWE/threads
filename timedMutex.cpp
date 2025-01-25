// Topic:- Timed Mutex in C++ Threading (std::timed_mutex)

// Notes;
// 0. std::timed_mutex is blocked till timeout_time or the lock is acquired and returns true if success otherwise false.
// 1. Member Functions;
//      a. lock
//      b. try_lock
//      c. try_lock_for   ---\ These 2 functions makes it different from mutex.
//      d. try_lock_until ---/
//      e. unlock


// Example; try_lock_for();
// Waits until specified timeout_duration has elapsed or the lock is acquired, whichever comes first .
// On successful lock acquistion return true, otherwise returns false.

#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

// using namespace std;

int myAmount = 0;
std::timed_mutex m;

void increment(int i) {
    if(m.try_lock_for(std::chrono::seconds(1))) {
        ++myAmount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout<< "Thread " << i << " Entered" <<std::endl;
        m.unlock();
    } else {
        std::cout<< "Thread " << i << " Couldn't Enter" <<std::endl;
    }
}

// for Using try_lock_until - doing exactly the same as we did in increment function using try_lock_for
// waits until specefied timeout time have been reached or the locks is aqcuired, whichever comes first
// On a successfull lock acquisition returns true, therseise returned false.

void increment(int i) {
    auto now = std::chrono::steady_clock::now();
    if(m.try_lock_until(now + std::chrono::seconds(1))) {
        ++myAmount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Thread " << i << " Entered" << std::endl;
    } else {
        std::cout << "Thread " << i << " Couldn't Enter" << std::endl;
    }
}

int main() {
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout<< myAmount << std::endl;
    return 0;

}
