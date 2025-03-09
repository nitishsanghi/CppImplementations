#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

class Device{
    public:
        virtual void showDetails() = 0;
        virtual ~Device() = default;
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
        static std::unique_ptr<Device> createDevice(const std::string& device_type){
            if(device_type == "Smartphone"){
                std::unique_ptr<Device> device =  std::make_unique<Smartphone>();
                return device;
            }
            else if(device_type == "Laptop"){
                std::unique_ptr<Device> device =  std::make_unique<Laptop>();
                return device;
            }
            else if(device_type == "Smartwatch"){   
                std::unique_ptr<Device> device =  std::make_unique<Smartwatch>();
                return device;
            }
            else{
                throw std::invalid_argument("Unknown device type: " + device_type);
            }
        }

    private:
        //std::unordered_map<std::string, std::function<void()>> device_map;
};

int main(){
    auto a = DeviceFactory::createDevice("Smartphone");
    auto b = DeviceFactory::createDevice("Laptop");
    auto c = DeviceFactory::createDevice("Smartwatch");

    a->showDetails();
    b->showDetails();
    c->showDetails();

    return 0;
}