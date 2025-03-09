#include <iostream>
#include <string>
#include <thread>
#include <mutex>

class SingletonLogger{
    public:

        static SingletonLogger& getInstance(){
            static SingletonLogger logger;
            return logger;
        }

        void log(const std::string& message){
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << message << std::endl;
        }

        SingletonLogger(const SingletonLogger& logger) = delete;
        SingletonLogger& operator=(const SingletonLogger& logger) = delete;

    private:
        
        SingletonLogger(){
            std::cout << "First Instantiation" << std::endl;
        }
        ~SingletonLogger() = default;
        std::mutex mtx;

};


void A(){
    auto& logger = SingletonLogger::getInstance();
    std::stringstream ss;
    ss << std::this_thread::get_id();
    logger.log("I am A " + ss.str());
    logger.log("A");
}

void B(){
    auto& logger = SingletonLogger::getInstance();
    std::stringstream ss;
    ss << std::this_thread::get_id();
    logger.log("I am B " + ss.str());
    logger.log("B");
}

void C(){
    auto& logger = SingletonLogger::getInstance();
    std::stringstream ss;
    ss << std::this_thread::get_id();
    logger.log("I am C " + ss.str());
    logger.log("C");
}


int main(){

    std::thread t1(A);
    std::thread t2(B);
    std::thread t3(C);
    
    A();
    B();
    C();
    
    t1.join();
    t2.join();
    t3.join();

    return 0;
}