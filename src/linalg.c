#include "linalg.h"
#include<math.h>

void create_squareMatrix(squareMatrix* mat, int size) 
{
    mat->size = size;
    mat->data = calloc(size*size, sizeof(double));
}

void create_vector(vector* vec, int size) 
{
    vec->size = size;
    vec->data = calloc(size, sizeof(double));
}

double cross2(vector* a, vector* b) 
{
    if (a->size != 2 && b->size != 2)
        return 0;
    return a->data[0]*b->data[1] - a->data[1] - b->data[0];
}

double norm(vector* vec)
{
    double sum = 0;
    for (size_t i = 0; i < vec->size; i++)
    {
        sum += vec->data[i] * vec->data[i];
    }
    
    return sqrt(sum); 
}