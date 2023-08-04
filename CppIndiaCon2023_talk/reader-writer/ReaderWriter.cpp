//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

// valgrind --leak-check=full --show-leak-kinds=all ./rw_v
// valgrind --tool=helgrind ./rw_v

#include <iostream>
#include <array>
#include <random>
#include <future>
#include <shared_mutex>
#include <chrono>
#include <algorithm>
#include <random>
#include <atomic>
#include "AsyncOut.hpp"

using namespace std;
static constexpr std::uint8_t MAX_READERS     = 30;
static constexpr std::uint8_t MAX_WRITERS     = 5;
static constexpr std::uint8_t MAX_ELEMENTS_DB = 100;

std::atomic<bool> shutdownFlag(false);
static std::mutex rdMutex;

static int64_t genRandomNo(int64_t min, int64_t max) {
    std::unique_lock<std::mutex> lk(rdMutex);
    static std::random_device r;
    static std::default_random_engine e1(r());
    std::uniform_int_distribution<int64_t> uniform_dist(min, max);
    return uniform_dist(e1);
}

class DB {
public:
    DB() {
        mDataColl.reserve(MAX_ELEMENTS_DB);
    }
    ~DB() {
    }

    void read() const {
        /* multiple threads can call this function simultaneously
        * no writing access allowed when lk is acquired */
        while (!shutdownFlag) {
            {
                std::shared_lock<std::shared_mutex> lk(mMutex);

                // is DB empty ? 
                if (mDataColl.empty()) {
                    return;
                }

                auto sz = mDataColl.size();
                for (size_t index = 0; index != sz;  ++index) {
                    AsyncOut() << "[DB]: read data from DB:" << mDataColl.at(index) << " at index:" << index << "\n";
                }
            }
        }
    }

    void write(int64_t value) {
        while (!shutdownFlag) {
            {
                /* exclusive access to vector guaranteed */
                std::unique_lock<std::shared_mutex> lk(mMutex);
                mDataColl.emplace_back(value);
                AsyncOut() << "[DB]: added to DB:" << value << "\n";
            }
        }
    }

private:
    mutable std::shared_mutex                    mMutex;
    std::vector<int64_t>                         mDataColl;
};

int main() {
    DB db;

    auto writer = [](DB& db) {
        AsyncOut() << "###" << "[main]: started writing by id:" << std::this_thread::get_id() << "###" << "\n";
        db.write(genRandomNo(1, 1000));
        AsyncOut() << "###" << "[main]: ended writing by id:" << std::this_thread::get_id() << "###" << "\n";
    };

    auto reader = [](DB& db) {
        AsyncOut() << "###" << "[main]: started reading by id:" << std::this_thread::get_id() << "###" << "\n";
        db.read();
        AsyncOut() << "###" << "[main]: ended reading by id:" << std::this_thread::get_id() << "###" << "\n";
    };

    // writing
    std::vector<std::future<void>> thWwriters;
    for (size_t i = 0; i < MAX_WRITERS; i++) {
        thWwriters.emplace_back(std::async(std::launch::async, writer, std::ref(db)));
    }

    // reading
    std::vector<std::future<void>> thReaders;
    for (size_t i = 0; i < MAX_READERS; i++) {
        thReaders.emplace_back(std::async(std::launch::async, reader, std::ref(db)));
    }

    // Set the shutdownFlag to signal the threads to stop
    bool expected = false;
    if(shutdownFlag.compare_exchange_strong(expected, true)) {
        AsyncOut() << "[main]: shutting down.." << "\n";
    }

    // Wait for reader and writer threads to finish
    for (auto& readerThread : thReaders) {
        readerThread.wait();
    }

    for (auto& writerThread : thWwriters) {
        writerThread.wait();
    }

    return 0;
}