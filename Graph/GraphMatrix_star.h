#ifndef _GRAPH_MATRIX_
#define _GRAPH_MATRIX_

#include "../Vector/vector_star.h"
#include "graph_star.h"

template <typename Tv>
struct Vertex//顶点对象
{
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int parent;
    int priority;
    
    Vertex(Tv const& d = (Tv) 0 ) ://构造新顶点
    
}
















#endif
