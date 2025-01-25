:Wq#include<iostream>
#include<thread>

using namespace std;

// Thread Creation
// Using 1. Function Pointer - The basic form of thread creation
void fun(int x) {
    while (x --> 0) {
        cout << x << " ";
    }
    cout << endl;
}

 int main() {

    thread t1(fun, 11);
    t1.join();
    return 0;
}

// Using 2. Lamda Functions
int main() {
    // We can directly inject lambda at thread creation time
    // auto fun = ;

    thread t([](int x) {
        while (x --> 0) {
            cout<< x <<endl;
        }
    }, 11);

    t.join();
    return 0;
}

// Using 3. Functor - Funtion Objects
class base {
public:
    void operator ()(int x) {
        while (x --> 0) {
            cout << x << endl;
        }
    }
};

int main() {
    thread t((base()), 11);
    t.join();
    return 0;
}

// Using 4. Non - Static Member Function
class base {
public:
    void run(int x) {
        while (x --> 0) {
            cout << x << endl;
        }
    }
};

int main() {
    base b;
    thread t(&base::run, &b, 11);
    t.join();
    return 0;

}

// Using 5. Static Member Function
class base {
public:
    static void run(int x) {
        while(x --> 0) {
        cout<< x << endl;
        }
    }
};

int main() {
    thread t(&base :: run, 11);
    t.join();
    return 0;

}


















