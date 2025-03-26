#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);
/**
* Initializes all elements of the matrix to ones.
*/
void init_identity_matrix(float matrix[3][3]);
/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);
/**
* Multiply matrices 
*/
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void transform_point(const float transformationMatrix[3][3],const float point[3], float result[3]);

void scale(float transformationMatrix[3][3], float lambda);

void shift(float transformationMatrix[3][3], float dx, float dy);

void rotate(float transformationMatrix[3][3], float fi);

#endif // MATRIX_H

