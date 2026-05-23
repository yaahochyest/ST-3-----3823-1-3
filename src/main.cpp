// Copyright 2026 Salykina Alena

#include "TimedDoor.h"

#include <iostream>

int main() {
    TimedDoor door(1);

    try {
        door.unlock();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
