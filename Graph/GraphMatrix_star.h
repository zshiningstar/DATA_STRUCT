#ifndef _GRAPH_MATRIX_
#define _GRAPH_MATRIX_

#include "../Vector/vector_star.h"
#include<limits.h>
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;//顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv>
struct Vertex//顶点对象
{
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime;
    int fTime;
    int parent;
    int priority;
    
    Vertex(Tv const& d = (Tv) 0 ) ://构造新顶点
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te>
struct Edge
{
    Te data;
    int weight;
    EType type;
    Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

template <typename Tv, typename Te>//顶点类型、边类型
class Graph
{
public:
    int n, e;
public:
//    int n;//总顶点数
    virtual int insert(Tv const& ) = 0;
    virtual Tv remove(int) = 0;
    virtual Tv& vertex(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int) = 0;
    virtual VStatus& status(int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0;
    virtual int& priority(int) = 0;
    
//    int e;//总边数
    virtual bool exists(int, int) = 0;
    virtual void insert(Te const&, int, int, int) = 0;
    virtual Te remove(int, int) = 0;
    virtual EType& type(int, int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int& weight(int, int) = 0;
//    void bfs(int);//广度优先算法
//    void dfs(int);//深度优先算法
//    void bcc(int);
//    Stack<Tv>* tSort(int);//基于dfs的拓扑排序法
//    void prim(int);//最小支撑树Prim算法
//    void dijkstra(int);//最短路径dijkstra算法
//    template <typename PU>
//    void pfs(int, PU);//优先级搜索框架
private:
    void reset()
    {
        for(int i = 0; i < n; i++)
        {
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for(int j = 0; j < n; j++)
                if(exists(i, j)) type(i, j) = UNDETERMINED;
        }
    }
    
//    void BFS(int, int&);//广度优先搜索算法
//    void DFS(int, int&);//深度优先搜索算法
//    void BCC(int, int&, Stack<int>&);
//    bool TSort(int, int&, Stack<Tv>* );
//    template <typename PU>
//    void PFS(int, PU);
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
private:
    Vector< Vertex<Tv> > V;
    Vector< Vector<Edge<Te>*> > E;
public:
    int n;
    int e;
    GraphMatrix()
    {
        n = e = 0;
    }
    ~GraphMatrix()//释放动态分配的内存
    {
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                delete E[j][k];
    }
    
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return nextNbr(i, n); }
    virtual int nextNbr(int i,int j)
    {
        while((-1 < j) && (!exists(i,--j)));
        return j;
    }
    virtual VStatus& status(int i) { return V[i].status; }
    virtual int& dTime(int i) { return V[i].dTime; }
    virtual int& fTime(int i) { return V[i].fTime; }
    virtual int& parent(int i) { return V[i].parent; }
    virtual int& priority(int i) { return V[i].priority; }
    
    virtual int insert(Tv const& vertex)
    {
        for(int j = 0; j < n; j++)
            E[j].insert(NULL);
        n++;
        E.insert(Vector<Edge<Te>*> (n, n, (Edge<Te>*) NULL));
        return V.insert(vertex);//按照书上写的编译不过
    }
    
    virtual Tv remove(int i)
    {
        for(int j = 0; j < n; j++)
            if(exists(i, j))
            {
                delete E[i][j];
                V[j].inDegree--;
            }
        E.remove(i);
        n--;
        Tv vBak = vertex(i);
        V.remove(i);
        for(int j = 0; j < n; j++)
            if(Edge<Te> * e = E[j].remove(i))
            {
                delete e;
                V[j].outDegree--;
            }
        return vBak;
    }
    
    virtual bool exists(int i, int j)
    {
        return (0 <= i) && (i < n) && (0 <=j ) && (j < n) && E[i][j] != NULL;
    }
    
    virtual EType& type(int i, int j)
    {
        return E[i][j]->type;
    }
    
    virtual Te& edge(int i, int j)
    {
        return E[i][j]->data;
    }
    
    virtual int& weight(int i, int j)
    {
        return E[i][j]->weight;
    }
    
    virtual void insert(Te const& edge, int w, int i, int j)
    {
        if(exists(i, j))
            return;
        E[i][j] = new Edge<Te> (edge, w);
        e++;
        V[i].outDegree++;
        V[j].inDegree++;
    }
    
    virtual Te remove(int i, int j)
    {
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;
        e--;
        V[i].outDegree--;
        V[j].inDegree--;
        return eBak;
    }
};

#endif
