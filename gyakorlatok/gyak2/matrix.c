#include "matrix.h"

#include <stdio.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void init_identity_matrix(float matrix[3][3]) 
{
	int i,j;
	
	for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				matrix[i][j] = 1.0;
			}
	}
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]) {
	int i, j, k;
	
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			float sum;
			for(k = 0; k < 3; k++) {
				sum = a[i][k]* b[k][j];
			}
			c[i][j] = sum;
		}
	}
}

void transform_point(const float transformationMatrix[3][3],const float point[3],float result[3]) {
	int i,j;
	
	for(i = 0; i < 3;i++) {
		sum = 0;
		for(j = 0; j < 3; j++) {
			sum = transformationMatrix[i][j] * result[j];
		}
		result[i] = sum;
	}
}

void scale(float transformationMatrix, float scale) {
	
}

void shift(float transformationMatrix) {
	
}

void rotate(float transformationMatrix) {
	
}
