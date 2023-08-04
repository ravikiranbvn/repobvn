//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
// 

// valgrind --leak-check=full --show-leak-kinds=all ./dp_v
// valgrind --tool=helgrind ./dp_v

#include <iostream>
#include <string>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include "AsyncOut.hpp"
#include "Philosopher.hpp"
#include "Display.hpp"
#include "Table.hpp"

static constexpr int size = 5;
static constexpr int maxPhilosopherWait = 3000;
static constexpr int duration = 7000;
static std::condition_variable cv;
static std::mutex cv_m;

int main() {
    Display disp{size};
    Table table{size, disp, maxPhilosopherWait};
    AsyncOut() << "Starting... dp simulation: T -> thinking, E -> eating and W -> waiting/want to eat\n";
    table.start();

    std::unique_lock<std::mutex> lk(cv_m);
    auto result = cv.wait_for(lk, std::chrono::milliseconds(duration));
    if (result == std::cv_status::timeout) {
        AsyncOut() << "Terminating...\n";
        table.terminate();;
    }
    else {
        AsyncOut() << "Could not timeout...\n";
    }

    return 0;
}