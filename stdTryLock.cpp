// Topic :- std::try_lock() in C++11
// 
// Notes;
// 0. std::try_lock() tries to lock all the lockable objects passed in it one by one in given order.
// 1. Syntax :- std::try_lock(m1, m2, m3, m4, m5, m6....,mn);
// 2. The actual use of std::try_lock() function is, it can try to lock multiple mutex objects at the same time.
// 3. If it fails to lock any of the mutex then it will release all the mutex it locked before.
// 4. if a call to try_lock results in an exception, unlock is called for any other locked objects before rethrowing. 

#include<mutex>
#include<thread>
#include<iostream>

using namespace std;

int X = 0, Y = 0;
mutex m1, m2;

void doSomeWordForSeconds(int seconds) { 
    this_thread::sleep_for(std::chrono::seconds(seconds));
}

void incrementXY(int& XorY, mutex& m, const char* desc) {
    for (int i = 0; i < 5; ++i) {
        m.lock();
        ++XorY;
        cout << desc << " " << XorY << endl;
        m.unlock();
        doSomeWordForSeconds(1);
    }
}

void consumeXY() {
    int useCount = 5;
    int XplusY = 0;

    while(1) {
        int lockResult = std::try_lock(m1, m2);
        if (lockResult == -1) {
            if (X != 0 && Y != 0) {
                --useCount;
                XplusY += X + Y;
                X = 0;
                Y = 0;
                cout << " X Plus Y: " << XplusY << endl;
            }
            m1.unlock();
            m2.unlock();
            if (useCount == 0) break;
        }
    }
}

int main() {

    thread t1(incrementXY, std::ref(X), std::ref(m1), "X");
    thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y");
    thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
