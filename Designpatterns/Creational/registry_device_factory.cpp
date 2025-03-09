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

        using DeviceCreator = std::function<std::unique_ptr<Device>()>;

        static std::unique_ptr<Device> createDevice(const std::string& device_type){
            if(device_registry.find(device_type) != device_registry.end()){
                device_registry.find(device_type)->second();
            }
            else{
                throw std::invalid_argument("Unknown device type: " + device_type);
            }
        }

    private:
       static std::unordered_map<std::string, DeviceFactory::DeviceCreator> device_registry;
};

std::unordered_map<std::string, DeviceFactory::DeviceCreator> device_registry = {
    {"Smartphone", [](){return std::make_unique<Smartphone>();}},
    {"Laptop", [](){return std::make_unique<Laptop>();}},
    {"Smartwatch", [](){return std::make_unique<Smartwatch>();}}
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