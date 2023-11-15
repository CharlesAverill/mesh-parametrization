#ifndef OBJPARSE_H
#define OBJPARSE_H

#include <stdlib.h>

typedef struct vertex {
    double x;
    double y;
    double z;
} vertex;

typedef struct edge {
    int v1;
    int v2;
} edge;

typedef struct obj {
    char* name;
    size_t n_verts;
    vertex* vertices;
    size_t n_edges;
    edge* edges;
} obj;

void print_obj(obj* obj);
int parse_obj(char* path_to_obj);

#endif /* OBJPARSE_H */
