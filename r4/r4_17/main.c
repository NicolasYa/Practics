#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////////////////////////////////////////////////////////////

int get_array(char* name, int array[], int size)
{
    if (name == 0 || array == 0 || size <= 0)
    {
        printf("\nInternal error: incorrect array params");
        return 0;
    }

    printf("\n%s [%d]:\n", name, size);
    for (int i=0; i < size; i++)
    {
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

void print_array(char* name, int array[], int size)
{
    if (name == 0 || array == 0 || size <= 0)
    {
        printf("\nInternal error: incorrect array print params");
        return;
    }
    printf("\n%s: { ", name);
    for (int i=0; i < size-1; i++)
        printf("%d, ", array[i]);
    printf("%d }\n", array[size-1]);
}

//////////////////////////////////////////////////////////////////////////////////////////

int get_matrix(char* name, int raws, int columns, int matrix[raws][columns])
{
    if (name == 0 || matrix == 0 || raws <= 0 || columns <= 0)
    {
        printf("\nInternal error: incorrect matrix params");
        return 0;
    }

    printf("\n%s [%d,%d]:\n", name, raws, columns);
    for (int i=0; i < raws; i++)
    {
        for (int j=0; j < columns; j++)
        {
            int item = 0;
            if (scanf("%d", &item) != 1)
            {
                while(getchar() != '\n');
                printf("\nError: incorrect matrix item value");
                return 0;
            }
            matrix[i][j] = item;
        }
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////

void print_matrix(char* name, int raws, int columns, int matrix[raws][columns])
{
    if (name == 0 || matrix == 0 || raws <= 0 || columns <= 0)
    {
        printf("\nInternal error: incorrect matrix params");
        return;
    }
    printf("\n%s [%d,%d]:\n", name, raws, columns);
    for (int i=0; i < raws; i++)
    {
        printf("{ ");
        for (int j=0; j < columns-1; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("%d }\n", matrix[i][columns-1]);
    }
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

    if (!get_array("A", A, Size_A) || !get_array("B", B, Size_B))
    {
        return -1;
    }

    printf("\nArrays before sorting:\n");
    print_array("A", A, Size_A);
    print_array("B", B, Size_B);

    for (int i=0; i < Size_A; i++)
        C[i] = A[i];

    for (int i=0; i < Size_B; i++)
        C[Size_A + i] = B[i];

    sort_array(A, Size_A);
    sort_array(B, Size_B);
    sort_array(C, Size_C);

    printf("\nArrays after sorting:\n");
    print_array("A", A, Size_A);
    print_array("B", B, Size_B);
    print_array("C", C, Size_C);

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
    int A[Size];
    if (!get_array("A", A, Size))
    {
        return -1;
    }

    printf("\nArray before changes:\n");
    print_array("A", A, Size);

    for (int i = 0;i < Size; i++)
    {
        if (A[i] == 0)
        {
            // find first non-zerro
            int non_zerro=i+1;
            for (; non_zerro < Size; non_zerro++)
            {
                if (A[non_zerro] != 0)
                    break;
            }
            if (non_zerro==Size)
                break; // no non-zerro items

            // swap zerro item with non-zerro item
            A[i] = A[non_zerro];
            A[non_zerro] = 0;
        }
    }

    printf("\nArray after changes:\n");
    print_array("A", A, Size);

    system("pause");
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Дан целочисленный массив В (7х11). Определить, сколько в
//    нем пар соседних одинаковых элементов. Элементы считаются сосед-
//    ними, если их индексы в столбцах и/или в строках различаются не
//    более чем на единицу.

int main_3()
{
    const int Raws = 3;
    const int Columns = 4;
    int M[Raws][Columns];

    if (!get_matrix("M", Raws, Columns, M))
    {
        return -1;
    }

    print_matrix("M", Raws, Columns, M);

    int pairs = 0;
    for (int i = 0; i < Raws-1; i++)
        for (int j = 0; j < Columns-1; j++)
        {
            if (M[i][j] == M[i+1][j])
                pairs++;
            if (M[i][j] == M[i][j+1])
                pairs++;
            if (M[i][j] == M[i+1][j+1])
                pairs++;
            if (M[i+1][j] == M[i][j+1])
                pairs++;
        }

    int last_raw = Raws-1;
    for (int j = 0; j < Columns-1; j++)
    {
        if (M[last_raw][j] == M[last_raw][j+1])
            pairs++;
    }

    int last_column = Columns-1;
    for (int i = 0; i < Raws-1; i++)
    {
        if (M[i][last_column] == M[i+1][last_column])
            pairs++;
    }

    printf("\nPairs detected: %d\n", pairs);

    system("pause");
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Вычислить min
//    Z = Xmin / (Xmax+Xmin)
//    , где Xmin и Xmax – минимальный положительный и максимальный элементы матрицы.

int main_4()
{
    const int Raws = 3;
    const int Columns = 4;
    int M[Raws][Columns];

    if (!get_matrix("M", Raws, Columns, M))
    {
        return -1;
    }
    print_matrix("M", Raws, Columns, M);

    int positive_max = INT_MIN;
    int positive_min = INT_MAX;

    for (int i = 0; i < Raws; i++)
        for (int j = 0; j < Columns; j++)
        {
            int item = M[i][j];
            if( item < 0 )
                continue;
            if (item < positive_min)
                positive_min = item;
            if (item > positive_max)
                positive_max = item;
        }

    if (positive_min == INT_MAX )
        printf("\nXmin not found");
    else
        printf("\nXmin: %d", positive_min);

    if (positive_max == INT_MIN )
        printf("\nXmax not found");
    else
        printf("\nXmax: %d", positive_max);

    if (positive_min != INT_MAX && positive_max != INT_MIN)
    {
        float devider = positive_min + positive_max;
        if (devider != 0)
            printf("\nXmin/(Xmin + Xmax) = %f", positive_min/devider);
        else
            printf("\nError: Xmin + Xmax = 0");
    }
    printf("\n");

    system("pause");
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//    main_2();
//    main_3();
do {
      main_4();
} while(1);
    return 0;
}
