#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arguments.h"
#include "globals.h"
#include "objparse.h"

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

    parse_obj(args->obj_path);

    return 0;
}
