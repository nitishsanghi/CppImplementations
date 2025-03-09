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

class SSOString{

    public:

        SSOString(){
            _string_sso[0] = '\0';
            heap_allocation = false;
            size = 0;
        }

        SSOString(const char* s){
            cout << "Constructor" << endl;

            if(s == nullptr){
                _string_sso[0] = '\0';
                heap_allocation = false;
                size = 0;
            }
            else{
                size = strlen(s);
                if(size <= SSO_CAPACITY){
                    strcpy(_string_sso, s);
                    heap_allocation = false;
                }
                else{
                    _string = new char[size + 1];
                    strcpy(_string, s);
                    heap_allocation = true;
                }
            }
        }

        SSOString(const SSOString& s){
            cout << "Copy Constructor" << endl;
            
            heap_allocation = s.heap_allocation;
            size = s.size;

            if(s.size <= SSO_CAPACITY){
                strcpy(_string_sso, s._string_sso);
            }
            else{
                _string = new char[s.size + 1];
                strcpy(_string, s._string);
            }

            return;
        }
        
        SSOString& operator=(const SSOString& s){
            cout << "Copy Assignment" << endl;
            if(this == &s){
                return *this;
            }

            if(heap_allocation){
                delete[] _string;
            }

            size = s.size;

            if(s.size <= SSO_CAPACITY){
                strcpy(_string_sso, s._string_sso);
            }
            else{
                _string = new char[s.size + 1];
                strcpy(_string, s._string);
            }

            return *this;
        }
        
        SSOString(SSOString&& s){
            cout << "Move Constructor" << endl;

            size = s.size;
            heap_allocation = s.heap_allocation;

            if(s.size <= SSO_CAPACITY){
                strcpy(_string_sso, s._string_sso);
            }
            else {
                _string = s._string;
                s._string = nullptr;
            }
   
            s.size = 0;
            s.heap_allocation = false;
            return;
        }
        
        SSOString& operator=(SSOString&& s){
            cout << "Move Assignment" << endl;
            if(this == &s){
                return *this;
            }

            if(heap_allocation){
                delete[] _string;
            }

            size = s.size;
            heap_allocation = s.heap_allocation;

            if(s.size <= SSO_CAPACITY){
                strcpy(_string_sso, s._string_sso);
            }
            else {

                _string = s._string;
                s._string = nullptr;
            }
   
            s.size = 0;
            s.heap_allocation = false;

            return *this;
        }
        
        ~SSOString(){
            if(heap_allocation){
                delete[] _string;
            }
            size = 0;
        }

        void print() const {
            
            if(heap_allocation){
                if(_string != nullptr)
                    cout << _string << endl;
                else
                    cout << "Empty" << endl;
            }
            else{
                cout << _string_sso << endl;
            }
        }

        std::size_t getSize() const {
            return size;
        }

    private:
        static constexpr std::size_t SSO_CAPACITY = 15;
        union{
            char _string_sso[SSO_CAPACITY + 1];
            struct {
                char* _string;
                std::size_t size;
            };
        };
        bool heap_allocation;
};

int main(){
    SSOString A("Hello");
    SSOString B(A);
    A.print();
    B.print();
    cout << A.getSize() << endl;
    cout << B.getSize() << endl;

    SSOString C(std::move(A));
    A.print();
    C.print();
    cout << A.getSize() << endl;
    cout << C.getSize() << endl;

    SSOString D;
    D = C;
    C.print();
    D.print();
    cout << C.getSize() << endl;
    cout << D.getSize() << endl;

    SSOString E;
    E = std::move(D);
    D.print();
    E.print();
    cout << D.getSize() << endl;
    cout << E.getSize() << endl;

    return 0;
}
