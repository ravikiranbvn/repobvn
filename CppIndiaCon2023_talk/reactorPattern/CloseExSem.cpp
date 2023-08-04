//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

// g++ CloseEx.cpp -o closeex -std=c++17 -luv -pthread
// valgrind --leak-check=full --show-leak-kinds=all ./closeexsem_v
// valgrind --tool=helgrind ./closeexsem_v

#include <iostream>
#include <thread>
#include <atomic>
#include <semaphore.h>
#include "AsyncOut.hpp"
#include "uv.h"

using namespace std;
static sem_t    sem_shutdown;
static std::atomic<bool>   mShutdown{false};

class CloseEx {
public:
    CloseEx(uv_loop_t* loop): mLoop(loop), mThread() {}
    ~CloseEx() {
        mThread.join();
    }

    CloseEx(const CloseEx &o) = delete;
    CloseEx(CloseEx &&o) = delete;
    CloseEx& operator=(const CloseEx &o)  = delete;
    CloseEx& operator=(CloseEx &&o) = delete;

    void close() {
    mThread = std::thread([&] {
        AsyncOut() << "[CloseEx]: closing.. " << "\n";
        sem_post(&sem_shutdown);
        });
    }

private:
    uv_loop_t*  mLoop;
    std::thread mThread;
};

class EventLoop {
public:
    EventLoop(uv_loop_t* loop): 
    mLoop(loop),
    mThread() {}

    ~EventLoop() {
        mThread.join();
    }
    
    EventLoop(const EventLoop &o) = delete;
    EventLoop(EventLoop &&o) = delete;
    EventLoop& operator=(const EventLoop &o)  = delete;
    EventLoop& operator=(EventLoop &&o) = delete;

    void run() {
    mThread = std::thread([&] {
        while(!mShutdown) {
                ::uv_run(mLoop, ::UV_RUN_DEFAULT);
            }
            AsyncOut() << "[EventLoop]: eventloop closed" << "\n";
        });
    }

private:
    uv_loop_t*          mLoop;
    std::thread         mThread;
};

int main() {
    // sem init
    sem_init(&sem_shutdown, 0, 0);

    // loop init 
    uv_loop_t loop;
    int iret = ::uv_loop_init(&loop);
    if(iret) {
        AsyncOut() << "[main]: loop init failed" << "\n";
        return -1;
    }

    // create
    EventLoop eventLoop(&loop);
    CloseEx   closeEx(&loop);

    // start eventloopThread
    std::thread evenLoopThread = std::thread([&] {
        std::thread::id this_id = std::this_thread::get_id();
        AsyncOut() << "[eventLoopThread]: evenloop thread id: " << this_id << "\n";
        eventLoop.run();
    });
    
    // start closeThread
	std::thread closeThread = std::thread([&] {
        std::thread::id this_id = std::this_thread::get_id();
        AsyncOut() << "[closeThread]: close thread id: " << this_id << "\n";
        const auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(2000ms);
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        AsyncOut() << "[closeThread]: close thread slept for:" << elapsed.count() << "\n";
        closeEx.close();
    });

    sem_wait(&sem_shutdown);
    bool expected = false;
    if(mShutdown.compare_exchange_strong(expected, true)) {
        AsyncOut() << "[main]: eventloop closing.." << "\n";
    }

    // join
    closeThread.join();
    evenLoopThread.join();

    // loop close
    ::uv_loop_close(&loop);

    // sem destroy
    sem_destroy(&sem_shutdown);

    return 0;
}