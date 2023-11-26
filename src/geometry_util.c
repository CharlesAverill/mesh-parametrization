#include "geometry_util.h"
#include "logging.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

squareMatrix build_adjacency_matrix(obj* obj) 
{
    size_t size = obj->n_verts;
    squareMatrix* adajacency; 

    create_squareMatrix(adajacency, size);

    if (obj->n_edges == 0)
        build_edges(obj);

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

void build_edges(obj* obj) {
    face* faces = obj->faces;
    size_t n_faces = obj->n_faces;
    edge halfEdges[3 * n_faces];

    for (size_t i = 0; i < n_faces; i++)
    {
        halfEdges[3*i] = (edge){faces[i].v2,faces[i].v3};
        halfEdges[3*i+1] = (edge){faces[i].v3,faces[i].v1};
        halfEdges[3*i+2] = (edge){faces[i].v1,faces[i].v2};
    }

    edge edges[3 * n_faces];
    size_t n_edges = 0;

    for (size_t i = 0; i < 3*n_faces; i++)
    {
        bool seen = false;
        for (size_t j = 0; j < n_edges; j++)
            if (halfEdges[i].v1 == edges[j].v2 && halfEdges[i].v2 == edges[j].v1) 
            {
                seen = true;
                break;
            }

        if (seen)
            break;
        
        edges[n_edges++] = halfEdges[i];
    }

    free(halfEdges);
    free(obj->edges);
    
    obj->edges = edges;
    obj->n_edges = n_edges;
}

void find_boundary_edges(edgeList* b_edges, face* faces, size_t n_faces)
{
    edge halfEdges[3 * n_faces];

    for (size_t i = 0; i < n_faces; i++)
    {
        halfEdges[3*i] = (edge){faces[i].v2,faces[i].v3};
        halfEdges[3*i+1] = (edge){faces[i].v3,faces[i].v1};
        halfEdges[3*i+2] = (edge){faces[i].v1,faces[i].v2};
    }

    size_t size = n_faces;
    edge* boundaryEdges = malloc(n_faces * sizeof(edge));
    size_t n_boundaryEdges = 0;
    for (size_t i = 0; i < 3*n_faces; i++)
    {
        bool seen = false;
        for (size_t j = 0; j < 3*n_faces; j++)
            if (i == j)
                continue;
            else if (halfEdges[i].v1 == boundaryEdges[j].v2 && halfEdges[i].v2 == boundaryEdges[j].v1) 
            {
                seen = true;
                break;
            }

        if (seen)
            break;
        
        if (n_boundaryEdges + 1 > size) 
        {
            size *= 2;
            boundaryEdges = realloc(boundaryEdges, size * sizeof(edge));
            if(!boundaryEdges) {
                    fatal(RC_MEMORY_ERROR, "Failed to resize faces array");
            }
        }

        boundaryEdges[n_boundaryEdges++] = halfEdges[i];
    }
    
    free(halfEdges);

    b_edges->edges = boundaryEdges;
    b_edges->n_edges = n_boundaryEdges;
}

bool any(bool* array, size_t size)
{
    bool flag = false;
    for (size_t i = 0; i < size; i++)
    {
        flag |= array[i];
    }
    
}

void find_boundary_loop(int* boundary, size_t* b_size, obj* obj)
{
    edgeList* boundaryEdges;
    find_boundary_edges(boundaryEdges, obj->faces, obj->n_faces);
    edge* bE = boundaryEdges->edges;
    size_t size = boundaryEdges->n_edges;
    bool unseen[size];
    int greatest_loop[2*size];
    int greatest_size = 0;


    for (size_t i = 0; i < size; i++)
    {
        unseen[i] = true;
    }

    while (any(unseen, size))
    {
        int loop[2*size];
        int loop_size = 0;
        int current_edge_index;
        for (size_t i = 0; i < size; i++)
        {
            if (unseen[i] == true)
            {
                current_edge_index = i;
                break;
            }
        }

        edge current_edge = bE[current_edge_index];
        int start = current_edge.v1;
        int head = current_edge.v2;
        unseen[current_edge_index] = false;
        loop[loop_size++] = start;

        while(head != start) 
        {
            loop[loop_size++] = head;
            for (size_t i = 0; i < size; i++)
            {
                if (unseen[i])
                {
                    if (bE[i].v1 == head) 
                    {
                        head = bE[i].v2;
                    }
                    if (bE[i].v2 == head)
                    {
                        head = bE[i].v1;
                    }
                    unseen[i] = false;
                    break;
                }
            }
        }

        if (loop_size > greatest_size)
        {
            greatest_size = loop_size;
            memcpy(greatest_loop, loop, loop_size);
        }
    }

    boundary = greatest_loop;
    *b_size = greatest_size;    
}