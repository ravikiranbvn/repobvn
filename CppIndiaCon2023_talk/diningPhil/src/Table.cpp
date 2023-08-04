//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#include "Table.hpp"

Table::Table(const int philosopherCount, Display& display, const int maxWait) {
        mPhilosophers.resize(philosopherCount);
        mSticks.resize(philosopherCount);
        for(int i = 0; i < philosopherCount; ++i) {
            mSticks[i] = std::make_unique<ChopStick>(i);
            mPhilosophers[i] = std::make_unique<Philosopher>(i, *this, display, maxWait);
        }

        for(int i = 0; i < philosopherCount; ++i) {
            seatPhilosophers(*mPhilosophers[i]);
        }
} 

Table::~Table() {}

bool Table::waitFor(const std::chrono::milliseconds interval) {
    std::unique_lock<std::mutex> lk(mMutex);
    mHasTerminated.wait_for(lk, interval, [this](){return mTerminated;});
    return !mTerminated;
}

bool Table::waitForSticks(const Philosopher& phil) {
    {
        std::unique_lock<std::mutex> lk(mMutex);
        mWaitingList.push_back(phil.mID);
        while(!canEat(phil)) {
            phil.displayWait();
            mMayTryToEatNow.wait(lk);
        }
    
        std::erase(mWaitingList, phil.mID);
        mMayTryToEatNow.notify_all();

        if(mTerminated) {
            return false;
        }
        
        phil.mLeftStick->pickUp();
        phil.mRightStick->pickUp();
    }
    
    
    return true;
}

void Table::layDownSticks(const Philosopher& phil) {
    {
        std::unique_lock<std::mutex> lk(mMutex);
        phil.mLeftStick->layDown();
        phil.mRightStick->layDown();
        mMayTryToEatNow.notify_all();
    }
}

void Table::seatPhilosophers(Philosopher& phil) {
    int id = phil.mID;
    phil.mLeftStick = mSticks[id];
    id++;
    
    if(id >= mSticks.size()) {
        id = 0;
    }

    phil.mRightStick = mSticks[id];
}

bool Table::canEat(const Philosopher& phil) {
    return mTerminated || phil.mLeftStick->isFree() && phil.mRightStick->isFree()   // -> To ensure correctness
        && (phil.mID == mWaitingList.front()                                        // -> To ensure fairness and starvation free 
            || 2 == std::count_if(mWaitingList.begin(), mWaitingList.end(),         // -> To ensure occupancy,  we can allow an phil to progress 
                                                                                    // if both its adjacent guests are waiting as well
                [this,id = phil.mID](int waitingId){return adjacent(waitingId, id);} // -> To ensure fairness: first added to queue -> to eat first
                ));
}

bool Table::adjacent(int leftId, int rightId) {
    return leftId == rightId + 1 || leftId == rightId -1 
        || (leftId == 0 && rightId == mPhilosophers.size() - 1)
        || (leftId == mPhilosophers.size() - 1 && rightId == 0);
}

void Table::start() {
    for(std::size_t i = 0; i < mPhilosophers.size(); ++i) {
        mPhilThreads.emplace_back([this, i](){mPhilosophers[i]->run();});
    }
}

void Table::terminate(){
    {
        std::unique_lock<std::mutex> lk(mMutex);
        mTerminated = true;
        mMayTryToEatNow.notify_all();
        mHasTerminated.notify_all();
    }    
    
    for(std::size_t i = 0; i < mPhilosophers.size(); ++i) {
        mPhilosophers[i]->displayTerminate();
        mPhilThreads[i].join();
    }
}