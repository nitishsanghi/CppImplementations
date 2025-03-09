#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;

class ThreadPoolBasic{
    public:
        ThreadPoolBasic(int n_threads){
            for(int i = 0; i < n_threads; ++i){
                nThreads.emplace_back(std::thread([this]{thread_loop();}));
            }
        }

        void shutdown(){
            std::unique_lock<mutex> lock(m);
            stopFlag = true;
            cv.notify_all();
        }

        void enqueue(function<void()> task){
            unique_lock<mutex> lock(m);
            if(stopFlag)
                return;
            tasks.push(std::move(task));
            cv.notify_one();
        }

        ~ThreadPoolBasic(){
            for(auto& thread : nThreads){
                thread.join();
            }
        }


    private:
        vector<thread> nThreads;
        queue<function<void()>> tasks;
        bool stopFlag{false};
        mutex m;
        condition_variable cv;

    void thread_loop(){
        while(true){
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&](){return !tasks.empty() || stopFlag;});

            if(stopFlag && tasks.empty()){
                return;
            }
            function<void()> task = std::move(tasks.front());
            tasks.pop();
            lock.unlock();
            task();
        }
}

};

int main(){
    
    ThreadPoolBasic pool(18);
    for(int i = 0; i < 100; ++i){
            pool.enqueue([=](){ std::cout << "Task running: " << i << endl; });
    }

    pool.shutdown();

    return 0;
}