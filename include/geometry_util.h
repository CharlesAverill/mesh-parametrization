#ifndef GEOMETRY_UTIL_H
#define GEOMETRY_UTIL_H

#include "linalg.h"
#include "objparse.h"

squareMatrix build_adjacency_matrix(obj* obj);

void find_boundary_loop(int* boundary, size_t* b_size, obj* obj);

void build_edges(obj* obj);

typedef struct edgeList {
    edge* edges;
    size_t n_edges;
} edgeList;

#endif /* GEOMETRY_UTIL_H */