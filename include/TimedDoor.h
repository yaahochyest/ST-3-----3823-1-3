// Copyright 2026 Salykina Alena

#ifndef INCLUDE_TIMEDDOOR_H_
#define INCLUDE_TIMEDDOOR_H_

class TimerClient {
 public:
    virtual void Timeout() = 0;
};

class Door {
 public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool isDoorOpened() = 0;
};

class TimedDoor;

class DoorTimerAdapter : public TimerClient {
 private:
    TimedDoor& door;

 public:
    explicit DoorTimerAdapter(TimedDoor&);
    void Timeout() override;
};

class TimedDoor : public Door {
 private:
    DoorTimerAdapter* adapter;
    int timeoutValue;
    bool opened;

 public:
    explicit TimedDoor(int timeout);
    ~TimedDoor();

    bool isDoorOpened() override;
    void unlock() override;
    void lock() override;

    int getTimeOut() const;

    void throwState();
};

class Timer {
 private:
    TimerClient* client;

    void sleep(int seconds);

 public:
    void tregister(int delay, TimerClient* timerClient);
};

#endif  // INCLUDE_TIMEDDOOR_H_
