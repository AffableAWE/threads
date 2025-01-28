// Topic:- Thread OR Process Synchronization

// Note:- We will use only thread examples to explain this topic.

// Points;
// 0. Thread OR Process synchronize to access critical section.
// 1. Critical Section is one or more collection of program statements which should be executed by only thread
//    or process at a time. 

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
long long bankBalance = 0;

void addMoney(long long money) {
    m.lock();
    bankBalance += money;
    m.unlock();
}

int main() {
    std::thread t1(addMoney, 100);
    std::thread t2(addMoney, 200);

    t1.join();
    t2.join();

    std::cout<< "Final Bank Balance: " << bankBalance << std::endl;
}



