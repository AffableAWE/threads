// Topic:- Condition Variable in C++ Threading

// Important Point: CVs are used for two purposes:
// A. Notifying other threads.
// B. Waiting for certain conditions.

// 1. Condition Variables allow running threads to wait on certain conditions, and once those conditions are met, 
//    the waiting thread is notified using:
//       a. notify_one();
//       b. notify_all();
// 2. You need a mutex to use a condition variable.
// 3. If a thread wants to wait on a condition, it must do the following:
//       a. Acquire the mutex lock using std::unique_lock<std::mutex> lock(m);
//       b. Execute wait, wait_for, or wait_until. The wait operations atomically release the mutex 
//          and suspend the execution of the thread.
//       c. When the condition variable is notified, the thread is awakened, and the mutex is atomically re-acquired.
//          The thread should then check the condition and resume waiting if the wake-up was spurious.

// Notes:
// 1. Condition Variables are used to synchronize two or more threads.
// 2. The best use case of a condition variable is the Producer/Consumer problem.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
int balance = 0;

void addMoney (int money) {
    std::lock_guard<std::mutex> lg(m);
    balance += money;
    std::cout<< "Amount added successfully, Current Balance: " << balance << std::endl;
    cv.notify_one();
}

void withdrawMoney (int money) {
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, [] { return (balance != 0)? true : false; });
    if (balance >= money) {
        balance -= money;
        std::cout<< "Amount Deducted: " << money << std::endl;
    }
    else {
        std::cout<< "Amount cant be deducted, current balance is less than " << money << std::endl;
    }
    std::cout<< "Current amount is: " << balance << std::endl;
}

int main() {
    std::thread t1(withdrawMoney, 500);
    // std::this_thread::sleep_for(std::chrono::seconds(5)); Doesn't matter t1 will wait till t2 is finished.
    std::thread t2(addMoney, 500);

    t1.join();
    t2.join();

    return 0;
}






























