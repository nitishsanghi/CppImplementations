#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

class Device{
    public:
        virtual void showDetails() = 0;
    private:

};

class Smartphone : public Device{
    public:
        void showDetails(){
            std::cout << "Smartphone 5 mp" << std::endl;
        }
};

class Laptop : public Device{
    public:
        void showDetails(){
            std::cout << "Laptop Xeon processor" << std::endl;
        }
};

class Smartwatch : public Device{
    public:
        void showDetails(){
            std::cout << "Smartwatch Heart rate tracker" << std::endl;
        }
};

class DeviceFactory{
    public:
        static Device* createDevice(const std::string& device_type){
            if(device_type == "Smartphone"){
                Device* device =  new Smartphone();
                return device;
            }
            else if(device_type == "Laptop"){
                Device* device =  new Laptop();
                return device;
            }
            else {   
                Device* device =  new Smartwatch();
                return device;
            }
        }

    private:
        //std::unordered_map<std::string, std::function<void()>> device_map;
};


int main(){
    DeviceFactory df;
    auto a = df.createDevice("Smartphone");
    auto b = df.createDevice("Laptop");
    auto c = df.createDevice("Smartwatch");

    a->showDetails();
    b->showDetails();
    c->showDetails();


    return 0;
}