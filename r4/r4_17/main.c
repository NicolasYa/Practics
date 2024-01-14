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
    if (array == 0 || size <= 0)
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
    const int Size_A = 3;
    const int Size_B = 5;
    const int Size_C = Size_A + Size_B;

    int A[Size_A];
    int B[Size_B];
    int C[Size_C];

    if (!get_array('A', A, Size_A) || !get_array('B', B, Size_B))
    {
        return -1;
    }

    printf("\nArrays before sorting:");
    print_array('A', A, Size_A);
    print_array('B', B, Size_B);

    for (int i=0; i < Size_A; i++)
        C[i] = A[i];

    for (int i=0; i < Size_B; i++)
        C[Size_A + i] = B[i];

    sort_array(A, Size_A);
    sort_array(B, Size_B);
    sort_array(C, Size_C);

    printf("\nArrays after sorting:");
    print_array('A', A, Size_A);
    print_array('B', B, Size_B);
    print_array('C', C, Size_C);
    printf("\n");

    system("pause");
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Удалить из линейного целочисленного массива все нули, пе-
//    редвинув на их место следующие элементы без нарушения порядка их
//    следования.

int main_2()
{
    const int Size = 6;
    int a[Size];
    if (!get_array('a', a, Size))
    {
        return -1;
    }

    printf("\nArray before changes:");
    print_array('a', a, Size);

    for (int i = 0;i < Size; i++)
    {
        if (a[i] == 0)
        {
            // find first non-zerro
            int non_zerro=i+1;
            for (; non_zerro < Size; non_zerro++)
            {
                if (a[non_zerro] != 0)
                    break;
            }
            if (non_zerro==Size)
                break; // no non-zerro items

            // swap zerro with non-zerro items
            a[i] = a[non_zerro];
            a[non_zerro] = 0;
        }
    }

    printf("\nArray after changes:");
    print_array('a', a, Size);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//    main_2();
do {
      main_2();
} while(1);
    return 0;
}
