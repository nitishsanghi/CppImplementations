#include <iostream>

template <typename T>
class SharedPtr{
    public:
        struct ControlBlock{
            T* object;
            size_t count;
        };

        SharedPtr(T* ptr){
            cb = new ControlBlock();
            cb->object = ptr;
            cb->count = 1;
        }

        SharedPtr(const SharedPtr& ptr){
            std::cout << "Copy Construct" << std::endl;
            cb = ptr.cb;
            cb->count++;
        }

        SharedPtr& operator=(const SharedPtr& ptr){
            std::cout << "Copy Assignment" << std::endl;
            if(this == & ptr){
                return *this;
            }
            if(cb->count == 1){
                delete cb->object;
                delete cb;
            }
            else{
                cb->count--;
            }
            cb = ptr.cb;
            cb->count++;
            return *this;
        }

        SharedPtr(SharedPtr&& ptr){
            std::cout << "Move Construct" << std::endl;
            cb = ptr.cb;
            ptr.cb = nullptr;
        }

        SharedPtr& operator=(SharedPtr&& ptr){
            std::cout << "Move Assignment" << std::endl;
            if(this == & ptr){
                return *this;
            }
            if(cb->count == 1){
                delete cb->object;
                delete cb;
            }
            else{
                cb->count--;
            }

            cb = ptr.cb;
            ptr.cb = nullptr;
            return *this;
        }

        ~SharedPtr(){
            if(cb->count > 1){
                std::cout << "Reducing : " <<  cb->count << std::endl;
                --cb->count;
            }
            else{
                std::cout << "Destroying" << std::endl;
                delete cb->object;
                delete cb;
            }
        }

        void print(){
            std::cout << cb->count << std::endl;
        }

    private:
        ControlBlock* cb;

};

int main(){
    SharedPtr<int> g = new int(10);
    SharedPtr<int> i = new int(10);
    i.print();
    SharedPtr<int> j(i);
    j.print();
    i.print();
    SharedPtr<int> k = j;
    j.print();
    i.print();
    k.print();
    g = i;
    return 0;
}