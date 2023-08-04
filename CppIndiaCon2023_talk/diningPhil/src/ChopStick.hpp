//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once 

class ChopStick {
public:
    ChopStick(): mId{-1}, mbIsUsed{false} {}
    explicit ChopStick(const int id): mId{id}, mbIsUsed{false} {}
    ~ChopStick() {}

    ChopStick(const ChopStick&) = default;
    ChopStick(ChopStick&&) = default;
    ChopStick& operator=(const ChopStick& other) = default;
    ChopStick& operator=(ChopStick&& other) = default;

    bool isFree() { 
        return !mbIsUsed;
    }
 
    void pickUp() {
        mbIsUsed = true;
    }

    void layDown() {
        mbIsUsed = false;
    }
private:
    bool       mbIsUsed;
    const int  mId;
};