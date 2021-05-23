#ifndef _LISTNODE_STAR_H
#define _LISTNODE_STAR_H

#include <cstdlib>
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode
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
    void reverse();
    
    void traverse(void(* ) (T& ));
    template <typename VST>
    void traverse(VST&);
};

#endif
