// Topic:- unique_lock in C++ (std::unique_lock<mutex> lock(m1))

// Notes;
// 0. The class unique_lock is a mutex ownership wrapper.
// 1. It Allows:
//      a. Can have different locking strategies.
//      b. time-constrained attempts at locking (try_lock_for, try_lock_until).
//      c. recursive locking.
//      d. transfer of lock ownership (move not copy).
//      e. condition variables.

// Locking Strategies
//      TYPE                     EFFECTS;
// 1. defer_lock                do not acquire ownership of the mutex.
// 2. try_to_lock               try to acquire ownership of the mutex without blocking.
// 3. adopt_lock                assume the calling thread already has ownership of the mutex.

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
int buffer = 0;

// Example 1. simple lock using unique_lock
void task(const char* threadNumber, int loopFor) {
    std::unique_lock<std::mutex> lock(m1); // Automatically calls the lock on mutex m1
    for (int i = 0; i<loopFor; ++i) {
        buffer++;
        std::cout<< threadNumber << " " << buffer << std::endl;
    }
}

// Example 2. with defer_lock
void task2(const char* threadNumber, int loopFor) {
    std::unique_lock<std::mutex> lock(m1, std::defer_lock); // Does not call lock on mutex m1, because we used differ_lock
    lock.lock(); // But then we have to tell explicitly tell to lock when ever we want to lock mutex m1.
    for (int i = 0; i<loopFor; ++i) {
        buffer++;
        std::cout << threadNumber << " " << buffer << std::endl;
    }
    // lock.unlock(); is not needed as it will be unlocked in destructor of unique_lock.
}

// Example 3. with try_to_lock
void task3(const char* threadNumber, int loopFor) {
    std::unique_lock<std::mutex> lock(m1, std::try_to_lock); // Attempt to lock m1 without blocking
    if (lock.owns_lock()) { // checking if the lock is successfully acquired
        for (int i = 0; i<loopFor; ++i) {
            buffer++;
            std::cout<< threadNumber << " " << buffer << std::endl;
        }
    }
    else {
        std::cout << "Thread " << threadNumber << " could not acquire the lock. Another thread is using the resource. \n ";
    }
}

// Example 4. with adopt_lock
void task4(const char* threadNumber, int loopFor) {
    m1.lock(); // locking explicitly
    std::unique_lock<std::mutex> lock(m1, std::adopt_lock); // adopting the ownership of the lock
    for (int i = 0; i<loopFor; ++i) {
        buffer++;
        std::cout<< threadNumber << " " << buffer << std::endl;
    }
}

int main() {
    std::thread t1(task, "T1 ", 10);
    std::thread t2(task, "T2 ", 10);

    std::thread t3(task2, "T3 ", 10);
    std::thread t4(task2, "T4 ", 10);

    std::thread t5(task3, "T5 ", 10);
    std::thread t6(task3, "T6 ", 10);

    std::thread t7(task4, "T7 ", 10); 
    std::thread t8(task4, "T8 ", 10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    return 0;

}
