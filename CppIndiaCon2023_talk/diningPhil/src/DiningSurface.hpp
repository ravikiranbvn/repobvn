//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once 
#include "Philosopher.hpp"

class Philosopher;
class DiningSurface {
public:
    virtual bool waitForSticks(const Philosopher&) = 0;
    virtual void layDownSticks(const Philosopher&) = 0;
    virtual bool waitFor(const std::chrono::milliseconds howLong) = 0;
};
