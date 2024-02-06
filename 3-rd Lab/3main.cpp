#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* str;
    int length;

public:
    MyString(const char* s = "") {
        length = std::strlen(s);
        str = new char[length + 1];
        std::strcpy(str, s);
    }

    MyString(const MyString& other) {
        length = other.length;
        str = new char[length + 1];
        std::strcpy(str, other.str);
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            std::strcpy(str, other.str);
        }
        return *this;
    }

    ~MyString() {
        delete[] str;
    }

    void display() {
        cout << str << endl;
    }
};

int main() {
    MyString str1("Hello");
    MyString str2 = str1;
    MyString str3;
    str3 = str1;

    cout << "str1: ";
    str1.display();
    cout << "str2: ";
    str2.display();
    cout << "str3: ";
    str3.display();

    return 0;
}