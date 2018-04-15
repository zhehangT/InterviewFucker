/**
* Author: T_Zhehang
* Date: 18-3-26
*/

#include <iostream>
#include <string>

using namespace std;

class B{

};

class A{
public:

    A(string ss):i_const(5), b(), s(ss){
        cout << "Constructor" << endl;
    };

    A(const A& a): i_const(0), b(), s(a.s){
        cout << "Copy Constructor" << endl;
    }

    //常量变量必须在初始化列表里初始化
    const int i_const;
    int i;
    const B b;
    string& s;

    int f(){
        cout << "f()" << endl;
        return i_const;
    }

    int f_const() const{
        cout << "f_const()" << endl;
        return i;
    }

    int f_noconst() {
        cout << "f_noconst()" << endl;
        return 1;
    }

    int f() const {
        cout << "f() const" << endl;
        return 1;
    }
};


int main(){

    A a("s");
    cout << a.f() << endl;
    a.f_const();

    //常量对象，类必须要有显示的构造函数
    const A a2 = a;
    a2.f();
    //常量对象不能调用非常量成员函数
    //a2.f_noconst();
}