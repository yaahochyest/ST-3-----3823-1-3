// Copyright 2026 Salykina Alena

#include "TimedDoor.h"

#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <memory>
#include <stdexcept>
#include <thread>

using ::testing::Return;

class MockTimerClient : public TimerClient {
public:
    MOCK_METHOD(void, Timeout, (), (override));
};

class MockDoor : public Door {
public:
    MOCK_METHOD(void, lock, (), (override));
    MOCK_METHOD(void, unlock, (), (override));
    MOCK_METHOD(bool, isDoorOpened, (), (override));
};

class TimedDoorTest : public ::testing::Test {
protected:
    void SetUp() override {
        door = std::make_unique<TimedDoor>(0);
        door->lock();
    }

    void TearDown() override {
        door.reset();
    }

    std::unique_ptr<TimedDoor> door;
};

TEST_F(TimedDoorTest, DoorClosedAfterLock) {
    EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, ReturnsCorrectTimeout) {
    TimedDoor localDoor(5);

    EXPECT_EQ(localDoor.getTimeOut(), 5);
}

TEST_F(TimedDoorTest, ClosedDoorDoesNotThrow) {
    EXPECT_NO_THROW(door->throwState());
}

TEST_F(TimedDoorTest, OpenDoorThrowsException) {
    EXPECT_THROW(door->unlock(), std::runtime_error);
}

TEST_F(TimedDoorTest, MultipleLocksKeepDoorClosed) {
    door->lock();
    door->lock();

    EXPECT_FALSE(door->isDoorOpened());
}

TEST(TimerTest, TimeoutMethodCalled) {
    MockTimerClient mock;
    Timer timer;

    EXPECT_CALL(mock, Timeout()).Times(1);

    timer.tregister(0, &mock);
}

TEST(TimerTest, NullptrClientDoesNotThrow) {
    Timer timer;

    EXPECT_NO_THROW(timer.tregister(0, nullptr));
}

TEST(MockDoorTest, LockMethodCalled) {
    MockDoor mock;

    EXPECT_CALL(mock, lock()).Times(1);

    mock.lock();
}

TEST(MockDoorTest, UnlockMethodCalled) {
    MockDoor mock;

    EXPECT_CALL(mock, unlock()).Times(1);

    mock.unlock();
}

TEST(MockDoorTest, StubbedDoorState) {
    MockDoor mock;

    EXPECT_CALL(mock, isDoorOpened())
        .WillOnce(Return(true));

    EXPECT_TRUE(mock.isDoorOpened());
}

TEST(TimedDoorIntegrationTest, DoorLockedBeforeTimeout) {
    TimedDoor door(1);

    door.lock();

    std::exception_ptr exceptionPtr;

    std::thread thread([&door, &exceptionPtr]() {
        try {
            door.unlock();
        }
        catch (...) {
            exceptionPtr = std::current_exception();
        }
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    door.lock();

    thread.join();

    if (exceptionPtr) {
        std::rethrow_exception(exceptionPtr);
    }
}
