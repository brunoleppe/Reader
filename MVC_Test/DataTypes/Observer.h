//
// Created by bleppe on 12/05/23.
//

#ifndef LCDTEST_OBSERVER_H
#define LCDTEST_OBSERVER_H


#include <list>
#include "input.h"

// Forward declaration of the Subject class
template <typename T>
class Subject;

// Observer abstract class
class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

template <typename T>
class Subject {
private:
    T data;
    std::list<Observer*> observers;

public:

    void set_data(T& d){
        data = d;
    }
    T& get_data(){
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
            observer->update();
        }
    }
};

class InputEventObserver : public Observer{
public:
    Subject<InputEvent> *inputSubject;
};

#endif //LCDTEST_OBSERVER_H
