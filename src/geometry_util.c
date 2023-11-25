#include "geometry_util.h"
#include <stdlib.h>

squareMatrix build_adjacency_matrix(obj* obj) 
{
    size_t size = obj->n_verts;
    squareMatrix* adajacency; 

    create_squareMatrix(adajacency, size);

    for (size_t i = 0; i < obj->n_edges; i++)
    {
        edge e = obj->edges[i];
        if (adajacency->data[e.v1 * size + e.v2] == 0)
        {
            adajacency->data[e.v1 * size + e.v2] = 1;
            adajacency->data[e.v2 * size + e.v1] = 1;
        }
    }
    
    return *adajacency;
}
