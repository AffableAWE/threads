// Problem Statement: Producer-Consumer Problem (Bounded Buffer Implementation)
// --------------------------------------------------------------
// - This program demonstrates a solution to the Producer-Consumer problem
//   using threads, mutexes, and condition variables in C++.
//
// Description:
// - We have a shared buffer (deque) of limited size (`max_buffer`).
// - The producer thread generates values (starting from 100) and adds them to the buffer.
// - The consumer thread removes values from the buffer and processes them.
//
// Constraints:
// 1. The producer must wait if the buffer is full (i.e., `buffer.size() == max_buffer`).
// 2. The consumer must wait if the buffer is empty (i.e., `buffer.size() == 0`).
//
// Tools Used:
// 1. **Mutex (`std::mutex`)**: Ensures that access to the shared buffer is thread-safe.
// 2. **Condition Variable (`std::condition_variable`)**:
//    - Used to block the producer when the buffer is full and unblock it when space becomes available.
//    - Used to block the consumer when the buffer is empty and unblock it when new data is produced.
//
// Behavior:
// - The producer pushes values into the buffer, decrementing from 100.
// - The consumer pops values from the buffer and prints them.
// - Synchronization is handled using condition variables to avoid race conditions or deadlocks.
//
// Objective:
// - Efficiently synchronize producer and consumer threads, ensuring no data is lost, and resources 
//   are utilized effectively.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

std::mutex mu;
std::condition_variable cond;
std::deque<int> buffer;
const unsigned int max_buffer = 50;

void producer(int val) {
    while(val) {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, []() {return buffer.size() < max_buffer;});
        buffer.push_back(val);
        std::cout<< "Produced: " << val << std::endl;
        val--;
        lock.unlock();
        cond.notify_one();
    }
}

void consumer() {
    while(true) {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, [](){return buffer.size() > 0;});
        int val = buffer.back();
        buffer.pop_back();
        std::cout<< "Consumed: " << val << std::endl;
        lock.unlock();
        cond.notify_one();
    }

}

int main() {
    std::thread t1(producer, 100);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;

}

