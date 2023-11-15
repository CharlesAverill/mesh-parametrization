#include "objparse.h"
#include "logging.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

size_t max_line_length = 50;

bool prefix(const char* pre, const char* str) { return strncmp(pre, str, strlen(pre)) == 0; }

void strip_whitespace(char* str)
{
    size_t start = 0;
    size_t end = strlen(str) - 1;

    while (start <= end && isspace((unsigned char)str[start])) {
        start++;
    }

    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    memmove(str, str + start, end - start + 1);

    str[end - start + 1] = '\0';
}

int parse_obj(char* path_to_obj)
{
    FILE* fp = fopen(path_to_obj, "r");
    if (!fp) {
        fatal(RC_FILE_ERROR, "Failed to open obj file \"%s\"", path_to_obj);
    }

    obj* obj = malloc(sizeof(struct obj));
    obj->n_verts = 0;
    size_t verts_length = 50;
    obj->vertices = malloc(sizeof(struct vertex) * verts_length);
    if (!obj->vertices) {
        fatal(RC_MEMORY_ERROR, "Failed to create vertices array");
    }
    obj->n_edges = 0;
    size_t edges_length = 50;
    obj->edges = malloc(sizeof(struct edge) * edges_length);
    if (!obj->edges) {
        fatal(RC_MEMORY_ERROR, "Failed to create edges array");
    }

    char* line = malloc(max_line_length);
    int line_number = 1;
    while (getline(&line, &max_line_length, fp) != -1) {
        strip_whitespace(line);

        mp_log(LOG_DEBUG, "Line %d: %s", line_number++, line);
        // Ignore comments, materials
        if (line[0] == '#' || prefix("mtllib", line)) {
            continue;
        }

        if (prefix("o ", line)) {
            // Parse object name
            obj->name = malloc(strlen(line) - 1);
            strcpy(obj->name, line + 2);
        } else if (prefix("v ", line)) {
            if (obj->n_verts >= verts_length) {
                verts_length *= 2;
                obj->vertices = realloc(obj->vertices, sizeof(struct vertex) * verts_length);
                if (!obj->vertices) {
                    fatal(RC_MEMORY_ERROR, "Failed to resize vertices array");
                }
            }

            // Parse vertex components
            char* x_str = strtok(line + 2, " ");
            char* y_str = strtok(NULL, " ");
            char* z_str = strtok(NULL, " ");
            obj->vertices[obj->n_verts++] = (vertex){atof(x_str), atof(y_str), atof(z_str)};
        } else if (prefix("l ", line)) {
            if (obj->n_edges >= edges_length) {
                edges_length *= 2;
                obj->edges = realloc(obj->edges, sizeof(edge) * edges_length);
                if (!obj->edges) {
                    fatal(RC_MEMORY_ERROR, "Failed to resize edges array");
                }
            }

            // Parse edge components
            char* v1_str = strtok(line + 2, " ");
            char* v2_str = strtok(NULL, " ");
            obj->edges[obj->n_edges++] = (edge){atoi(v1_str), atoi(v2_str)};
        }
    }

    fclose(fp);

    print_obj(obj);

    return 0;
}

void print_obj(obj* obj)
{
    printf("NAME: %s\n", obj->name);
    printf("-----------------------\n");
    printf("VERTS: %lu\n", obj->n_verts);
    for (int i = 0; i < obj->n_verts; i++) {
        printf("  %12.6f %12.6f %12.6f\n", obj->vertices[i].x, obj->vertices[i].y,
               obj->vertices[i].z);
    }
    printf("EDGES: %lu\n", obj->n_edges);
    for (int i = 0; i < obj->n_edges; i++) {
        printf("  %d %d\n", obj->edges[i].v1, obj->edges[i].v2);
    }
}
