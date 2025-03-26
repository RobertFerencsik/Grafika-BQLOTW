#include "matrix.h"
#include <math.h>
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
    int i;
    int j;
	init_zero_matrix(matrix);
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(j == i)
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
		float sum = 0;
		for(j = 0; j < 3; j++) {
			sum = transformationMatrix[i][j] * result[j];
		}
		result[i] = sum;
	}
}

void scale(float transformationMatrix[3][3], float lambda) {
	init_identity_matrix(transformationMatrix);
	transformationMatrix[0][0] = lambda;
	transformationMatrix[1][1] = lambda;
}

void shift(float transformationMatrix[3][3], float dx, float dy) {
	init_identity_matrix(transformationMatrix);
	transformationMatrix[0][2] = dx;
	transformationMatrix[1][2] = dy;
}

void rotate(float transformationMatrix[3][3], float fi) {
	init_identity_matrix(transformationMatrix);
	fi = (fi / 180) * M_PI;
	transformationMatrix[0][0] = cos(fi);
	transformationMatrix[1][1] = cos(fi);
	transformationMatrix[0][1] = -sin(fi);
	transformationMatrix[1][0] = sin(fi);
}
