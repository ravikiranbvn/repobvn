//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <string>
#include "Display.hpp"
#include "ChopStick.hpp"
#include "DiningSurface.hpp"

using namespace std::literals;

class DiningSurface;
class Philosopher {
public:
    const int mID;
    std::shared_ptr<ChopStick> mLeftStick;
    std::shared_ptr<ChopStick> mRightStick;

    Philosopher(const int id, DiningSurface& table, Display& disp, const int maxWait);
    ~Philosopher();

    Philosopher(const Philosopher&) = delete;
    Philosopher(Philosopher&&) = delete;
    Philosopher& operator=(const Philosopher& other) = delete;
    Philosopher& operator=(Philosopher&& other) = delete;

    void run();
    void displayWait() const;
    void displayTerminate() const;

private:
    void think();
    void eat();

    DiningSurface&                      mTable;
    Display&                            mDisplay;
    std::random_device                  mRandom_device{};
    std::mt19937                        mRandom_engine{mRandom_device()};
    std::uniform_int_distribution<int>  mRandom_wait_time;
};


