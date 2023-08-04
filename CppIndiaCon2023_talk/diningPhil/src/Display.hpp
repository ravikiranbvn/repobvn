//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once
#include <iostream>
#include <iomanip>
#include <mutex>
#include <memory>
#include "AsyncOut.hpp"

class Display {
public:
    Display(std::uint32_t numberOfPhilosophers) {
        std::uint32_t numOfChars = (numberOfPhilosophers-1) * 2 + 1;
        mLine.resize(numOfChars, ' ');
    }

    void update(int phid, char symbol) {
        std::unique_lock<std::mutex> lk(mMutex);
        mLine[phid * 2] = symbol;
        AsyncOut() << std::setw(10) << mTurn++ << std::setw(0) << ": " << mLine << "\n";
    }

private:
    std::string mLine;
    int         mTurn{0};
    std::mutex  mMutex;
};