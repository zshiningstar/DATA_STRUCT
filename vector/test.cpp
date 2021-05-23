#include "vector_star.h"
#include<iostream>
using namespace std;


int main()
{
    Vector<int> test(20,10,0);
//    int a = 3;
//    int b = 4;
//    swap(a, b);
    test[0] = 4;
    test[1] = 6;
    test[2] = 3;
    test[3] = 2;
    test[4] = 1;
//    std::cout << a << "\t" << b << std::endl;
//    std::cout << test.size() << std::endl;    
    test.sort(0,test.size());
    test.remove(0,test.size());
    std::cout << test.size() << std::endl; 
    for(int i = 0;i<test.size();i++)
        std::cout << test[i] << std::endl;
//    std::cout << "hello!" << std::endl;
    return 0;
}
