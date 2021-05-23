#ifndef _STACK_H
#define _STACK_H

#include "../vector/vector_star.h"

template <typename T>
class Stack : public Vector<T>
{
public:
    void push(T const& e)
    {
        insert(this->size(), e);//入栈，等效为在向量的末尾加入元素
    }
    T pop()
    {
        return remove (this->size() - 1);//出栈，等效为删除向量的末元素
    }
    T& top()
    {
        return (*this) [this->size() - 1];//直接返回向量的末元素
    }
};

#endif
