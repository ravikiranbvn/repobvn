//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#include "BarberShop.hpp"

BarberShop::BarberShop(const std::uint8_t max_chairs): 
            mNoCustomers(0),
            mBarberOpened{false}, 
            mCustomerAvailable{false},
            mHairCutDone{false},
            mClosed{false},
            mMaxChairs(max_chairs) {}

BarberShop::~BarberShop() {
    isShopClosed();
}

void BarberShop::setShopOpened() {
    std::lock_guard<std::mutex> lk(mMutex);
    mBarberOpened = true;
}

void BarberShop::setCustAvailable() {
    std::lock_guard<std::mutex> lk(mMutex);
    mCustomerAvailable = true;
}

void BarberShop::setHairCutDone() {
    std::lock_guard<std::mutex> lk(mMutex);
    mHairCutDone = true;
}

void BarberShop::resetHairCutDone() {
    std::lock_guard<std::mutex> lk(mMutex);
    mHairCutDone = false;
}

// to notify customer
void BarberShop::waitTillShopOpened() {
    std::unique_lock<std::mutex> lk(mMutex);
    mCvCustomer.wait(lk, [&]{return mBarberOpened;});
}

void BarberShop::customerNotify() {
    std::unique_lock<std::mutex> lk(mMutex);
    mCvCustomer.notify_one();
}

// to notify barber
void BarberShop::waitTillCustomerAvailable() {
    std::unique_lock<std::mutex> lk(mMutex);
    mCvBarber.wait(lk, [&]{return mCustomerAvailable;});
}

void BarberShop::waitTillCustomerDP() {
    std::unique_lock<std::mutex> lk(mMutex);
    mCvBarber.wait(lk, [&]{return !mQueue.empty();});
}

void BarberShop::waitTillHairCutDone() {
    std::unique_lock<std::mutex> lk(mMutex);
    mCvCustomer.wait(lk, [&]{return mHairCutDone;});
}

void BarberShop::barberNotify() {
    std::unique_lock<std::mutex> lk(mMutex);
    mCvBarber.notify_one();
}

void BarberShop::barberNotifyAll() {
    mCvBarber.notify_all();
}

void BarberShop::customerNotifyAll() {
    mCvCustomer.notify_all();
}

// add customer to queue
bool BarberShop::addCustomer(const std::string& name) {
    std::atomic<bool> status{false};
    {
        std::lock_guard<std::mutex> lk(mMutex);
        if(mNoCustomers < mMaxChairs) {
            mQueue.push(name);
            mNoCustomers++;
            status = true;
        }
    }
    
    return status;
}

// remove customer from queue
void BarberShop::removeCustomer() {
    {
        std::lock_guard<std::mutex> lk(mMutex);
        mQueue.pop();
        mNoCustomers--;
    }
}

std::string BarberShop::getNxtCustomer() {
    std::lock_guard<std::mutex> lk(mMutex);
    return mQueue.front();
}

// status check -> if shop is closed
bool BarberShop::isShopClosed() {
    std::lock_guard<std::mutex> lk(mMutex);
    if(mQueue.empty()) { 
        mHairCutDone = true;
        mBarberOpened = true;
        mCustomerAvailable = true;
        mClosed = true;

        barberNotifyAll();
        customerNotifyAll();
    }

    return mClosed;
}