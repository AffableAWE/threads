// Topic:- Recursive Mutex in C++

// Notes;
// 0. It is same as mutex but, same thread can lock one mutex multiple times using recursion mutex.
// 1. If thread T1 first call lock/try_lock on recursive mutex m1, then m1 is locked by T1, now as T1
//    is running in recursion T1 can call lock/try_lock any number of times there is no issue.
// 2. But if T1 have acquired 10 times lock/try_lock on mutex m1 then thread t1 will have to unlock
//    it 10 times otherwise no thread will be able lock mutex mutex m1.
//    It means recursive mutex keeps count how many times it was locked so that many times it should be unlocked.
// 3. How many times we can lock recursive mutex is not defined but where that number reaches and if we were calling 
//    lock() it will return std::system_error OR if we were calling try_lock() then it will return false.

// Bottom Line;
// 0. It is similar to mutex but have extra facility that it can be locked multiple time by same thread.
// 1. If we can avoid recursive mutex then we should because it brings overhead to the system.
// 2. It can be used in loops also.

#include<iostream>
#include<thread>
#include<mutex>

// Example 1; With Recursion

std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor) {
    if (loopFor < 0) return;

    m1.lock();

    std::cout << "ThreadId:" << c << " " << buffer++ << std::endl;
    recursion(c, --loopFor);
    m1.unlock();
    std::cout << "Unlocked by Thread " << c << std::endl;
}

int main() {
    std::thread t1(recursion, '1', 10);
    std::thread t2(recursion, '2', 10);

    t1.join();
    t2.join();

    return 0;
}

// If you can't understand the recursion part then look at the iterative approach
// Example 2; With Loops
/*
std::recursive_mutex m1;

int main() {
    for (int i = 0; i<5; ++i) {
        m1.lock();
        std::cout << "Locked " << i << std::endl;
    }

    for (int i = 0; i<5; ++i) {
        m1.unlock();
        std::cout << "Unlocked " << i << std::endl;
    }
    return 0;
}
*/











