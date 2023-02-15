// program for blocking queue 
// working with queue closing, condition variables and informing threads 
// Drawback: still there is a time out error

#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <condition_variable>
 
template <typename T>
class blocking_queue {
public:
    bool add(T const& e) {
        std::unique_lock<std::mutex> lg(mutex);
        
        // Fix the program never terminates because consumer 
        // the thread never catches up.
        if(qIsClosed)
          return false;

        queue.push(e);

        // Fix the queue so that the calling thread take blocks 
        // if the queue is empty.
        cv.notify_one();

        return true;
    }
 
    std::pair<bool, T> take() {
        std::unique_lock<std::mutex> lg(mutex);
        
        // Fix the queue so that the calling thread take blocks 
        // if the queue is empty.
        cv.wait(lg, [&] () -> bool { return queue.size() > 0 || qIsClosed; });
        
        // Fix the program never terminates because consumer 
        // the thread never catches up.
        if (queue.size() == 0) {
            return { false, T{} };
        }
        auto out = std::move(queue.front()); queue.pop();
        return { true, std::move(out) };
    }

    // Fix the program never terminates because consumer 
    // the thread never catches up.
    void close()
    {
        std::unique_lock<std::mutex> lg(mutex);
        qIsClosed = true;
        cv.notify_all();
    }
 
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cv;

    // Fix the program never terminates because consumer 
    // the thread never catches up.
    bool qIsClosed = false;
};
 
int main() {
    using namespace std::chrono_literals;
    blocking_queue<int> queue;
    auto producer = [] (blocking_queue<int>& queue) {
        for (int i = 0; i < 100; ++i) {
            queue.add(i);
            std::this_thread::sleep_for(100ms);
        }

        // Fix the program never terminates because consumer 
        // the thread never catches up.
        queue.close();
    };
 
    auto consumer = [] (blocking_queue<int>& queue) {
        while (true) {
            auto elem = queue.take();
            
            // Fix the program never terminates because consumer 
            // the thread never catches up.
            if (!elem.first) {
                break;
            }
            std::cout << elem.second << '\n';
        }
    };
 
    std::thread t1(producer, std::ref(queue));
    std::thread t2(consumer, std::ref(queue));
 
    t1.join();
    t2.join();
}
