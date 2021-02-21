#include "function.hpp"
#include <iostream>
#include <string>

#define PRINT(msg)       std::cout << (msg)
#define PRINTLN(msg)     PRINT(msg) << std::endl;

void FreeFunction()
{
    PRINTLN("in free function");
}

class Functor1
{
public:
    Functor1(int data) : data(data) {}
    double operator()(int i)
    {
        data += 10;  // modify internal state
        PRINTLN("in functor's overloaded function call operator:");
        return (double)i;
    }
    int GetData() const { return data; }
private:
    int data;
};

class Functor2
{
private:
    typedef void(*PtrToFun)();
    PtrToFun p = []() { PRINTLN("in functor's overloaded type conversion operator to function pointer"); };
public:
    operator PtrToFun()
    {
        return p;
    }
};

int main(int argc, char **argv)
{
    Function<void()> o1 = &FreeFunction;
    Functor1 fun(5);
    Function<double(int)> o2 = fun;
    Function<std::string(const std::string&)> o3 = [](const std::string &s) -> std::string { return std::string("in lambda: ") + s; }; 
    Function<void()> o4 = Functor2();
    
    o1();
    PRINTLN(o2(1));
    PRINTLN(o3("hello!"));
    o4();

    PRINTLN("**************");
    PRINTLN(fun.GetData());  

    const Function<void()> &ff = [o4](){};
    const Function<void()> &ff2 = ff;
    Function<void()> fff = ff2;

    return 0;
}