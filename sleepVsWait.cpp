// Topic:- Sleep Vs Wait

/*  SLEEP; 
    Sleep is: "I m done with my timeslice, and"
    please dont give me another one for atleast
    'n' miliseconds." The OS doesnt even try to 
    schedule the sleeping thread until requested 
    time has passed.

    Points;
    1. It will keep the lock and sleep.
    2. Sleep is directly to thread,it is 
       a thread function.

    WAIT;
    Wait is: "I m done with my timeslice, and
    dont give me another timeslice until someone
    calls notify() or notifyAll()."

    As with sleep(), the OS wont even try to 
    schedule your task unless someone calls 
    notify() (Or one of a few waking scenrios occues).

    Points;
    1. It releases the lock and wait.
    2. Wait is on condition variable, it is like there
    is a condition variable in a thread and wait is 
    applied to that CV but it ends up putting thread
    in waiting state.
*/
