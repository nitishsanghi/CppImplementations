#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>




template <typename T>
class BasicSparseMatrix{
    
    struct Element{
        size_t row;
        size_t col;
        T value;
    };

    public:
        BasicSparseMatrix(size_t rows, size_t cols) : num_rows{rows}, num_cols{cols}{}
        
        void setValue(size_t row, size_t col, T value){
            try{
                if(row < num_rows && row >= 0 && col < num_cols && col >= 0)
                    values.emplace_back(Element{row, col, value});
                else
                    throw std::invalid_argument("Check matrix dimension range");
            }
            catch (std::exception& e){
                std::cout << e.what() << std::endl;
            }

            std::sort(values.begin(), values.end(), compare);

        }

        void print(){
            for(auto& value : values){
                std::cout << value.row << " " << value.col << " " << value.value << std::endl;
            }
        }

        std::function<bool(Element, Element)> compare = [](Element a, Element b){
            if(a.row == b.row)
                return a.col < b.col;
            return a.row < b.row;};

    private:
        std::vector<Element> values;
        size_t num_rows;
        size_t num_cols;

};


int main(){

    BasicSparseMatrix<int> bsm_int(10,100);
    bsm_int.setValue(1,67,10);
    bsm_int.setValue(3,31,1);
    bsm_int.setValue(7,67,10);
    bsm_int.setValue(2,51,1);
    bsm_int.setValue(9,67,10);
    bsm_int.setValue(1,34,10);;
    bsm_int.setValue(11,42,87);
    bsm_int.setValue(9,51,1);
    bsm_int.setValue(2,11,1);
    bsm_int.print();
    return 0;
}