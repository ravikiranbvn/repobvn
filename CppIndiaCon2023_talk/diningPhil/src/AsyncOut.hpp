//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once

#include <mutex>
#include <memory>
#include <iostream>

static std::mutex mtx_cout;

class AsyncOut
{
public:
    AsyncOut(): lk(std::unique_lock<std::mutex>(mtx_cout)) {}
    ~AsyncOut(){}

    template<typename T>
    AsyncOut& operator<<(const T& _t){
        std::cout << _t;
        return *this;
    }

    AsyncOut& operator<<(std::ostream& (*fp)(std::ostream&)) {
        std::cout << fp;
        return *this;
    }

private:
    std::unique_lock<std::mutex> lk;
};