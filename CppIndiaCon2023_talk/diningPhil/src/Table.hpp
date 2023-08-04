//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once

#include <condition_variable>
#include <chrono>
#include <deque>
#include <memory>
#include <thread>
#include <vector>
#include <algorithm>

#include "ChopStick.hpp"
#include "Display.hpp"
#include "DiningSurface.hpp"

class Table: public DiningSurface {
public:   
    Table(const int philosopherCount, Display& display, const int maxWait);
    ~Table();

    Table(const Table&) = delete;
    Table(Table&&) = delete;
    Table& operator=(const Table& other) = delete;
    Table& operator=(Table&& other) = delete;

    void start();
    void terminate();
    
private:
    bool waitFor(std::chrono::milliseconds interval) override;
    bool waitForSticks(const Philosopher& phil) override;
    void layDownSticks(const Philosopher& phil) override;

    void seatPhilosophers(Philosopher& phil);
    bool canEat(const Philosopher& phil);
    bool adjacent(int leftId, int rightId);

    std::vector<std::unique_ptr<Philosopher>> mPhilosophers;
    std::vector<std::shared_ptr<ChopStick>> mSticks;

    std::mutex               mMutex;
    std::condition_variable  mMayTryToEatNow;
    std::condition_variable  mHasTerminated;
    std::deque<int>          mWaitingList;
    bool                     mTerminated{false};
    std::vector<std::thread> mPhilThreads;
};