// Topic:- Threading in C++11

#include<iostream>
#include<thread>

using namespace std;
typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end) {
    for (ull i = start; i <= end; ++i) {
        if ((i & 1) == 0) {
            evenSum += i;
        }
    }
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; ++i) {
        if ((i & 1) == 1) {
            oddSum += i;
        }
    }
}

int main() {
    ull start = 0, end = 1900000000;

    auto startTime = chrono::high_resolution_clock::now();

    thread t1(findEven, start, end);
    thread t2(findOdd, start, end);

    t1.join();
    t2.join();

    // findOdd(start, end);
    // findEven(start, end);

    auto stopTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stopTime - startTime);

    cout << "Odd Sum: " << oddSum << endl;
    cout << "Even Sum: " << evenSum << endl;

    cout << "Duration: " << duration.count()/1000000 << endl; 
}
