//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

#pragma once 
#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <thread>
#include "BarberShop.hpp"

class Barber {

enum class BARBER_POSITION {
  SLEEPING=0,    // barber sleeping
  CHECKING=1,    // barber check on waiting customer
  BUSY=2,        // barber busy with haircut
  FINISHED=3     // barber finished haircut
};

public:
  Barber(BarberShop& shop);
  ~Barber();

  Barber(const Barber&) = delete;
  Barber(Barber&&) = delete;
  Barber& operator=(const Barber& other) = delete;
  Barber& operator=(Barber&& other) = delete;

private:
  void run();
  int  genRandNo(int min, int max);
  void sleeping();
  void check();
  void doHaircut();
  void finished();
  void close();

  // Member variables
  BARBER_POSITION          mState;
  BarberShop&              mBShop;
  std::mutex               mMutex;
  std::thread              mThread;
};