//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#include "Barber.hpp"

Barber::Barber(BarberShop& shop):
        mState(BARBER_POSITION::SLEEPING),
        mBShop(shop),
        mThread(&Barber::run, this) {}

Barber::~Barber() {
    close();
    AsyncOut() << " ###"  << "[Barber]:  deleted" << "###" << "\n";
}

void Barber::close() {
    std::lock_guard<std::mutex> lk(mMutex);
    if(mThread.joinable()) {
        mThread.join();
    }
}

int Barber::genRandNo(int min, int max) {
    std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min,max)(rnd);
}

void Barber::sleeping() {
    std::lock_guard<std::mutex> lk(mMutex);
    if(mState == BARBER_POSITION::SLEEPING) {
        AsyncOut() << " [Barber]: sleeping" << "\n";
        mBShop.waitTillCustomerAvailable();
        mState = BARBER_POSITION::CHECKING;
    }
}

void Barber::check() {  
    std::lock_guard<std::mutex> lk(mMutex);
    if(mState == BARBER_POSITION::CHECKING){
        AsyncOut() << "\t\t\t" << " [Barber]: checking" << "\n";
        mBShop.waitTillCustomerDP();
        mState = BARBER_POSITION::BUSY;
    }
}

void Barber::doHaircut() {
    std::lock_guard<std::mutex> lk(mMutex);
    if(mState == BARBER_POSITION::BUSY) {
        mState = BARBER_POSITION::FINISHED;
        int duration = genRandNo(100, 500);
        AsyncOut() <<"\t\t\t" << " [Barber]: cutting hair.. for " << mBShop.getNxtCustomer() << " time: " << duration << "ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }
}

void Barber::finished() {
    {
        std::lock_guard<std::mutex> lk(mMutex);
        if(mState == BARBER_POSITION::FINISHED) {
            mBShop.setHairCutDone();
            mBShop.removeCustomer();
            mState = BARBER_POSITION::CHECKING;
        }
    }

    mBShop.customerNotify();    
}

void Barber::run() {
    // set shop opened
    mBShop.setShopOpened();

    // notify customer
    mBShop.customerNotify();

    while (true) {    
        sleeping();
        check();
        doHaircut();
        finished();
                
        // check if shop is closed
        if(mBShop.isShopClosed()) {
            break;
        }
    }
}