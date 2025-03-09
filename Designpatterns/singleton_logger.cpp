#include <iostream>
#include <string>

class SingletonLogger{
    public:

        static SingletonLogger& getInstance(){
            static SingletonLogger logger;
            return logger;
        }

        void log(const std::string& message){
            std::cout << message << std::endl;
        }

        SingletonLogger(const SingletonLogger& logger) = delete;
        SingletonLogger& operator=(const SingletonLogger& logger) = delete;

    private:
        
        SingletonLogger() = default;
        ~SingletonLogger() = default;


};


void A(){
    auto& logger = SingletonLogger::getInstance();
    logger.log("I am A");
}

void B(){
    auto& logger = SingletonLogger::getInstance();
    logger.log("I am B");
}

void C(){
    auto& logger = SingletonLogger::getInstance();
    logger.log("I am C");
}


int main(){

    A();
    B();
    C();

    return 0;
}