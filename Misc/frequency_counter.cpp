#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

template<typename T>
using pt = pair<int, T>;

template<typename T>
struct Compare{
    bool operator()(pt<T> a, pt<T> b){return a.first > b.first;};
};

template <typename T>
class FrequencyCounter{
    public:
        FrequencyCounter() = default;
        void insert(const T& value){
            um[value]++;
        }

        std::vector<T> getTopK(int k){

            priority_queue<pt<T>, vector<pt<T>>, Compare<T>> pq;
            
            for(auto& x : um){
                pq.push({x.second, x.first});
                if(pq.size() > k){
                    pq.pop();
                }
            }
            vector<T> k_values;
            while(!pq.empty()){
                k_values.push_back(pq.top().second);
                pq.pop();
            }

            reverse(k_values.begin(), k_values.end());
            return k_values;
        }

        int getFrequency(const T& value) const {
            if(um.find(value) != um.end()){
                return um[value];
            }
            return -1;
        }

        void remove(const T& value){
            um.erase(value);
        }

    private:
        unordered_map<T, int> um;
        
};

int main(){
    return 0;
}