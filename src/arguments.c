#include <string.h>

#include "arguments.h"
#include "info.h"

const char* argp_program_version = PROJECT_NAME_AND_VERS;
const char* argp_program_bug_address = "";
static char doc[] = "A program to parametrize .OBJ meshes";
static char args_doc[] = "OBJ";

static struct argp_option options[] = {
    {"logging", 'l', "LOG_LEVEL", 0,
     "The logging level during execution (DEBUG, INFO, WARNING, ERROR, CRITICAL)"},
    {0},
};

error_t parse_opt(int key, char* arg, struct argp_state* state)
{
    Arguments* arguments = state->input;

    switch (key) {
    case 'l':
        if (strcmp(arg, "DEBUG") == 0) {
            arguments->log_level = LOG_DEBUG;
        } else if (strcmp(arg, "INFO") == 0) {
            arguments->log_level = LOG_INFO;
        } else if (strcmp(arg, "WARNING") == 0) {
            arguments->log_level = LOG_WARNING;
        } else if (strcmp(arg, "ERROR") == 0) {
            arguments->log_level = LOG_ERROR;
        } else if (strcmp(arg, "CRITICAL") == 0) {
            arguments->log_level = LOG_CRITICAL;
        } else {
            argp_usage(state);
        }
        break;
    case ARGP_KEY_ARG:
        // Check for too many arguments
        if (state->arg_num >= 1) {
            argp_usage(state);
        }
        arguments->obj_path = arg;
        break;
    case ARGP_KEY_END:
        // Check for not enough arguments
        if (state->arg_num < 1) {
            argp_usage(state);
        }
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

/**
 * @brief Parse arguments into an Arguments structure
 *
 * @param args Arguments struct to parse into
 * @param argc Number of arguments
 * @param argv List of arguments as strings
 */
void parse_args(Arguments* args, int argc, char* argv[])
{
    // Set defaults here
    args->obj_path = "objs/cube.obj";
    args->log_level = LOG_INFO;

    argp_parse(&argp, argc, argv, 0, 0, args);
}
