// Topic:- std::lock()

// It is use to lock multiple mutex at the same time.

// Important:
// syntax -> std::lock(m1, m2, m3, m4);
// 1. All arguments are locked via a sequence of call to lock(), try_lock(), or unlock() on each argument.
// 2. Order of locking is not defined (it will try to lock provided mutex in any order and ensure that there is
//    no dead lock).
// 3. It is a blocking call.

// Example 1 ---> No Deadlock
// Thread 1                     Thread 2
// std::lock(m1, m2);           std::lock(m1, m2);

// Example 2 ---> No Deadlock (most important example to under why no deadlock)
// Thread 1                     Thread 2
// std::lock(m1, m2);           std::lock(m2, m1); 

/* Why No Deadlock ---> Both threads use std::lock() to lock m1 and m2. The std::lock() function ensures that the
                        locks are acquired in a consistent, well-defined order across all threads, regardless of the 
                        order in which they are requested. 
                   ---> This prevents circular waiting, which is a key condition for deadlock. 
                   ---> std::lock() also provides exception safety by releasing any already-acquired locks if an 
                        exception occurs. */

// Example 3 ---> No Deadlock 
// Thread 1                     Thread 2
// std::lock(m1, m2, m3, m4)    std::lock(m3, m4);
//                              std::lock(m1, m2);

/* Why No Deadlock ---> std::lock() ensures that all locks (m1, m2, m3, m4) are acquired in a consistent order, avoiding 
                        circular waiting and thus preventing deadlock, even with different lock sequences in threads. */ 

// Example 4 ---> Deadlock
// Thread 1                     Thread 2
// std::lock(m1, m2)            std::lock(m3, m4)
// srd::lock(m3, m4)            std::lock(m1, m2)

/* Why Deadlock ---> Thread 1 locks m1 and m2, then tries to lock m3 and m4.
                     Thread 2 locks m3 and m4, then tries to lock m1 and m2.
                     Both threads hold some locks and wait for each other to release the remaining locks,
                     creating a circular waiting condition, which leads to deadlock. */ 

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void task1() {
    while(1) {
        // std::lock(m1, m2); // Deadlock will be avoided with this statement
        m1.lock(); // ---\ Deadlock will happen now
        m2.lock(); // ---/ 
        std::cout << "task a \n";
        m1.unlock();
        m2.unlock();
    }
}

void task2() {
    while(1) {
        //std::lock(m2, m1);
        m2.lock();
        m1.lock();
        std::cout << "task b \n";
        m2.unlock();
        m1.unlock();
    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}


