#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arguments.h"
#include "globals.h"
#include "objparse.h"
#include "linalg.h"
#include "geometry_util.h"

/**
 * @brief Program entrypoint
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments as strings
 * @return Return code for program
 */
int main(int argc, char* argv[])
{
    // Parse arguments
    Arguments* args = malloc(sizeof(Arguments));
    if (args == NULL) {
        fprintf(stderr, "Failed to allocate memory for argument parsing\n");
        return 1;
    }

    parse_args(args, argc, argv);

    global_log_level = args->log_level;

    obj* obj = parse_obj(args->obj_path);

    printf("%ld, %ld, %ld\n", obj->n_verts,obj->n_edges, obj->n_faces);
    
    build_edges(obj);

    squareMatrix* adj = build_adjacency_matrix(obj);
    printf("%ld, %ld, %ld\n", obj->n_verts,obj->n_edges, obj->n_faces);
    size_t size;
    int* boundary = find_boundary_loop(&size, obj);
    //for (size_t i = 0; i < size; i++)
    //{
        //printf("%d ", boundary[i]);
    //}
    
    printf("\n");

    return 0;
}
