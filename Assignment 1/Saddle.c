#include <stdio.h>
#include <stdlib.h>

/* Function: create2DArray
 * --------------------------
 *  Creates a 2D array dynamically 
 *  
 *  r: Number of rows of the array
 *  c: Number of columns of the array
 *
 *  returns: Base address of the created array
 */
int** create2DArray(int r, int c)
{
    int** newArray = (int**)malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            newArray[i] = (int*)malloc(c * sizeof(int));
    }
    printf("Enter the values:\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            scanf("%d", &newArray[i][j]);
    }
    return newArray;
}

/* Function: free2DArray
 * ------------------------
 *  Frees the memory allocated dynamically for a given 2D matrix
 *  
 *  rows: Number of rows of the matrix
 *  array: Base address of the matrix
 */
void free2DArray(int rows, int **array)
{
    for (int i = 0; i < rows; i++)
        free(array[i]);
    free(array);
}

/* Function: findMinInRow
 * --------------------------
 *  Finds the minimum element of a given row of a given 2D array
 *  
 *  cols: Number of columns of the array
 *  arrayRow: A row of a 2D matrix (may also be a 1D array)
 *
 *  returns: 1 if value is minimum in row, 0 otherwise
 */
int findMinInRow(int cols, int *arrayRow)
{
    int min = arrayRow[0];
    int minPos = 0;
    for (int j = 1; j < cols; j++)
    {
        if (arrayRow[j] < min)
        {
            min = arrayRow[j];
            minPos = j;
        }
    }
    return minPos;
}

/* Function: isMaxInCol
 * --------------------------
 *  Checks if an element of the 2D array is the maximum in its corresponding column 
 *  
 *  value: The element to be checked
 *  rows: Number of columns of the array
 *  c: Corresponding column of value
 *  array: The 2D matrix whose column is to be checked
 *
 *  returns: 1 if value is maximum in column, 0 otherwise
 */
int isMaxInCol(int value, int rows, int c, int **arrayCol)
{
    for (int i = 0; i < rows; i++)
    {
        if (arrayCol[i][c] > value)
            return 0;
    }
    return 1;
}

int main()
{
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    if((rows <= 0) || (cols <= 0))
        printf("-2");
    else
    {
        int flag = 0;       // Status of presence of saddle point
        int saddleRow, saddleColumn;    // Index of saddle point
        int **array = create2DArray(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            int rowMinPos = findMinInRow(cols, array[i]);
            if (isMaxInCol(array[i][rowMinPos], rows, rowMinPos, array))
            {
                flag = 1;
                saddleRow = i;
                saddleColumn = rowMinPos;
                break;
            }
        }
        if (flag)
            printf("%d %d", saddleRow, saddleColumn);
        else
            printf("-1");
        free2DArray(rows, array);
    }
}