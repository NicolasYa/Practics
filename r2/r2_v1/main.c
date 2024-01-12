#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// for test only!
#define system(a) printf("\n")

double factorial( int n )
{
    return n < 2 ? 1 : ( n * factorial( n - 1 ) );
}

int get_int_value( char* ptext, int* pvalue )
{
    if( ptext == 0 || pvalue == 0 )
        return 0;

    printf( "\nEnter %s = ", ptext );
    if( scanf( "%d", pvalue ) != 1 )
    {
        printf( "Error: incorrect value entered\n" );
        while( getchar() != '\n');
        return 0;
    }
    return 1;
}

int get_double_value( char* ptext, double* pvalue )
{
    if( ptext == 0 || pvalue == 0 )
        return 0;

    printf( "\nEnter %s = ", ptext );
    if( scanf( "%lf", pvalue ) != 1 )
    {
        printf( "Error: incorrect value entered\n" );
        while( getchar() != '\n');
        return 0;
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    программе вычислить значение функции, используя
//    условную операцию «?:».

int main_1()
{
    int x = 0;
    int y = 0;
    if( !get_int_value( "integer x", &x ) || !get_int_value( "integer y", &y ) )
        return -1;

    int f_xy;
    f_xy = x > 0 ? (x+y) : ( x <=0 ? ( y < 0 ? (x*y) : (5*x) ) : (5*x) );
    printf( "x=%d, y=%d, f(x,y,)=%d\n", x, y, f_xy );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    вычислить значение по указанной формуле,
//    используя функции математической библиотеки. Перед написанием
//    программы требуется вычислить область определения функции
//    (ООФ), в программе после ввода аргументов проверить их принад-
//    лежность ООФ.

int main_2()
{
    double x = 0;
    if( !get_double_value( "enter non zerro float x", &x ) )
        return -1;

    if( x == 0 )
    {
        printf( "Error: incorrect value entered\n" );
        return -1;
    }

//    double at = atan( 0 );
//    printf( "at=%f\n", at );
//
//    double t = tan( exp(-x) );
//    if( t == 0 )
//    {
//        printf( "Error: incorrect value entered\n" );
//        return -1;
//    }

    double z = pow( x, 2 ) - cos( log( sqrt( fabs(x) ) ) / tan( exp(-x) ) );

    printf( "x=%f, z=%f\n", x, z );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    3. Вывести на экран номер четверти, которой принадлежит точ-
//    ка с координатами (x,y), или указать, какой оси принадлежит эта точ-
//    ка

//  4 | 1
//  --+--
//  3 | 2

int main_3()
{
    int x = 0;
    int y = 0;
    if( !get_int_value( "x", &x ) || !get_int_value( "y", &y ) )
        return -1;

    printf( "\npoint(x=%d,y=%d) in ", x, y );

    if( x == 0 )
    {
        if( y == 0 )
        {
            printf( "Center\n" );
            return 0;
        }
        else
        {
            printf( "axis Y\n" );
            return 0;
        }
    }
    else
    {
        if( y == 0 )
        {
            printf( "axis X\n" );
            return 0;
        }
    }

    int part = 0;

    if( x > 0 )
    {
        if( y > 0 )
            part = 1;
        else
            part = 2;
    }
    else
    {
        if( y > 0 )
            part = 4;
        else
            part = 3;
    }
    printf( "Part %d\n", part );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Ввести с клавиатуры натуральное число N>2. Вывести на
//    экран последовательность вида «S=2*4*6*…*N», если N четное, или
//    «S=1*3*5*…*N», если N нечетное.

int main_4()
{
    int n = 0;
    if( !get_int_value( "enter natural value from [3...]", &n ) )
        return -1;

    if( n <= 2 )
    {
        printf( "Error: incorrect value entered\n" );
        return -1;
    }

    int start_from = ( n%2 == 0 ) ? 2 : 1;

    for( int i = start_from; i < n; i += 2 )
        printf( "%d*", i );

    printf( "%d", n );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//Найти первое число Фибоначчи, большее заданного n (n>1).
//Каждый член последовательности Фибоначчи является суммой двух
//предыдущих: xn = xn-1 + xn-2, x0 = 0, x1 = 1.

int main_5()
{
    int n = 0;
    if( !get_int_value( "enter natural n from [2...]", &n ) )
        return -1;

    if( n < 2 )
    {
        printf( "Error: incorrect value entered\n" );
        return -1;
    }

    int prev = 0;
    int current = 1;
    int fibonachi = 0;

    printf( "0,1," );
    do
    {
        fibonachi = prev + current;
        printf("%d,", fibonachi );
        prev = current;
        current = fibonachi;
    }
    while( fibonachi <= n );

    printf( "\nn=%d, fibonachi=%d\n", n, fibonachi );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    M и N – числитель и знаменатель обыкновенной дроби. Со-
//    ставить программу, позволяющую сократить эту дробь.

int main_6()
{
    int m = 0;
    int n = 0;
    if( !get_int_value( "integer m", &m ) || !get_int_value( "non zerro integer n", &n ) )
        return -1;

    if( n == 0 )
    {
        printf( "Error: incorrect value entered\n" );
        return -1;
    }

    int denominator = 2;
    int new_m = m;
    int new_n = n;
    printf( "\n%d/%d", new_m, new_n );
    do
    {
        if( (new_m/denominator > 0) && (new_m%denominator == 0) &&
            (new_n/denominator > 0) && (new_n%denominator == 0) )
        {
            new_m = new_m/denominator;
            new_n = new_n/denominator;
            printf( "\n%d/%d", new_m, new_n );
        }
        denominator++;
    }
    while( denominator <= new_m && denominator <= new_n );

    printf( "\n\n%d/%d => %d/%d\n", m, n, new_m, new_n );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Вычислить значение суммы бесконечного ряда с
//    точностью до члена ряда, по модулю меньшего 10-4,

double calculate_sum7( double x, double accuracy )
{
    double prev_result = 0;
    double result = 0;
    double delta = 0;
    printf( "Calculating:\n");

    int n = 0;
    do
    {
        prev_result = result;
        result = ( pow( -1, n ) * pow( x, n ) ) / factorial( n );
        if( _isnan( result ) )
        {
            printf( "Error: incorrect value calculated!\n" );
            break;
        }
        delta = fabs( result );
        result += prev_result;
        printf( "%d:\t delta = %.15f,\t result = %.15f\n", n, delta, result );
        n++;
    }
    while( delta > accuracy );

    printf( "Executed %d iterations\n", n );
    return result;
}

int main_7()
{
    const double accuracy = 1E-4;
    double x = 0;
    if( !get_double_value( "float value", &x ) )
        return -1;

    double result = calculate_sum7( x, accuracy );
    printf( "\nValue=%.15f, Accuracy=%.15f\n", x, accuracy );
    printf( "\nCalculated result:\t%.15f\n", result );

    double reference_result = exp( -x );
    printf( "Reference result:\t%.15f\n", reference_result );

    double ref_difference = fabs( result - reference_result );
    printf( "Diff with reference:\t%.15f\n\n", ref_difference );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Вычислить значение суммы бесконечного ряда с заданной точностью 10-6
//    и значение функции (для проверки)

double calculate_sum8( double x, double accuracy )
{
    double prev_result = 0;
    double result = 0;
    double delta = 0;
    printf( "Calculating:\n");

    int n = 0;
    do
    {
        n++;
        prev_result = result;
        result = ( pow( x, n ) * cos( ( n * M_PI ) / 3 ) ) / n;
        if( _isnan( result ) )
        {
            printf( "Error: incorrect value calculated!\n" );
            break;
        }
        delta = fabs( result );
        result += prev_result;
        printf( "%d:\t delta = %.15f,\t result = %.15f\n", n, delta, result );
    }
    while( delta > accuracy );

    printf( "Executed %d iterations\n", n );
    return result;
}

int main_8()
{
    const double accuracy = 1E-6;
    double x = 0;
    if( !get_double_value( "float value in range [0.1 ... 0.8]", &x ) )
        return -1;

    if( x < 0.1 || x > 0.8 )
    {
        printf( "Error: incorrect value range\n" );
        return -1;
    }

    double result = calculate_sum8( x, accuracy );
    printf( "\nValue=%.15f, Accuracy=%.15f\n", x, accuracy );
    printf( "\nCalculated result:\t%.15f\n", result );

    double reference_result = -0.5 * log( 1 - 2 * x * cos( M_PI / 3 ) + pow( x, 2 ) );
    printf( "Reference result:\t%.15f\n", reference_result );

    double ref_difference = fabs( result - reference_result );
    printf( "Diff with reference:\t%.15f\n\n", ref_difference );

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//    Дано целое k > 2. Напечатать все числа из диапазона [2,k], не
//    являющиеся простыми. Простые числа не имеют других делителей,
//    кроме 1 и самого себя.

int main_9()
{
    int k = 0;
    if( !get_int_value( "enter natural value from [3...]", &k ) )
        return -1;

    if( k < 3 )
    {
        printf( "Error: incorrect value entered\n" );
        return -1;
    }

    for( int number = 3; number <= k; number++ )
    {
        int is_simple = 1;
        for( int divider = 2; divider < number; divider++ )
        {
            if( number%divider == 0 )
            {
                is_simple = 0;
                break;
            }
        }
        if( is_simple == 1 )
        {
            printf( "%d\n", number );
        }
    }

    system( "pause" );
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//    main_2();
//    main_3();
//    main_4();
//    main_5();
//    main_6();
//    main_7();
//    main_8();
//    main_9();
do
{
    main_8();
} while(1);
    return 0;
}
