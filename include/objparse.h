#ifndef OBJPARSE_H
#define OBJPARSE_H

#include <stdlib.h>

/**
 * @struct vertex
 * @brief Represents a 3-dimensional vertex
 */
typedef struct vertex {
    double x;
    double y;
    double z;
} vertex;

/** 
 * @struct edge 
 * @brief Represents an edge between two vertices, members are indices into a vertex[]
 */
typedef struct edge {
    int v1;
    int v2;
} edge;

/** 
 * @struct face
 * @brief Represens a face consisting of three vertices, members are indices into a vertex[] 
 */
typedef struct face {
    int v1;
    int v2;
    int v3;
} face;

/** 
 * @struct obj
 * @brief Contains 3-dimensional object data read in from an .OBJ file
 */
typedef struct obj {
    /** Name of the object */
    char* name;
    /** Number of vertices */
    size_t n_verts;
    /** vertex[] */
    vertex* vertices;
    /** Number of edges */
    size_t n_edges;
    /** edge[] */
    edge* edges;
    /** Number of faces */
    size_t n_faces;
    /** face[] */
    face* faces;
} obj;

void print_obj(obj* obj);
int parse_obj(char* path_to_obj);

#endif /* OBJPARSE_H */
