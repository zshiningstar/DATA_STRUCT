#ifndef _BINNODE_
#define _BINNODE_

#include <cstdlib>

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)//节点高度(空树高度为-1)
typedef enum {RB_RED, RB_BLACK} RBColor;

template <typename T>
struct BinNode
{
    T data;
    BinNodePosi(T) parent;//父节点
    BinNodePosi(T) lc;//左孩子
    BinNodePosi(T) rc;//右孩子
    int height;//高度
    int npl;//左式堆
    RBColor color;//颜色
    BinNode():
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    BinNode(T e,BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, 
            BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) : 
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
            
    //接口
    int size();//当前节点后代总数
    BinNodePosi(T) insertAsLC (T const& );
    BinNodePosi(T) insertAsRC (T const& );
    BinNodePosi(T) succ();//获取当前节点的直接后继

    bool operator< (BinNode const& bn)
    {
        return data < bn.data;
    }
    bool operator== (BinNode const& bn)
    {
        return data == bn.data;
    }

    //
    template <typename VST>
    void travLevel(VST& );

    template <typename VST>
    void travPre(VST& );

    template <typename VST>
    void travIn(VST& );

    template <typename VST>
    void travPost(VST& );
};
#endif
