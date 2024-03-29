#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////////////////////////////////////////////////////////////

int get_array(char* name, int array[], int size)
{
    if (name == NULL || array == NULL || size <= 0)
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
    if (name == NULL || array == NULL || size <= 0)
    {
        printf("\nInternal error: incorrect array print params");
        return;
    }
    printf("\n%s: ", name);
    for (int i=0; i < size; i++)
        printf("%d\t", array[i]);
}

//////////////////////////////////////////////////////////////////////////////////////////

int get_matrix(char* name, int raws, int columns, int matrix[raws][columns])
{
    if (name == NULL || matrix == NULL || raws <= 0 || columns <= 0)
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
    if (name == NULL || matrix == NULL || raws <= 0 || columns <= 0)
    {
        printf("\nInternal error: incorrect matrix params");
        return;
    }
    printf("\n%s [%d,%d]:\n", name, raws, columns);
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

    for (int i=0; i < Size_A; i++)
        C[i] = A[i];

    for (int i=0; i < Size_B; i++)
        C[Size_A + i] = B[i];

    printf("\nArrays before sorting:");
    print_array("A", A, Size_A);
    print_array("B", B, Size_B);
    print_array("C", C, Size_C);

    sort_array(A, Size_A);
    sort_array(B, Size_B);
    sort_array(C, Size_C);

    printf("\nArrays after sorting:");
    print_array("A", A, Size_A);
    print_array("B", B, Size_B);
    print_array("C", C, Size_C);

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
    int A[Size];
    if (!get_array("A", A, Size))
    {
        return -1;
    }

    printf("\nArray before changes:");
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

    printf("\nArray after changes:");
    print_array("A", A, Size);

    printf("\n");
    system("pause");
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Дан целочисленный массив В (7х11). Определить, сколько в
//    нем пар соседних одинаковых элементов. Элементы считаются сосед-
//    ними, если их индексы в столбцах и/или в строках различаются не
//    более чем на единицу.
//
//    Пример работы:
//    M [3,4]:
//    1 2 3 4
//    1 0 3 0
//    0 1 0 0
//
//    M [3,4]:
//    1       2       3       4
//    1       0       3       0
//    0       1       0       0
//
//    Pairs detected: 8
//    Для продолжения нажмите любую клавишу . . .


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
    for (int i = 1; i < Raws; i++)
        for (int j = 1; j < Columns; j++)
        {
            if (M[i][j] == M[i-1][j])
                pairs++;
            if (M[i][j] == M[i][j-1])
                pairs++;
            if (M[i][j] == M[i-1][j-1])
                pairs++;
            if (M[i-1][j] == M[i][j-1])
                pairs++;
        }
    // check first raw:
    for (int j = 1; j < Columns; j++)
    {
        if (M[0][j] == M[0][j-1])
            pairs++;
    }
    // check first column:
    for (int i = 1; i < Raws; i++)
    {
        if (M[i][0] == M[i-1][0])
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
//    main_4();
do {
      main_4();
} while(1);
    return 0;
}
