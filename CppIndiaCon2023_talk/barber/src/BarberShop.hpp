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
#include "AsyncOut.hpp"

class BarberShop
{
    public:
        BarberShop(const std::uint8_t max_chairs);
        ~BarberShop();

        BarberShop(const BarberShop&) = delete;
        BarberShop(BarberShop&&) = delete;
        BarberShop& operator=(const BarberShop& other) = delete;
        BarberShop& operator=(BarberShop&& other) = delete;

        void waitTillShopOpened();
        void setShopOpened();
        void barberNotify();
        void barberNotifyAll();
        void customerNotify();
        void customerNotifyAll();
        void waitTillCustomerAvailable();
        void waitTillCustomerDP();
        void waitTillHairCutDone();

        void setCustAvailable();
        void setHairCutDone();
        void resetHairCutDone();
        bool addCustomer(const std::string& name);
        void removeCustomer();
        std::string getNxtCustomer();
        bool isShopClosed();

private:
    std::condition_variable     mCvBarber;          // Check for action on barber
    std::condition_variable     mCvCustomer;        // Check for action on customer
    std::atomic<int>            mNoCustomers;       // Number of customers waiting for haircuts
    std::queue<std::string>     mQueue;             // FIFO for customers
    std::mutex                  mMutex;             // 
    
    bool                        mBarberOpened;
    bool                        mCustomerAvailable;
    bool                        mHairCutDone;
    std::atomic<bool>           mClosed;
    const std::uint8_t          mMaxChairs;
};  