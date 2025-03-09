/*
Implement a Custom String Class
Question:
Write a custom String class that supports dynamic memory allocation and implements copy, move, and assignment operators.
Follow-ups:
Optimize it using SSO (Small String Optimization).
Compare std::string vs a custom implementation.
Implement regular expression support.
*/

#include <iostream>

using namespace std;

class BasicString{

    public:

        BasicString(){
                _string = new char[1]{'\0'};
        }

        BasicString(const char* s){
            cout << "Constructor" << endl;
            if(s == nullptr){
                _string = new char[1]{'\0'};
                size = 0;
            }
            else{
                while(s[size] != '\0'){
                    ++size;
                }
                _string = new char[size + 1];
                int i = 0;
                while(s[i] != '\0'){
                    _string[i] = s[i];
                    ++i;
                }
                _string[i] = '\0';
            }
        }

        BasicString(const BasicString& s){
            cout << "Copy Constructor" << endl;

            _string = new char[s.size + 1];
            size = s.size;

            int i = 0;
            while(s._string[i] != '\0'){
                _string[i] = s._string[i];
                ++i;
            }

            _string[i] = '\0';
            return;
        }
        
        BasicString& operator=(const BasicString& s){
            cout << "Copy Assignment" << endl;
            if(this == &s){
                return *this;
            }

            delete[] _string;

            _string = new char[s.size + 1];
            size = s.size;
            int i = 0;
            while(s._string[i] != '\0'){
                _string[i] = s._string[i];
                ++i;
            }
            _string[i] = '\0';
            return *this;
        }
        
        BasicString(BasicString&& s){
            cout << "Move Constructor" << endl;

            _string = s._string;
            size = s.size;
            s.size = 0;
            s._string = nullptr;
            return;
        }
        
        BasicString& operator=(BasicString&& s){
            cout << "Move Assignment" << endl;
            if(this == &s){
                return *this;
            }
            delete[] _string;

            _string = s._string;
            size = s.size;
            s.size = 0;
            s._string = nullptr;
            return *this;
        }
        
        ~BasicString(){
            delete[] _string;
            size = 0;
        }

        void print() const {
            if(_string != nullptr)
                cout << _string << endl;
            else
                cout << "Empty" << endl;
        }

        std::size_t getSize() const {
            return size;
        }

    private:
        char* _string{nullptr};
        std::size_t size{0};

};

int main(){
    BasicString A("Hello");
    BasicString B(A);
    A.print();
    B.print();
    cout << A.getSize() << endl;
    cout << B.getSize() << endl;

    BasicString C(std::move(A));
    A.print();
    C.print();
    cout << A.getSize() << endl;
    cout << C.getSize() << endl;

    BasicString D;
    D = C;
    C.print();
    D.print();
    cout << C.getSize() << endl;
    cout << D.getSize() << endl;

    BasicString E;
    E = std::move(D);
    D.print();
    E.print();
    cout << D.getSize() << endl;
    cout << E.getSize() << endl;

    return 0;
}
