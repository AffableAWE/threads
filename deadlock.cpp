// Topic:- Deadlock - (just an example)

#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
std:: mutex m2;

void thread1() {
    m1.lock();
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    m2.lock();
    std::cout<< "Critical section of Thread 1 " << std::endl;
    m1.unlock();
    m2.unlock();
}

// We can avoid deadlock if we dont switch the order of mutex
void thread2() {
    m2.lock();
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    m1.lock();
    std::cout<< "Critical section of Thread 2 " <<std::endl;
    m2.unlock();
    m1.unlock();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
