#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <argp.h>

/**
 * @struct Arguments
 * @brief Structure containing command line arguments
 */
typedef struct Arguments {
    /**Path to .obj file to read from*/
    char* obj_path;
} Arguments;

void parse_args(Arguments* args, int argc, char* argv[]);

#endif /* ARGUMENTS_H */
