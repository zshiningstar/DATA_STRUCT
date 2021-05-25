/*************************************
 对已知向量进行操作
*************************************/

#ifndef _VECTOR_STAR_H
#define _VECTOR_STAR_H

#include <stdlib.h>
#include<iostream>
#define DEFAULT_CAPACITY 10
using namespace std;

typedef int Rank;

template <typename T>
class Vector
{
protected:
    Rank _size;
    int _capacity;
    T* _item;
    
protected:
    void copyfrom(T const* A, Rank lo, Rank hi);//复制数组区间A[lo,hi]
    void expend();//扩容
    void shrink();//装填因子过小时压缩
    Rank max(Rank lo, Rank hi);//取最大
    //Rank partition(Rank lo, Rank hi);//轴点构造算法
    bool bubble(Rank lo, Rank hi);//扫描交换
    void bubbleSort(Rank lo, Rank hi);//冒泡排序
    //void selectionSort(Rank lo, Rank hi);//选择排序
    void merge(Rank lo, Rank mi, Rank hi);//归并算法
    void mergeSort(Rank lo, Rank hi);//归并排序
    void quickSort(Rank lo, Rank hi);//快速排序
    void heapSort(Rank lo, Rank hi);//堆排序
    
    static Rank binSearch(T* A, T const& e, Rank lo, Rank hi);
public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量为C，大小为S，所有元素均为V 形参具有默认值，则不传实参时，默认使用这个值，因此此类不需要定义默认构造函数;
    {
        if(c<s)
        {
            std::cerr << "The vector size must be less than capacity" << std::endl;
            std::cerr << "The first parameter is the vector capacity" << std::endl;
            return;
        }
        _item = new T [_capacity = c];
        for(_size=0;_size<s;_item[_size++]=v);
    }
    Vector(T const* A, Rank n)//数组整体复制
    {
        copyfrom(A, 0, n);
    }
    Vector(T const* A, Rank lo, Rank hi)//数组区间复制
    {
        copyfrom(A, lo, hi);
    }
    Vector(Vector<T> const& V)//向量整体复制
    {
        copyfrom(V._item,0,V.size());
    }
    Vector(Vector<T> const& V, Rank lo, Rank hi)//向量区间复制
    {
        copyfrom(V._item, lo, hi);
    }
    
    virtual ~Vector() 
    {
        delete [] _item;
    }
    
//only read
public:
    Rank size() const { return _size;}
    bool empty() const { return !_size;}
    int disordered() const;
    
    Rank find(T const& e) const { return find(e,0,_size);}//无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const;//无序向量整体区间查找
    Rank search(T const& e) const//有序向量整体查找
    {
        return((0>=_size) ? -1 : search(e,0,_size));
    }
    Rank search(T const& e, Rank lo, Rank hi) const;
//could write
    T& operator[] (Rank r) const;//重载[]
    Vector<T> & operator= (Vector<T> const& );//重载=使得可以直接克隆向量
    
    T remove(Rank i);
    int remove(Rank lo,Rank hi);
    Rank insert(Rank r, T const& e);
    Rank insert(T const& e) 
    {
        return insert(_size,e);
    }
    void sort(Rank lo, Rank hi);
    void sort()
    {
        sort(0,_size);
    }
    void unsort(Rank lo, Rank hi);
    void unsort()
    {
        unsort(0,_size);
    }
    int deduplicate();
    int uniquify();//有序向量剔除重复元素
    
    void traverse(void(* ) (T& ));
    template <typename VST>
    void traverse(VST& );
};

template <typename T>
void Vector<T>::copyfrom(T const* A, Rank lo, Rank hi)
{
    _item = new T [_capacity = 2 * (hi - lo)];//分配空间
    _size = 0;//大小清零
    while(lo < hi)
        _item[_size++] = A[lo++];//复制到_item[0,hi-lo]
}

template <typename T>
Vector<T> & Vector<T>::operator= (Vector<T> const& V)
{
    if(_item)
        delete [] _item;
    copyfrom(V._item, 0, V.size());
    return *this;
}

template <typename T>
void Vector<T>::expend()
{
    if(_size < _capacity)
        return;
    if(_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T* oldItem = _item;
    _item = new T [_capacity <<= 1];//容量加倍
    for(int i=0;i<_size;i++)
        _item[i] = oldItem[i];
    delete [] oldItem;
}

template <typename T>
void Vector<T>::shrink()
{
    if(_capacity < DEFAULT_CAPACITY << 1)//不致收缩到DEFAULT_CAPACITY以下
        return;
    if((_size << 2) > _capacity)//25%
        return;
    T* oldItem = _item;
    _item = new T [_capacity >>=1];//容量减半
    for(int i=0;i<_size;i++)
        _item[i] = oldItem[i];
    delete [] oldItem;
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _item + lo;
    for(Rank i=hi-lo;i>0;i--)
        swap(V[i-1],V[rand() % i]);
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const//从后向前，失败时，返回lo-1
{
    while((lo < hi--) && (e != _item[hi]));
    return hi;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
    expend();
    for(int i=_size;i>r;i--)
        _item[i] = _item[i-1];//自后向前，后继元素依次后移一个单元
    _item[r] = e;
    _size++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo,Rank hi)
{
    if(lo==hi)
        return 0;
    while(hi < _size)
        _item[lo++] = _item[hi++];
    _size = lo;
    shrink();
    return hi-lo;
}

template <typename T>
T Vector<T>::remove(Rank i)
{
    T e = _item[i];
    remove(i,i+1);
    return e;
}

template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while(i<_size)
        (find(_item[i],0,i) < 0) ? i++ : remove(i);//在前缀中查找一样的，没有则往后查找
    return oldSize - _size;
}

template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for(int i=1;i<_size;i++)
        if(_item[i-1] > _item[i] )//逆序则计数
            n++;
    return n;//n为0时则有序
}

template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0;
    Rank j = 0;
    while(++j < _size)
        if(_item[i]!=_item[j])
            _item[++i] = _item[j];
    _size = ++i;
    shrink();
    return j - i;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
    return binSearch(_item,e,lo,hi);
}

template <typename T>
Rank Vector<T>::binSearch(T* A, T const& e, Rank lo, Rank hi)
{
    while(lo < hi)
    {
        Rank mi = (hi - lo) >> 1;
        (e<A[mi]) ? hi = mi : lo = mi+1;
    }
    return --lo;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while(!bubble(lo, hi--));
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)//从小到大
{
    bool sorted = true;
    while(++lo < hi)
        if(_item[lo - 1] > _item[lo])
        {
            sorted = false;
            swap(_item[lo-1], _item[lo]);
        }
    return sorted;
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi)
{
    bubbleSort(lo, hi);
    return hi;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if(lo < hi - 2)
        return;
    int mi = (lo + hi) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    T* A = _item + lo;//A[0, hi-lo] _item是个指针，加上lo后指针移动到lo处，此时A的大小为hi-lo;_item则为_item[lo, hi]
    int lb = mi - lo;//左子向量大小
    T* B = new T [lb];//用来存放前子向量B[0,lb] = _item[0,mi]
    for(Rank i = 0;i<lb;B[i]=A[i++]);//复制前子向量
    int lc = hi - mi;
    T* C = _item + mi;//后子向量C[mi, hi];
    for(Rank i=0,j=0,k=0;(j<lb) || (k<lc);)
    {
        if((j<lb) && (!(k<lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if((k<lc) && (!(j<lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete [] B;
}

template <typename T>
T& Vector<T>::operator[] (Rank r) const
{
    return _item[r];
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    bubbleSort(lo, hi);
}
 
 
#endif
