#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double det(double **matrix, int size);
double cofactor(double **matrix, int ele_row, int ele_col, int size);
void inverse(double **matrix, int size);
void transpose(double **matrix, int size);

int main(int argc, char const *argv[])
{
    int n;
    printf("Enter matrix size (size of matrix): ");
    scanf("%d", &n);

    // Allocate memory for the matrix
    double **matrix = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double *)malloc(sizeof(double) * n);
    }

    // Input matrix elements
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter element %d,%d: ", i + 1, j + 1);
            scanf("%lf", &matrix[i][j]);
        }
    }

    // Calculate determinant
    double determinant = det(matrix, n);
    printf("Determinant: %.2lf\n", determinant);

    // Calculate and print the inverse
    inverse(matrix, n);
    printf("Inverse matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2lf ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

double det(double **matrix, int size)
{
    if (size == 1)
        return matrix[0][0];

    if (size == 2)
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);

    double determinant = 0;
    for (int i = 0; i < size; i++)
    {
        determinant += matrix[0][i] * cofactor(matrix, 0, i, size);
    }

    return determinant;
}

double cofactor(double **matrix, int ele_row, int ele_col, int size)
{
    // Allocate memory for the smaller matrix
    double **temp_matrix = (double **)malloc(sizeof(double *) * (size - 1));
    for (int i = 0; i < size - 1; i++)
    {
        temp_matrix[i] = (double *)malloc(sizeof(double) * (size - 1));
    }

    int row_itr = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == ele_row)
            continue;

        int col_itr = 0;
        for (int j = 0; j < size; j++)
        {
            if (j == ele_col)
                continue;

            temp_matrix[row_itr][col_itr] = matrix[i][j];
            col_itr++;
        }
        row_itr++;
    }

    // Calculate cofactor value
    double cofactor_value = pow(-1, (ele_row + ele_col)) * det(temp_matrix, size - 1);

    // Free allocated memory for the smaller matrix
    for (int i = 0; i < size - 1; i++)
    {
        free(temp_matrix[i]);
    }
    free(temp_matrix);

    return cofactor_value;
}

void inverse(double **matrix, int size)
{
    double det_value = det(matrix, size);
    if (det_value == 0)
    {
        printf("No inverse, singular matrix.\n");
        exit(0);
    }

    // Allocate memory for the cofactor matrix
    double **temp_matrix = (double **)malloc(sizeof(double *) * size);
    for (int i = 0; i < size; i++)
    {
        temp_matrix[i] = (double *)malloc(sizeof(double) * size);
    }

    // Calculate the cofactor matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp_matrix[i][j] = cofactor(matrix, i, j, size);
        }
    }

    // Transpose the cofactor matrix (to get the adjugate)
    transpose(temp_matrix, size);

    // Calculate the inverse matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = temp_matrix[i][j] / det_value;
        }
    }

    // Free the allocated memory for temp_matrix
    for (int i = 0; i < size; i++)
    {
        free(temp_matrix[i]);
    }
    free(temp_matrix);
}

void transpose(double **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}
