//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once 

#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include "BarberShop.hpp"

class Customer {
public:
    Customer(const std::string& name, BarberShop& shop);
    ~Customer();

    Customer(const Customer&) = delete;
    Customer(BarberShop&&) = delete;
    Customer& operator=(const Customer& other) = delete;
    Customer& operator=(Customer&& other) = delete;
    
private:
    void close();
    void run();
    bool tryHairCut();

    // Member variables
    std::string        mName;
    BarberShop&        mBShop;
    std::mutex         mMutex;
    std::thread        mThread;
};