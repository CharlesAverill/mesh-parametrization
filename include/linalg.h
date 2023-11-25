#ifndef LINALG_H
#define LINALG_H

#include<stdlib.h>

/**
 * @struct square matrix
 * @brief Matrix of size n x n
 */
typedef struct squareMatrix {
    double* data;
    size_t size;
} squareMatrix;


/**
 * @struct vector 
 * @brief vector of size n
 */
typedef struct vector {
    double* data;
    size_t size;
} vector;

void create_squareMatrix(squareMatrix* mat, int size);
void create_vector(vector* vec, int size);

double cross2(vector* a, vector* b);
double norm(vector* vec);


#endif /* LINALG_H */ 