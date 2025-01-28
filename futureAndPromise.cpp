// Topic:- std::future and std::promise in threading.

// Notes;
// 1. std::promise 
//      a. Used to set values or exceptions.
// 2. std::future
//      a. used to get values from promise.
//      b. Ask promise if the value is available.
//      c. Wait for the promise.

// Program

#include <iostream>
#include <thread>
#include <future>

typedef long int ull;

void findOdd(std::promise<ull> oddSumPromise, ull start, ull end) {
    ull oddSum = 0;
    for (ull i = start; i < end; ++i) {
        if (i & 1) {
            oddSum += i;
        }
    }
    oddSumPromise.set_value(oddSum);
}

int main() {
    ull start = 0, end = 1900000000;

    std::promise<ull> oddSum;
    std::future<ull> oddFuture = oddSum.get_future();

    std::cout<< "Thread Created!! " << std::endl;
    std::thread t1(findOdd, std::move(oddSum), start, end);

    std::cout << "Waiting for the Result: " <<std::endl;

    std::cout<< "OddSum: " << oddFuture.get() << std::endl;

    std::cout<< "Completed " << std::endl;
    t1.join();

    return 0;
}
