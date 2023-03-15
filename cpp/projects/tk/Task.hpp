#pragma once 

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <pthread.h>
#include <stdexcept>

using namespace std::chrono_literals;
using namespace std;

static const uint8_t prioLowest      = 1U;
static const uint8_t prioBelowNormal = 16U;
static const uint8_t prioNormal      = 32U;
static const uint8_t prioAboveNormal = 66U;
static const uint8_t prioHighest     = 99U;

constexpr float DEFAULT_THREAD_PRIORITY = float(0.5);

class Task {
public:
    Task();
    void run();
    Task(const Task &) = delete;
    virtual ~Task();
    void configure();
    void startWithPriority(int priority, const std::function<void()> job);
    void stop();
    void set_thread_name(std::thread* thread, const std::string& name);
    bool set_thread_priority_safe(
    float priority = DEFAULT_THREAD_PRIORITY, bool realtime = true);

private:
    std::function<void()> m_execute;
    std::thread           m_thread;
};
