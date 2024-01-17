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

int main()
{
//    main_1();
//    main_2();
//    main_3();
//do {
      main_1();
//} while(1);
    return 0;
}
