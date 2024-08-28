// File: main.cpp
// Description: Example usage of SingletonBase and Guard classes.

#include "SingletonBase.hpp"
#include "Guard.hpp"
#include <iostream>

class MySingleton : public SingletonBase {
private:
    MySingleton() {
        std::cout << "MySingleton instance created." << std::endl;
    }

public:
    static MySingleton* getInstance() {
        // Ensure that the mutex is locked/unlocked automatically using the Guard class
        Guard guard(SingletonBase::mutex);
        
        // Create the singleton instance
        static MySingleton* instance = new MySingleton();
        return instance;
    }

    void doSomething() {
        std::cout << "Doing something with the singleton instance." << std::endl;
    }
};

int main() {
    // Obtain the singleton instance and perform an action
    MySingleton* singleton = MySingleton::getInstance();
    singleton->doSomething();

    return 0;
}
