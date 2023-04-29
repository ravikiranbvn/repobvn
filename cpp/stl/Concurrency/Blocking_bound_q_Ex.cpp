// Blocking bounded queue with no errors

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

template <typename T>
class blocking_bounded_queue {
public:
    blocking_bounded_queue(size_t max_size = 100):
        max_size(max_size)
    {}

    ~blocking_bounded_queue(){
        take_var.notify_all();
    }

    bool add(T const& e) {
        std::unique_lock<std::mutex> lg(mutex);
        
        if(isQsizeInlimit())
        {
            queue.push(e);
            take_var.notify_one();
            cout << "q added with = " << e << " size= " << queue.size() << "\n";
        }
        else
           return false;
        
        return true;
    }

    T take() {
        std::unique_lock<std::mutex> lg(mutex);
        take_var.wait(lg, [&] () -> bool { return !queue.empty();});
        auto out = std::move(queue.front()); queue.pop();
        return { std::move(out) };
    }
    
    bool isEmpty() {
        return queue.empty();
    }
    
    bool isQsizeInlimit() {
        return queue.size() < max_size;
    }


private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable take_var; 
    size_t max_size;
};

int main() {
    using namespace std::chrono_literals;
    blocking_bounded_queue<int> queue;
    auto producer = [] (blocking_bounded_queue<int>& queue) {
        for (int i = 0; i < 100; ++i) {
            if(!queue.add(i))
                break;
        }
    };

    auto consumer = [] (blocking_bounded_queue<int>& queue) {
        while (!queue.isEmpty()) {
            auto elem = queue.take();
            std::cout << "q popped =" << elem << '\n';
            std::this_thread::sleep_for(100ms);
        }
    };

    std::thread t1(producer, std::ref(queue));
    std::thread t2(consumer, std::ref(queue));
    std::thread t3(consumer, std::ref(queue));

    t1.join();
    t2.join();
    t3.join();
}
