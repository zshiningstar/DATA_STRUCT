#ifndef _LISTNODE_STAR_H
#define _LISTNODE_STAR_H

#include <cstdlib>
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode//节点结构体，当一个节点创建后，自动拥有以下内容
{
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;
    
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : 
    data(e), pred(p), succ(s) {}
    
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, pred, this);//创建新的节点x，数据为e，前驱是（p的原前驱），后继为x
    pred->succ = x;//将p原前驱的后继变为x
    pred = x;//将x变为p的前驱
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, this, succ);//创建新的节点x，数据为e，前驱是（p的原前驱），后继为x
    succ->pred = x;//将p原前驱的后继变为x
    succ = x;//将x变为p的前驱
    return x;
}

template <typename T>
class List
{
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;
protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T) p, int n);//复制自列表中自位置P起的n项
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);//对p开始的连续n个节点归并排序
    void selectionSort(ListNodePosi(T), int);//对p开始的连续n个节点选择排序
    void insertionSort(ListNodePosi(T), int);//对p开始的连续n个节点插入排序
    
public:
    List() { init(); }
    List(List<T> const& L);
    List(List<T> const& L, Rank r, int n);
    List(ListNodePosi(T) p, int n);
    ~List();
    
//only read
    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    T& operator[] (Rank r) const;
    ListNodePosi(T) first() const { return header->succ; }
    ListNodePosi(T) last() const { return trailer->pred; }
    
    bool vaild(ListNodePosi(T) p)//判断P位置是否对外合法
    {
        return p && (trailer!=p) && (header!=p);
    }
    
    int disordered() const;
    ListNodePosi(T) find(T const& e) const
    {
        return find(e, _size, trailer);
    }
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) search(T const& e) const
    {
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax()
    {
        return selectMax(header->succ, _size);
    }
    
//could write
    ListNodePosi(T) insertAsFirst(T const& e);
    ListNodePosi(T) insertAsLast(T const& e);
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);//作为节点p的后继插入
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);//作为节点p的前驱插入 
    
    T remove(ListNodePosi(T) p);
    void merge(List<T> L)
    {
        merge(first(), _size, L, L.first(), L._size);///////////
    }
    void sort(ListNodePosi(T) p, int n);
    void sort()
    {
        sort(header->succ, _size);
    }
    int deduplicate();
    int uniquify();
//    void reverse();
    
//    void traverse(void(* ) (T& ));
//    template <typename VST>
//    void traverse(VST&);
};

template <typename T>
void List<T>::init()//创建一个空列表
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <typename T>
T& List<T>::operator[] (Rank r) const
{
    ListNodePosi(T) p = first();
    while(0 < r--)
        p->succ;
    return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const//在位置p的n个前驱中查找
{
    while(0 < n--)
        if(e == (p = p->pred)->data)
            return p;
    return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
    _size++;
    return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
    _size++;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
    init();
    while(n--)
    {
        insertAsLast(p->data);//依次作为末尾节点插入
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
    copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const& L)
{
    copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, int n)
{
//    ListNodePosi<T> p = (L.first())->succ;
//    while(r--)
//        ListNodePosi<T> p = p->succ;
    copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p)
{
    T e = p->data;
    p->succ = (p->pred)->succ;
    p->pred = (p->succ)->pred;
//    delete [] p;//重复释放空间
    _size--;
    return e;
}

template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while(0 < _size)
        remove(header->succ);
    return oldSize;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

template <typename T>
int List<T>::deduplicate()
{
    if(_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    Rank r = 0;
    while(trailer != (p=p->succ))
    {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize-_size;
}

template <typename T>
int List<T>::uniquify()
{
    if(_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    ListNodePosi(T) q;
    while(trailer != (q=p->succ))
        if(p->data != q->data)
            p = q;
        else
            remove(q);
    return oldSize-_size;
}
    void reverse();

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const//p的n个前驱里面查找e（有序向量）
{
    while(n--)
        if(((p=p->pred)->data) <= e)
            break;
    return p;
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
    switch(rand() % 3)
    {
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{
    for(int r=0;r<n;r++)
    {
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for(int i=0;i<n;i++)//确定排序区间
        tail = tail->succ;
    while(1 < n)
    {
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template <typename T>
ListNodePosi(T) selectMax(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) max = p;
    for(ListNodePosi(T) cur = p;1 < n;n--)
        if(((cur = cur->succ)->data) >= (max->data))
            max = cur;
    return max;
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n)
{
    if(n < 2)
        return;
    int m = n >> 1;//取中界点
    ListNodePosi(T) q = p;
    for(int i=0;i<m;i++)
        q = q->succ;
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m);
}

template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
{
    ListNodePosi(T) pp = p->pred;
    while(0 < m)
        if((0 < n) && (p->data <= q->data))
        {
            if(q == (p = p->succ))
                break;
            n--;
        }
        else
        {
            insertB(p, L.remove((q=q->succ)->pred));
            m--;
        }
    p = pp->succ;
}

#endif
