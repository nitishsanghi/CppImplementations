#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache{
    public:
        LRUCache(size_t capacity) : capacity{capacity}{}
        
        int get(int key){
            if(cachemap.find(key) == cachemap.end())
                return -1;
            
            auto nodeIterator = cachemap[key];
            auto value = nodeIterator->second;

            cachelist.splice(cachelist.begin(), cachelist, nodeIterator);
            return value;
        }

        void put(int key, int value){
            if(cachemap.find(key) != cachemap.end()){
                auto nodeIterator = cachemap[key];
                nodeIterator->second = value;
                cachelist.splice(cachelist.begin(), cachelist, nodeIterator);
                return;
            }

            if(cachelist.size() == capacity){
                auto backNode = cachelist.back();
                cachemap.erase(backNode.first);
                cachelist.pop_back();
            }

            cachelist.push_front({key, value});
            cachemap.insert({key,cachelist.begin()});

        }


    private:
        std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cachemap;
        std::list<std::pair<int, int>> cachelist;
        size_t capacity;
};

int main(){

    return 0;
}