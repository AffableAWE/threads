// Topic:- lock_guard in C++ (std::lock_guard<mutex> lock(m1))

// NOTES;
// 0. It is very light weight wrapper for owning mutex on scoped basis.
// 1. It acquires mutex lock the moment you create the object of lock_guard.
// 2. It automatically removes the lock while goes out of scope.
// 3. You can not explicitly unlock the lock_guard .
// 4. You can not copy the lock_guard.

#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
int buffer = 0;

// In place of lock() and unlock(), use lock_guard instead
void task(const char* threadNumber, int loopFor) {
    std::lock_guard<std::mutex> lock(m1);
    // m1.lock();
    for (int i = 0; i<loopFor; ++i) {
        buffer++;
        std::cout << threadNumber  << " "<< buffer << std::endl;
    }
    // m1.unlock();
}

int main() {
    std::thread t1(task, "T1", 10);
    std::thread t2(task, "T2", 10);

    t1.join();
    t2.join();

    return 0;

}
