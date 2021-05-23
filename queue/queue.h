#ifndef _QUEUE_H
#define _QUEUE_H

#include "../listnode/listnode_star.h"

template <typename T>
class Queue : public List<T>
{
    void enqueue(T const& e)
    {
        insertAsLast(e);//队尾插入
    }
    T dequeue()
    {
        return remove(first());//出队，首部删除
    }
    T& front()
    {
        return first()->data;//队首
    }
}

#endif
