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
#include <cstring>

using namespace std;

class OptString{

    public:

        OptString(){
                _string = new char[1]{'\0'};
        }

        OptString(const char* s){
            cout << "Constructor" << endl;
            if(s == nullptr){
                _string = new char[1]{'\0'};
                size = 0;
            }
            else{
                size = strlen(s);

                _string = new char[size + 1];
                strcpy(_string, s);
            }
        }

        OptString(const OptString& s){
            cout << "Copy Constructor" << endl;

            _string = new char[s.size + 1];
            size = s.size;

            strcpy(_string, s._string);

            return;
        }
        
        OptString& operator=(const OptString& s){
            cout << "Copy Assignment" << endl;
            if(this == &s){
                return *this;
            }

            delete[] _string;

            _string = new char[s.size + 1];
            size = s.size;

            strcpy(_string, s._string);

            return *this;
        }
        
        OptString(OptString&& s){
            cout << "Move Constructor" << endl;

            _string = s._string;
            size = s.size;
            s.size = 0;
            s._string = nullptr;
            return;
        }
        
        OptString& operator=(OptString&& s){
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
        
        ~OptString(){
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
    OptString A("Hello");
    OptString B(A);
    A.print();
    B.print();
    cout << A.getSize() << endl;
    cout << B.getSize() << endl;

    OptString C(std::move(A));
    A.print();
    C.print();
    cout << A.getSize() << endl;
    cout << C.getSize() << endl;

    OptString D;
    D = C;
    C.print();
    D.print();
    cout << C.getSize() << endl;
    cout << D.getSize() << endl;

    OptString E;
    E = std::move(D);
    D.print();
    E.print();
    cout << D.getSize() << endl;
    cout << E.getSize() << endl;

    return 0;
}
