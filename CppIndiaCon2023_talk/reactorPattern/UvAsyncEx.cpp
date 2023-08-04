//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

// g++ UvAsyncEx.cpp -o asyncuv -std=c++17 -luv -pthread
// valgrind --leak-check=full --show-leak-kinds=all ./asyncuv_v
// valgrind --tool=helgrind ./asyncuv_v

#include <iostream>
#include <thread>
#include "AsyncOut.hpp"
#include "uv.h"

using namespace std;

class AsyncEx {
public:
    AsyncEx(uv_loop_t* loop): mAsyncHandler(), mLoop(loop) {
        ::uv_async_init(mLoop, &mAsyncHandler, 
        [](uv_async_t *handle) {
            AsyncEx &asyncEx = *(static_cast<AsyncEx *>(handle->data));
            ::uv_walk(asyncEx.mLoop, [](uv_handle_t* handle, void* arg) {
                AsyncOut() << "[AsyncEx]: uv walking all handles" << "\n";
                if (!::uv_is_closing(handle)) {
                    AsyncEx &asyncEx = *(static_cast<AsyncEx *>(handle->data));
                    AsyncOut() << "[AsyncEx]: uv async cb called" << "\n";
                    ::uv_close((uv_handle_t*)&asyncEx.mAsyncHandler, 
                    [](uv_handle_t* handle){
                    AsyncOut() << "[AsyncEx]: uv closed all callbacks" << "\n";
                    });
                }
            }, NULL);
	    });

        mAsyncHandler.data = this;
    }

    ~AsyncEx() {
        mThread.join();
    }

    AsyncEx(const AsyncEx &o) = delete;
    AsyncEx(AsyncEx &&o) = delete;
    AsyncEx& operator=(const AsyncEx &o)  = delete;
    AsyncEx& operator=(AsyncEx &&o) = delete;

    void sendAsyncSignal() {
        mThread = std::thread([&] {
            AsyncOut() << "[AsyncEx]: init shutdown.. " << "\n";
            ::uv_async_send(&mAsyncHandler);
        });
    }
    
private:
    uv_async_t  mAsyncHandler;
    uv_loop_t*  mLoop;
    std::thread mThread;
};

class EventLoop {
public:
    EventLoop(): mThread() {
        int iret = ::uv_loop_init(&mLoop);
        if(iret) {
            AsyncOut() << "[EventLoop]: loop init failed" << "\n";
        }
    }
    ~EventLoop() {
        mThread.join();
        ::uv_loop_close(&mLoop);
    }

    EventLoop(const EventLoop &o) = delete;
    EventLoop(EventLoop &&o) = delete;
    EventLoop& operator=(const EventLoop &o)  = delete;
    EventLoop& operator=(EventLoop &&o) = delete;

    uv_loop_t* getLoop() {
        return &mLoop;
    }

    void run() {
        mThread = std::thread([&] {
          ::uv_run(&mLoop, ::UV_RUN_DEFAULT);
          AsyncOut() << "[EventLoop]: after eventloop" << "\n";
        });
    }
private:
    uv_loop_t  mLoop;
    std::thread mThread;
};

int main() {
    // create
    EventLoop eventLoop;
    AsyncEx asyncEx(eventLoop.getLoop());

    // start eventloopThread
    std::thread eventloopThread = std::thread([&] {
        std::thread::id this_id = std::this_thread::get_id();
        AsyncOut() << "[eventLoopThread]: eventloop thread id: " << this_id << "\n";
        eventLoop.run();
    });

    // start asyncThread
	std::thread asyncThread = std::thread([&] {
        std::thread::id this_id = std::this_thread::get_id();
        AsyncOut() << "[asyncThread]: async thread id: " << this_id << "\n";
        const auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(2000ms);
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        AsyncOut() << "[asyncThread]: async thread slept for:" << elapsed.count() << "\n";
        asyncEx.sendAsyncSignal();
    });

    // join
    asyncThread.join();
    eventloopThread.join();
    
    return 0;
}