/*
10. Implement a Memory Pool
Question:
Create a memory pool allocator that preallocates memory and efficiently reuses freed blocks.
Follow-ups:
How does this differ from malloc/free or new/delete?
Can you modify the allocator to support different object sizes?
What trade-offs exist between fragmentation and performance?
*/

#include <iostream>
#include <list>

using namespace std;

struct Data{
    int a;
    double b;
    char c;
    long d;
};

template <typename T>
class MemoryAllocator{
    public:
        MemoryAllocator(size_t size): pool_size{size}{
            memory_pool = static_cast<T*>(malloc(sizeof(T) * pool_size));

            if (!memory_pool) {
                throw bad_alloc();
            }

            for(size_t i = 0; i < size; ++i){
                free_list.push_front(memory_pool + i);
            }
        }

        T* allocate(){
            if(free_list.empty()){
                throw runtime_error("Memory pool out of memory blocks");
            }
            T* block = free_list.front();
            free_list.pop_front();
            new (block) T();
            return block;
        }

        void deallocate(T* block){
            if(!block){
                throw invalid_argument("Cannot deallocate a null pointer.");
            }
            if(block < memory_pool || block > memory_pool + pool_size){
                throw out_of_range("Pointer does not belong to the memory pool.");
            }

            block->~T();
            free_list.push_front(block);
        }

        ~MemoryAllocator(){
            free(memory_pool);
        }

        bool isFull(){
            return free_list.empty();
        }



    private:
        T* memory_pool;
        list<T*> free_list;
        size_t pool_size;

};


int main(){
    MemoryAllocator<Data> ma(5);
}

