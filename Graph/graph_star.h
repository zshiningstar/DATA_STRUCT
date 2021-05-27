#ifndef _GRAPH_
#define _GRAPH_

#include<limits.h>
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;//顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv, typename Te>//顶点类型、边类型
class Graph
{
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
    
public:
    int n;//总顶点数
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
    
    int e;//总边数
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
};

#endif
