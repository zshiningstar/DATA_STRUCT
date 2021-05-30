#include <iostream>
using std::cout;
using std::endl;
class A
{
public:
    int a,b;
    A() {}
};

class B : public A
{
public:
    B() { a = b = 5;}
    
    void show()
    {
        for(int i=0;i<a;i++)
            std::cout << "hello!" << std::endl;
    }
    
};

int main()
{
    B b;
    b.show();
    std::cout << b.a << std::endl;
    return 0;
}
