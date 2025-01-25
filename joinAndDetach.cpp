// Topic: Use of join(), detach(), and joinable()

// Join Notes:
// 1. Once a thread is started, we wait for this thread to finish by calling the join() function on the thread object.
// 2. Double join() will result in program termination.
// 3. If needed, we should check if the thread is joinable before joining (using the joinable() function).

// Detach Notes:
// 1. This is used to detach a newly created thread from the parent thread.
// 2. Always check before detaching a thread that it is joinable; otherwise, we may end up with double detachment.
//    Double detach() will result in program termination.
// 3. If we have detached a thread and the main function returns, the detached thread's execution is suspended.

// General Notes:
//  Either join() or detach() should be called on a thread object. Otherwise, during the thread object's destructor,
//  the program will terminate. This happens because the destructor checks if the thread is still joinable. If it is,
//  the program terminates.


#include<iostream>
#include<thread>

using namespace std;

void run(int count) {
    while (count --> 0) {
        cout << count << " Priyansh " << endl;
    }
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Thread Finished " << endl;
}

int main() {
    thread t1(run, 10);
    cout<< "Before main()" << endl;
    t1.join();

    //if(t1.joinable()) {
    //    t1.detach();
    //}
 
    cout<< "After main()" << endl;
    return 0;
}
