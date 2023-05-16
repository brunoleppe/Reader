//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_STATEMACHINE_H
#define LCDTEST_STATEMACHINE_H

enum StateEventSignal{
    EVENT_SIGNAL_ENTER,
    EVENT_SIGNAL_EXIT,

    EVENT_SIGNAL_SELECT,
    EVENT_SIGNAL_RETURN,
    EVENT_SIGNAL_OPTION,
    EVENT_SIGNAL_CANCEL,
    EVENT_SIGNAL_PUMP,
    EVENT_SIGNAL_READER,

    EVENT_SIGNAL_INVALID,
    EVENT_SIGNAL_TICK,
};

enum Status{
    STATUS_INIT,
    STATUS_HANDLED,
    STATUS_IGNORED,
    STATUS_TRANSITION,
};

struct StateEvent{
    StateEventSignal signal;
    int value;
};

class StateMachine;

class State{
protected:
protected:
    State() {}
    StateMachine *context = {};
    friend class StateMachine;
public:
    virtual Status on_event(StateEvent *evt) {
        return STATUS_IGNORED;
    }
    virtual ~State() = default;

};

class StateMachine{
protected:
    State *state = nullptr;
public:
    void set_state(State *next){
        StateEvent event = {EVENT_SIGNAL_ENTER};
        next->on_event(&event);
        state = next;
        state->context = this;
    }
    void transition(State *next){
        StateEvent event = {EVENT_SIGNAL_EXIT};
        state->on_event(&event);
        delete state;
        event.signal = EVENT_SIGNAL_ENTER;
        next->on_event(&event);
        state = next;
        state->context = this;
    }
    void stop(){
        StateEvent event = {EVENT_SIGNAL_EXIT};
        state->on_event(&event);
        delete state;
    }

};


#endif //LCDTEST_STATEMACHINE_H
