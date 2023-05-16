//
// Created by bleppe on 12/05/23.
//

#ifndef LCDTEST_OBSERVER_H
#define LCDTEST_OBSERVER_H


#include <list>
#include "input.h"

// Forward declaration of the Subject class

class Subject;

// Observer abstract class
class Observer {
public:
    virtual void update(Subject* subject) = 0;
    virtual ~Observer() = default;
};

class Subject {
protected:
    void* data;
    std::list<Observer*> observers;

public:

    void* get_data(){
        return data;
    }

    virtual ~Subject() = default;
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    void detach(Observer* observer) {
        observers.remove(observer);
    }
    void notify() {
        for (auto observer : observers) {
            observer->update(this);
        }
    }
};

#endif //LCDTEST_OBSERVER_H
