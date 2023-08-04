//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#include "Philosopher.hpp"

Philosopher::Philosopher(const int id, DiningSurface& table, Display& disp, const int maxWait): 
        mID{id}, mTable{table}, mDisplay{disp}, mRandom_wait_time{100, maxWait}
{}

Philosopher::~Philosopher() {}

void Philosopher::think() {
    mDisplay.update(mID, 'T');
    mTable.waitFor(mRandom_wait_time(mRandom_engine) * 1ms);
}

void Philosopher::eat() {
    mDisplay.update(mID, 'E');
    mTable.waitFor(mRandom_wait_time(mRandom_engine) * 1ms);
}

void Philosopher::run() {
    while (true) {
        think();
        if(!mTable.waitForSticks(*this)) {
            return;
        }
        eat();
        mTable.layDownSticks(*this);
    }
}

void Philosopher::displayWait() const {
    mDisplay.update(mID, 'W');
}

void Philosopher::displayTerminate() const {
    mDisplay.update(mID, 'x');
}