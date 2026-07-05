# threads: C++11 multithreading from scratch

Runnable examples for learning C++11 threading, one concept per file, with notes in the comments at the top of each. The files were written as the topics came up, so this README puts them in the order they make sense to study.

## Build and run

Every file is standalone. Compile with pthread support:

```bash
g++ -std=c++11 -pthread mutex.cpp -o mutex
./mutex
```

The sum-heavy examples (`threads.cpp`, `futureAndPromise.cpp`, `async.cpp`) loop to 1.9 billion, so give them a few seconds or add `-O2`.

## Learning path

### Part 1: thread basics

| # | File | What it covers |
|---|------|----------------|
| 1 | `threads.cpp` | First parallel program. Splits an odd/even sum up to 1.9 billion across two threads and times it with `chrono`. Swap in the commented serial calls and rerun to see the speedup for yourself. |
| 2 | `typesOfThreadCreation.cpp` | The five callables you can hand to `std::thread`: function pointer, lambda, functor, non-static member function, static member function. |
| 3 | `joinAndDetach.cpp` | `join()`, `detach()`, `joinable()`. Why calling neither terminates the program, and why a double join does too. |

### Part 2: race conditions and mutexes

| # | File | What it covers |
|---|------|----------------|
| 4 | `mutex.cpp` | Two threads increment a shared amount. Defines race condition and critical section, then guards it with `lock()`/`unlock()`. |
| 5 | `threadSynchronization.cpp` | Same pattern on a bank balance. Short reinforcement of the critical-section vocabulary before the mutex variants start. |
| 6 | `mutexTryLock.cpp` | `try_lock()` returns immediately instead of blocking. Two threads race to 200,000 increments and the final count comes up short, which is the point: failed attempts just skip. Ends with a list of all eight try_lock variants in the standard. |
| 7 | `timedMutex.cpp` | `std::timed_mutex` adds `try_lock_for` and `try_lock_until`. One thread holds the lock for 2 seconds while the other gives up after 1. |
| 8 | `recursiveMutex.cpp` | `std::recursive_mutex` lets the same thread lock N times, provided it unlocks N times. Shown with recursion, with a loop version in the comments. |

### Part 3: RAII lock wrappers

| # | File | What it covers |
|---|------|----------------|
| 9 | `lock_guard.cpp` | `std::lock_guard` locks on construction and unlocks when it leaves scope. No manual unlock, no copies. |
| 10 | `uniqueLock.cpp` | `std::unique_lock` with one worked example per strategy: plain, `defer_lock`, `try_to_lock` checked with `owns_lock()`, and `adopt_lock`. |

### Part 4: deadlock

| # | File | What it covers |
|---|------|----------------|
| 11 | `deadlock.cpp` | Two mutexes locked in opposite order by two threads. As committed it usually gets lucky; uncomment the two `sleep_for` lines to hit the deadlock reliably. |
| 12 | `stdLock.cpp` | `std::lock(m1, m2)` locks several mutexes without deadlock regardless of argument order. The comments walk four thread-pair scenarios and explain which deadlock and why. The code ships in the broken raw-lock form; switch to the commented `std::lock` lines to fix it. Runs in a `while(1)`, stop it with Ctrl+C. |
| 13 | `stdTryLock.cpp` | Variadic `std::try_lock(m1, m2, ...)`: locks all of them or releases whatever it managed to get. Returns -1 on success, otherwise the index of the mutex that failed. Two threads feed X and Y while a consumer grabs both locks at once to sum them. |

### Part 5: condition variables

| # | File | What it covers |
|---|------|----------------|
| 14 | `conditionVariable.cpp` | `wait` with a predicate plus `notify_one`. A withdraw thread blocks until a deposit thread funds the balance, even when the withdraw starts first. |
| 15 | `sleepVsWait.cpp` | Notes only, nothing to compile. Sleep keeps the lock and asks the scheduler for time. Wait releases the lock and sleeps until notified. |
| 16 | `boundedBufferProblem.cpp` | Producer-consumer over a 50-slot deque, the classic condition-variable exercise. Producer waits when the buffer is full, consumer waits when it is empty. The consumer loops forever, so Ctrl+C to exit. |

### Part 6: getting values out of threads

| # | File | What it covers |
|---|------|----------------|
| 17 | `futureAndPromise.cpp` | `std::promise` goes into the thread (moved, not copied) and `std::future::get()` blocks in main until the odd sum arrives. |
| 18 | `async.cpp` | `std::async` does the promise plumbing for you and returns the future directly. Covers the `launch::async` and `launch::deferred` policies, and prints thread ids so you can check whether a new thread actually ran. |

## Files that need a tweak before they compile

- `typesOfThreadCreation.cpp` keeps all five variants in one file, so there are five `main()`s. Keep the one you want and comment out the rest. Line 1 also has a stray `:Wq` from a vim exit that has to go.
- `timedMutex.cpp` defines `increment()` twice, once per timed variant. Comment one out.
- `sleepVsWait.cpp` has no `main()`. It is a reading file.

## How to work through it

Read the notes block at the top of the file, predict the output, then run it. Then break it: delete the lock in `mutex.cpp`, or put the raw locks back in `stdLock.cpp`, and run again. The failures teach more than the clean runs.
