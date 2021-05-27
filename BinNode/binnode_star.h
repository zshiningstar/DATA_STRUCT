#ifndef _BINNODE_
#define _BINNODE_

#include <cstdlib>
#define IsRoot(x)           (!((x).parent))//(x).parent == NULL说明为根节点
#define IsLChild(x)         (!IsRoot(x) && (&(x) == (x).parent->lc))//当前节点不是根节点并且当前节点地址和其父亲节点的左孩子一致
#define IsRChild(x)         (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x)        (!IsRoot(x))
#define HasLChild(x)        ((x).lc)
#define HasRChild(x)        ((x).rc)
#define HasChild(x)         (HasLChild(x) || HasRChild(x))
#define HasBothChild(x)     (HasLChild(x) && HasRChild(x))
#define IsLeaf(x)           (!HasChild(x))//是否叶子节点
#define sibling(p)          (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x)            (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x)     (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)//节点高度(空树高度为-1)带参宏定义
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

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC (T const& e)
{
    return lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC (T const& e)
{
    return rc = new BinNode(e, this);
}

#define BinTreePosi(T) BinTree<T>*

template <typename T>
class BinTree
{
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight (BinNodePosi(T) x);//更新节点x的高度
    void updateHeightAbove (BinNodePosi(T) x);//更新节点x及其祖先的高度
public:
    BinTree() : _size(0), _root(NULL) {}
    ~BinTree()
    {
        if(0<_size)
            remove(_root);
    }
    int size() const
    {
        return _size;
    }
    bool empty() const
    {
        return !_root;
    }
    BinNodePosi(T) root() const
    {
        return _root;
    }
    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);//左孩子
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);//右孩子
    BinNodePosi(T) attachAsLC(BinNodePosi(T), BinTreePosi(T) &);//"&" 换成"&T"带形参后会报错
    BinNodePosi(T) attachAsRC(BinNodePosi(T), BinTreePosi(T) &);
    
    int remove (BinNodePosi(T) x);
    BinNodePosi(T) secede(BinNodePosi(T) x);
    template <typename VST>
    void travLevel(VST& visit)
    {
        if(_root)
            _root->travLevel(visit);//层次遍历
    }
    template <typename VST>
    void travPre(VST& visit)
    {
        if(_root)
            _root->travPre(visit);//先序遍历
    }
    template <typename VST>
    void travIn(VST& visit)
    {
        if(_root)
            _root->travIn(visit);
    }
    template <typename VST>
    void travPost(VST& visit)
    {
        if(_root)
            _root->travPost(visit);
    }
    bool operator< (BinNode<T> const& t)
    {
        return _root && t._root && (_root == t._root);//
    }
    bool operator== (BinTree<T> const& t)
    {
        return _root && t._root && (_root == t._root);//调用结构体重载的==函数
    }
};

template <typename T>
int BinTree<T>::updateHeight (BinNodePosi(T) x)
{
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove (BinNodePosi(T) x)
{
    while(x)
    {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
    _size = 1;
    return _root = new BinNode<T> (e);//使用new关键字来创建一个根节点，形参传入第一个
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
    _size++:
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;//e插入为x的左孩子
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
    _size++:
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;//e插入为x的右孩子
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTreePosi(T) &S)//将S作为x的左子树插入
{
    if(x->lc == S->_root)
        x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTreePosi(T) &S)
{
    if(x->rc == S->_root)
        x->rc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}

template <typename T>
int BinTree<T>::remove (BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;//删除节点总数
}

template <typename T>
static int removeAt(BinNodePosi(T) x)
{
    if(!x)
        return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template <typename T>
BinNodePosi(T) BinTree<T>::secede(BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}

#endif
