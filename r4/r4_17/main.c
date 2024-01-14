#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////////

int get_array(char name, int array[], int size)
{
    if (array == 0 || size <= 0)
    {
        printf("\nError: incorrect array '%c' params", name);
        return 0;
    }

    printf("\nEnter array %c of %d items\n", name, size);
    for (int i=0; i < size; i++)
    {
        printf("%c[%d]=", name, i);
        int item = 0;
        if (scanf("%d", &item) != 1)
        {
            while(getchar() != '\n');
            printf("\nError: incorrect item value");
            return 0;
        }
        array[i] = item;
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////

void print_array(char name, int array[], int size)
{
    if( array == 0 || size <= 0 )
    {
        printf("\nInternal error: incorrect array '%c' print params", name);
        return;
    }
    printf("\n'%c': { ", name);
    for (int i=0; i < size-1; i++)
        printf("%d, ", array[i]);
    printf("%d }", array[size-1]);
}

//////////////////////////////////////////////////////////////////////////////////////////

void sort_array(int array[], int size)
{
    for (int i=0; i < size; i++)
    {
        for (int j=i+1; j < size; j++)
        {
            if (array[i] < array[j])
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
     }
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Сформировать новый упорядоченный по убыванию массив из
//    двух упорядоченных в том же порядке массивов: А (12) и В (20).

int main_1()
{
    const int SIZE_A = 3;
    const int SIZE_B = 5;
    const int SIZE_C = SIZE_A + SIZE_B;

    int A[SIZE_A];
    int B[SIZE_B];
    int C[SIZE_C];

    if (!get_array('A', A, SIZE_A) || !get_array('B', B, SIZE_B))
    {
        return -1;
    }

    printf("\nArrays before sorting:");
    print_array('A', A, SIZE_A);
    print_array('B', B, SIZE_B);

    for (int i=0; i < SIZE_A; i++)
        C[i] = A[i];

    for (int i=0; i < SIZE_B; i++)
        C[SIZE_A + i] = B[i];

    sort_array(A, SIZE_A);
    sort_array(B, SIZE_B);
    sort_array(C, SIZE_C);

    printf("\nArrays after sorting:");
    print_array('A', A, SIZE_A);
    print_array('B', B, SIZE_B);
    print_array('C', C, SIZE_C);
    printf("\n");

    system("pause");
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//do {
      main_1();
//} while(1);
    return 0;
}
