//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#include "Customer.hpp"

Customer::Customer(const std::string& name, BarberShop& shop):
    mName(name),
    mBShop(shop),
    mThread(&Customer::run, this) {}

Customer::~Customer() {
    close();
    AsyncOut() << " ###" << "[" << mName << "]: " << " deleted" << "###" << "\n";
}

void Customer::close() {
    if(mThread.joinable()) {
        mThread.join();
    }
}

bool Customer::tryHairCut() {
    std::atomic<bool> status{false};
    {
       std::lock_guard<std::mutex> lk(mMutex);
        if(mBShop.addCustomer(mName)) {
            status = true;
        }
    }

    mBShop.barberNotify();      // notify barber
    return status;
}

void Customer::run() {
    while(true) {
        // wait till barber shop is opened
        mBShop.waitTillShopOpened();

        // set customer available
        mBShop.setCustAvailable();

        // reset hair cut done
        mBShop.resetHairCutDone();

        // notify barber
        mBShop.barberNotify();

        // try for hair cut
        if(tryHairCut()) {
            // wait till hair cut is done
            mBShop.waitTillHairCutDone();
            break;
        }
        else {
            AsyncOut() << " ###"  << "[" << mName << "]: " << " left.. waiting room full.." << " ###" << "\n";
            break;
        }
    }    
}