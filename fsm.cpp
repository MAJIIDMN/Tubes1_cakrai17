#include "fsm.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include <chrono>
#include <vector>
#include <thread>

using namespace std;

uint32_t millis() {
    return static_cast<uint32_t>(chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now().time_since_epoch()).count());
}

FSM::FSM() : currentState(SystemState::INIT), lastHeartbeat(0), delay(1000), errorCount(0), moveCount(0) {
    stateHistory.clear();
}

FSM::FSM(uint32_t delay) : currentState(SystemState::INIT), lastHeartbeat(0), delay(delay), errorCount(0), moveCount(0) {
    stateHistory.clear();
}

FSM::~FSM() {
    stateHistory.clear();
}

SystemState FSM::getCurrentState() const {
    return currentState;
}

void FSM::transitionToState(SystemState newState) {
    currentState = newState;
    lastHeartbeat = millis();
    addStateToHistory(newState, lastHeartbeat);
}

void FSM::setDelay(uint32_t d) {
    delay = d;
}

void FSM::getDelay(uint32_t &d) const {
    d = delay;
}

void FSM::setErrorCount(int count) {
    errorCount = count;
}

int FSM::getErrorCount() const {
    return errorCount;
}

// Setter move count
void FSM::setMoveCount(int count) {
    moveCount = count;
}

int FSM::getMoveCount() const {
    return moveCount;
}
void FSM::addStateToHistory(SystemState state, uint32_t time) {
    stateHistory.emplace_back(state, time);
}

vector<pair<SystemState, uint32_t>> FSM::getStateHistory() const {
    return stateHistory;
}

uint32_t FSM::getLastHeartbeat() const {
    return lastHeartbeat;
}

void FSM::setLastHeartbeat(uint32_t heartbeat) {
    lastHeartbeat = heartbeat;
}

void FSM::start() {
    while (currentState != SystemState::STOPPED) {
        update();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    shutdown();
}

void FSM::update() {
    lastHeartbeat = millis();
    addStateToHistory(currentState, lastHeartbeat);

    switch (currentState) {
        case SystemState::INIT:
            performInit();
            break;
        case SystemState::IDLE:
            performProcess();
            break;
        case SystemState::MOVEMENT:
            performMovement();
            break;
        case SystemState::SHOOTING:
            performShooting();
            break;
        case SystemState::CALCULATION:
            performCalculation();
            break;
        case SystemState::ERROR:
            performErrorHandling();
            break;
        case SystemState::STOPPED:
            shutdown();
            break;
    }
}

void FSM::printStatus() {
    cout << "Status:\n";
    cout << "- State: " << static_cast<int>(currentState) << endl;
    cout << "- Last Heartbeat: " << lastHeartbeat << " ms\n";
    cout << "- Delay: " << delay << " ms\n";
    cout << "- Error Count: " << errorCount << "\n";
    cout << "- Move Count: " << moveCount << "\n";
}

void FSM::printStateHistory() {
    cout << "State History:\n";
    for (auto &entry : stateHistory) {
        cout << "- State: " << static_cast<int>(entry.first)
             << " at " << entry.second << " ms\n";
    }
}


void FSM::performInit() {
    cout << "Initializing system...\n";
    setDelay(1000);
    transitionToState(SystemState::IDLE);
    printStatus();
}

void FSM::performProcess() {
    cout << "\nChoose an action:\n"
         << "1. Display Status and History\n"
         << "2. Move\n"
         << "3. Shoot\n"
         << "4. Calculate\n"
         << "Enter choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            printStatus();
            printStateHistory();
            break;
        case 2:
            transitionToState(SystemState::MOVEMENT);
            break;
        case 3:
            transitionToState(SystemState::SHOOTING);
            break;
        case 4:
            transitionToState(SystemState::CALCULATION);
            break;
        default:
            cout << "Invalid input. Staying in IDLE.\n";
    }
}

void FSM::performMovement() {
    cout << "Moving...\n";
    moveCount++;
    if (moveCount >= 3) {
        transitionToState(SystemState::SHOOTING);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::performShooting() {
    cout << "Shooting...\n";
    moveCount = 0;
    transitionToState(SystemState::IDLE);
}

void FSM::performCalculation() {
    cout << "Performing calculation...\n";
    if (moveCount == 0) {
        transitionToState(SystemState::ERROR);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::performErrorHandling() {
    cout << "Error occurred, performing error handling...\n";
    errorCount++;
    if (errorCount > 3) {
        transitionToState(SystemState::STOPPED);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::shutdown() {
    cout << "System stopped, shutting down...\n";
    stateHistory.clear();
}