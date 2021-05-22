#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stack_star.h"
using namespace std;

int main ()
{
    string num[] = {"first","second","third","forth","fifth","sixth","seventh","eighth","ninth","tenth"};
    int first,second,third,forth,fifth,sixth,sevecth,eighth,ninth,tenth,twenty;
    int nums[] = {first,second,third,forth,fifth,sixth,sevecth,eighth,ninth,tenth};
//    int stacksize = nums.size();
//    cout << "Please input the size of stack: " << std::endl;
//    cin >> stacksize;
    Stack<int> test(10);
    for(int i=0;i<10;i++)
    {   
        printf("Please input the %s num:",num[i].c_str());
        cin >> nums[i];
    }
    test.push(first);
    test.push(second);
    test.push(third);
    std::cout << test.pop() << std::endl;
    std::cout << test.size() << std::endl;
    return 0;
}   
