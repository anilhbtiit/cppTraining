#if 0

/*
 mutex (short for “mutual exclusion”) ensures that
  only one thread can access a critical section of code at a time. 
  It prevents race conditions and maintains data integrity.


  Mutex is a locking mechanism, whereas Semaphore is a signaling mechanism

  https://en.cppreference.com/w/cpp/thread/counting_semaphore


*/


#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Declare a mutex

int sharedNumber = 0;

void increment() {
    for (int i = 0; i < 1000000; ++i) {
        mtx.lock(); // Acquire the lock
        sharedNumber++;
        mtx.unlock(); // Release the lock
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Shared number after execution: " << sharedNumber << std::endl;
    return 0;
}


#endif

#if 1

//c++ 20


/*
A non-negative integer variable shared among threads.
Works via signaling (using Wait and Signal operations).

Multiple threads can access the critical section simultaneously.
Machine-independent.
Allows a specified number of threads to enter.


*/


//g++ --std=c++20 .\a09mutexandsemaphore.cpp

#include <iostream>
#include <thread>
#include <semaphore>

// Shared design database (for demonstration purposes)
class DesignDatabase {
public:
    void accessDatabase(int taskId) {
        // Simulate accessing the database
        std::cout << "Task " << taskId << " accessing the design database." << std::endl;
        // ...
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        std::cout << "Task " << taskId << " finished accessing the database." << std::endl;
    }
};

DesignDatabase designDb;
std::counting_semaphore<1> dbSemaphore(1); // Initialize with a count of 1

void task(int taskId) {
    // Acquire the semaphore (waits if not available)
    dbSemaphore.acquire();
    designDb.accessDatabase(taskId);
    // Release the semaphore
    dbSemaphore.release();
}

int main() {
    std::thread t1(task, 1); // Task 1: Parsing design files
    std::thread t2(task, 2); // Task 2: Optimization
    std::thread t3(task, 3); // Task 3: Placement and routing
    std::thread t4(task, 4); // Task 4: Report generation

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}


#endif

/*


Functionality: It acts as a locking mechanism, allowing a process to acquire and release the mutex before entering or leaving a critical section of code.
Advantages:
No race conditions: Only one process can be in the critical section at any given time.
Data consistency: Ensures integrity by preventing concurrent access.
Priority inheritance: Helps mitigate priority inversion issues.
Disadvantages:
Starvation: If a thread holding the mutex sleeps or gets preempted, others can’t enter the critical section.
Busy waiting: May lead to CPU cycle wastage

Semaphore:
Purpose: A semaphore is a non-negative integer variable shared among threads.
Functionality: It uses signaling to control access to shared resources.
Advantages:
Multiple threads: Allows multiple threads to access the critical section simultaneously.
Machine-independent: Works across different platforms.
Flexible: Can limit the number of threads accessing a resource.




std::counting_semaphore serves as a synchronization primitive. Let’s break it down:

std::counting_semaphore:
A counting semaphore is a type of semaphore that maintains an internal count.
It allows a specified number of threads to access a shared resource concurrently.
we initialized it with a count of 1 (std::counting_semaphore<1>), which means only one thread can
acquire the semaphore at a time.
When a thread acquires the semaphore, the count decreases by 1; when it releases the semaphore,
the count increases by 1.
It’s a useful tool for managing access to shared resources, ensuring proper synchronization,
and preventing data corruption.

*/