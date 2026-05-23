// Copyright 2026 Salykina Alena

#include "TimedDoor.h"

#include <chrono>
#include <stdexcept>
#include <thread>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& timedDoor)
    : door(timedDoor) {
}

void DoorTimerAdapter::Timeout() {
    door.throwState();
}

TimedDoor::TimedDoor(int timeout)
    : adapter(new DoorTimerAdapter(*this)),
    timeoutValue(timeout),
    opened(false) {
}

TimedDoor::~TimedDoor() {
    delete adapter;
    adapter = nullptr;
}

bool TimedDoor::isDoorOpened() {
    return opened;
}

void TimedDoor::lock() {
    opened = false;
}

void TimedDoor::unlock() {
    opened = true;

    Timer timer;
    timer.tregister(timeoutValue, adapter);
}

int TimedDoor::getTimeOut() const {
    return timeoutValue;
}

void TimedDoor::throwState() {
    if (opened) {
        throw std::runtime_error("Door is still opened");
    }
}

void Timer::sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Timer::tregister(int delay, TimerClient* timerClient) {
    client = timerClient;

    sleep(delay);

    if (client != nullptr) {
        client->Timeout();
    }
}
