// File: Guard.hpp
// Description: Guard class that locks a mutex upon creation and unlocks it upon destruction (RAII pattern).

#ifndef GUARD_HPP
#define GUARD_HPP

#include <pthread.h>

class Guard {
private:
    pthread_mutex_t& mutex;

public:
    // Constructor locks the mutex
    Guard(pthread_mutex_t& m) : mutex(m) {
        pthread_mutex_lock(&mutex);
    }

    // Destructor unlocks the mutex
    ~Guard() {
        pthread_mutex_unlock(&mutex);
    }

    // Delete copy constructor and assignment operator to prevent copying
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;
};

#endif // GUARD_HPP
