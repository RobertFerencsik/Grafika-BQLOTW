#include "matrix.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 10

typedef struct 
{
	float matrix[3][3];
} Matrix;

typedef struct 
{
	Matrix array[MAX_SIZE];
	int top;
} Stack;

void intialize(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push_matrix(Stack *stack, Matrix matrix);
Matrix pop_marix(Stack *stack);

int main()
{
	float myMatrice[3][3];
	init_identity_matrix(myMatrice);
	print_matrix(myMatrice);
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);
    
    add_matrices(a, b, c);

    print_matrix(c);

	return 0;
}

void intialize(Stack *stack) 
{
	stack->top == -1;
}

bool isEmpty(Stack *stack) 
{
	return stack->top == -1;
}

bool isFull(Stack *stack)
{
	return stack->top == MAX_SIZE - 1;
}

void push_matrix(Stack *stack, Matrix matrix)
{
	if (isFull)
	{
		printf("Error: stack overflow");
		return;
	}
	stack->array[++stack->top] = matrix;
}

Matrix pop_matrix(Stack *stack)
{
	if (isEmpty(stack))
	{
		printf("Stack underflow");
		Matrix identity = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
		return identity;
	}
	
	Matrix popped = stack->array[stack->top];
	stack->top--;
	return popped;
}