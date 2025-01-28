// Topic:- std::async

// Notes;
// 1. It runs a function asynchronously (potentially in a new thread) and returns a std::future that
//    will hold the result.
// 2. There are 3 launch policies for creating task;
//      a. std::launch::async (async usually refers to create a thread)
//      b. std::launch::deffered (deffered refers to do not create a thread)
//      c. std::launch::async | std::launch::deffered (this statement means `let the computer decide`)

// How it works;
// 1. It automatically creates a thread (Or picks from internal thread pool) and a promise object from us.
// 2. Then passes the std::promise object to thread function and returns the associated std::future object.
// 3. When our passed argument function exists then its value will be set in this promise object,
//    so eventually return value will be available in std::future object.

// Side Notes;
// 1. We can send functors and lambda functions as callback to std::async, it will work the same

#include <iostream>
#include <thread>
#include <future>

typedef long int ull;

ull findOdd(ull start, ull end) {
    ull oddSum = 0;
    std::cout<< "ThreadId: " << std::this_thread::get_id() << std::endl;
    for (ull i = start; i <= end; ++i) {
        if (i & 1) {
            oddSum += i;
        }
    }
    return oddSum;
}

int main() {
    ull start = 0, end = 1900000000;

    std::cout<< "ThreadId: " << std::this_thread::get_id() << std::endl;
    std::cout<< "Thread created if policy is std::launch::async!!" <<std::endl;
    std::future<ull> oddSum = std::async(std::launch::async, findOdd, start, end);

    std::cout << "Waiting for the Result: " <<std::endl;

    std::cout<< "OddSum: " << oddSum.get() << std::endl;

    std::cout<< "Completed " << std::endl; 

    return 0;
}



















