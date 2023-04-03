//
// Created by bleppe on 03/04/23.
//

#include "State.h"

void State::on_enter() {}

void State::on_exit() {}

void State::on_input(InputEvent &evt) {}

void StateMachine::initialize(State *state) {
    current = state;
    state->on_enter();
}

void StateMachine::transition(State *nextState) {
    auto prev = current;
    current = nextState;
    current->prev = prev;
    prev->on_exit();
    current->on_enter();
}

void StateMachine::get_back() {
    current->on_exit();
    current = current->prev;
    current->on_enter();
}

void StateMachine::on_input(InputEvent &evt) {
    current->on_input(evt);
}