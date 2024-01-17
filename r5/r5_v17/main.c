#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
//    Отсортировать элементы нечетных строк матрицы А (6х7) в
//    порядке убывания, а четных – в порядке возрастания. Определить
//    функцию сортировки последовательности, направление сортировки
//    передавать параметром.

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
//    Даны матрицы В (m,n) и С (n,m). Определить, есть ли в задан-
//    ных матрицах столбцы, содержащие по два отрицательных элемента.
//    Вывести номера таких столбцов. Описать функцию для анализа одно-
//    го столбца.

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
//    метод Ньютона


// Функция для вычисления значения функции cos(x) / (1 + sin^2(x))

double func1(double x) {
    return cos(x) / (1 + pow(sin(x), 2));
}

// Функция для вычисления значения функции x * e^(x+1)
double func2(double x) {
    return x * exp(x+1);
}

// Функция для численного интегрирования методом Ньютона
double newton(double a, double b, int N, double (*f)(double)) {
    double h = (b - a) / N;
    double sum = 0;
    int i;

    for (i = 0; i <= N; i++) {
        double x = a + i * h;
        double y = f(x);

        if (i == 0 || i == N) {
            sum += y;
        } else if (i % 2 == 1) {
            sum += 4 * y;
        } else {
            sum += 2 * y;
        }
    }

    return sum * h / 3;
}

int main_3() {
    double a1 = 5.0;
    double b1 = 1.0;
    double a2 = 3.0;
    double b2 = -1.0;
    int N = 15;
    double result1, result2;

    result1 = newton(a1, b1, N, &func1);
    result2 = newton(a2, b2, N, &func2);

    printf("Integral (cos(x) / (1 + sin^2(x))) / [5, 1] = %f\n", result1);
    printf("Integral x * e^(x+1) / [3, -1] = %f\n", result2);

    return 0;
}



int main()
{
//    main_1();
//    main_2();
//    main_3();
//do {
      main_3();
//} while(1);
    return 0;
}
