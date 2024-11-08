// File: SingletonBase.hpp
// Description: Abstract base class for implementing the Singleton design pattern with thread safety using a POSIX mutex.

#ifndef SINGLETONBASE_HPP
#define SINGLETONBASE_HPP

#include <pthread.h>
#include <stdexcept>

class SingletonBase {
protected:
    // Protected constructor to prevent instantiation.
    SingletonBase() {}

    // Destructor
    virtual ~SingletonBase() {}

    // Mutex for thread-safe Singleton initialization
    static pthread_mutex_t mutex;

    // Added a pure virtual function to make the class abstract
    virtual void doSomething() = 0; // Pure virtual function

public:
    // Delete copy constructor and assignment operator to prevent copying
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    // Static method to get the instance of the derived Singleton class
    static SingletonBase* getInstance();
/*  an example of how its should look:
    static SingletonBase* getInstance() {
        pthread_mutex_lock(&mutex);  // Lock the mutex
        if (instance == nullptr) {
            instance = new SingletonDerived();  // Create the Singleton instance
        }
        pthread_mutex_unlock(&mutex);  // Unlock the mutex
        return instance;
    }
*/
};

// Initialize the static mutex
pthread_mutex_t SingletonBase::mutex = PTHREAD_MUTEX_INITIALIZER;

#endif // SINGLETONBASE_HPP
