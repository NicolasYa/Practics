#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////////

void print_matrix( int raws, int columns, int matrix[raws][columns])
{
    printf("\n[%d,%d]:\n", raws, columns);
    for (int i=0; i < raws; i++)
    {
        for (int j=0; j < columns; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

int compare_items( int a, int b, int direction)
{
    return direction > 0 ? (a > b) : (a < b);
}

void sort_array(int array[], int size, int direction)
{
    for (int i=0; i < size; i++)
    {
        for (int j=i+1; j < size; j++)
        {
            if (compare_items(array[i], array[j], direction))
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
     }
}

//////////////////////////////////////////////////////////////////////////////////////////

void main_1()
{
    int M[6][7]=
        {
            {1, 2, 3, 4, 5 ,6 ,7 },
            {1, 2, 3, 4, 5 ,6 ,7 },
            {1, 2, 3, 4, 5 ,6 ,7 },
            {1, 2, 3, 4, 5 ,6 ,7 },
            {1, 2, 3, 4, 5 ,6 ,7 },
            {1, 2, 3, 4, 5 ,6 ,7 },
        };

    printf("\nBefore:");
    print_matrix(6, 7, M);

    for (int i = 0; i<6; i++)
        sort_array( &(M[i][0]), 7, (i%2) ? 1 : -1);

    printf("\nAfter:");
    print_matrix(6, 7, M);
}

//////////////////////////////////////////////////////////////////////////////////////////

int find_2_negatives( int column, int raws, int columns, int matrix[raws][columns])
{
    int negatives = 0;
    for (int i=0; i < raws; i++)
    {
        if (matrix[i][column] < 0)
            negatives++;
    }
    return negatives == 2;
}

void main_2()
{
    int B[4][3]=
        {
            {-1, 2,  3 },
            { 1, 2, -3 },
            { 1, 2, -3 },
            {-1, 2,  3 },
         };

    int C[3][4]=
        {
            {1, -2, 3, -4 },
            {1,  2, 3, -4 },
            {1, -2, 3, -4 },
         };

    printf("\nB:");
    print_matrix(4, 3, B);

    printf("\nC:");
    print_matrix(3, 4, C);


    printf("\nIn matrix B 2 negatives in columns: ");
    for (int j = 0; j<3; j++)
        if ( find_2_negatives(j, 4, 3, B))
            printf("%d ", j+1);

    printf("\nIn matrix C 2 negatives in columns: ");
    for (int j = 0; j<4; j++)
        if ( find_2_negatives(j, 3, 4, C))
            printf("%d ", j+1);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//    main_2();
//    main_3();
//do {
      main_2();
//} while(1);
    return 0;
}
