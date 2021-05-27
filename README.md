### C++
* toupper() 
    小写转换大写
* isalpha() 
    判断是否是字母字符，是则返回非零值，否则返回零值
* std::cerr 
    cerr对应标准错误流，用于显示错误消息;std::cerr 与 std::cout的最大不同是cerr是不带输出缓冲的，直接就可以输出到显示器上,而 cout是带输出缓冲的,需要刷新缓冲区才能输出。
* exit(EXIT_FAILURE) 
    结束程序（到此位置）·
* i <<= 1
    //i = i<<1  i等于i乘以2的1次方
* swap():
    位于C++头文件#include<iostream> using namespace std;
* release():
    在标准库头文件：memory里面
    1.常用变量
    unique_ptr    //模板类，拥有独有对象所有权语义的智能指针
    shared_ptr    //模板类，拥有共享对象所有权语义的智能指针，不会因为weak_ptr也指向同一个对象而引用计数加1
    weak_ptr    //模板类，由shared_ptr所管理的对象的弱引用，避免循环引用
    auto_ptr    //模板类，C++17中移除
    2.常用操作
    std::make_unique<int>(5);//将5变成独有对象
    unique_ptr::get();//返回指向被管理对象的指针，如果无被管理对象，则为nullptr
    unique_ptr::release();//释放被管理对象的所有权
    unique_ptr::swap(unique_ptr& other);//交换两个被管理对象
    std::make_shared<int>(5);//将5变成共享对象
    shared_ptr::get();//返回指向被管理对象的指针，如果无被管理对象，则为nullptr
    shared_ptr::swap(unique_ptr& other);//交换两个被管理对象
    shared_ptr::use_count();//返回共享对象的引用计数
    weak_ptr::use_count();//返回管理该对象的shared_ptr对象数量，将shared_ptr对象赋给weak_ptr对象，引用计数加一
    weak_ptr::expired();//检查被引用的对象是否已删除 
    weak_ptr::lock();//创建被引用的对象的shared_ptr 
    auto_ptr::get();//返回指向被管理对象的指针，如果无被管理对象，则为nullptr
    **auto_ptr::release()**;//释放被管理对象的所有权

* INT_MAX:
    量INT_MAX和INT_MIN分别表示最大、最小整数，定义在头文件limits.h
