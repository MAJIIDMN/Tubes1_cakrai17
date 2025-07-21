#include "fsm.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include <chrono>
#include <vector>

using namespace std;

enum class SystemState {
        INIT,
        IDLE,
        MOVEMENT,
        SHOOTING,
        CALCULATION,
        ERROR,
        STOPPED
};

uint32_t millis() {
    return static_cast<uint32_t>(chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now().time_since_epoch()).count());
}

// Constructor default
FSM::FSM() : currentState(SystemState::INIT), lastHeartbeat(0), delay(1000), errorCount(0), moveCount(0) {
    stateHistory.clear();
}

// Constructor dengan parameter delay
FSM::FSM(uint32_t delay) : currentState(SystemState::INIT), lastHeartbeat(0), delay(delay), errorCount(0), moveCount(0) {
    stateHistory.clear();
}

// Destructor
FSM::~FSM() {
    stateHistory.clear(); // Bersihkan vektor dari state history
}

// Ambil state saat ini
SystemState FSM::getCurrentState() const {
    return currentState;
}

// Pindah ke state baru dan catat heartbeat serta history
void FSM::transitionToState(SystemState newState) {
    currentState = newState;
    lastHeartbeat = millis();
    addStateToHistory(newState, lastHeartbeat);
}
// Setter delay
void FSM::setDelay(uint32_t d) {
    delay = d;
}

// Getter delay
void FSM::getDelay(uint32_t &d) const {
    d = delay;
}

// Setter error count
void FSM::setErrorCount(int count) {
    errorCount = count;
}

// Getter error count
int FSM::getErrorCount() const {
    return errorCount;
}

// Setter move count
void FSM::setMoveCount(int count) {
    moveCount = count;
}

// Getter move count
int FSM::getMoveCount() const {
    return moveCount;
}
