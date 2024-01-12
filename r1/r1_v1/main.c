//1. Набрать текст программы, представленный ниже. Проанализи-
//ровать значения переменных после каждой операции присваивания.
//Проверить порядок выполнения операций в каждом выражении, со-
//держащем несколько операций присваивания, разделив каждый опе-
//ратор-выражение на несколько операторов, выполняемых последова-
//тельно. В функциях ввода и вывода изменить спецификаторы форма-
//та, проанализировать полученные результаты.

#include <stdio.h>
#include <stdlib.h>

int main_1(void)
{
    int a, b = 5, c;
    double x, y = -.5, z;
    printf("a=");
    scanf("%d", &a);
    x = c = a;
    printf("x = c = a : a=%d c=%d x=%f\n",a, c, x);
    a += b;
    printf("a += b : a=%d\n", a);
    x *= b+a;
    printf("x *= b+a : x=%lf\n", x);
    b += a--;
    printf("b += a-- : a=%d b=%d\n", a, b);
    x -= ++c;
    printf("x -= ++c : c=%d x=%lf\n", c, x);
    c = a/b;
    printf("c = a/b : c=%4d\n",c);
    c = a%b;
    printf("c = a%%b : c=%d\n",c);
    y += (a+1)/a++;
    printf("y += (a+1)/a++ : a=%d y=%.3lf\ty=%.0lf\n",
    a, y, y);
    b = 3*(y-=.6)+2*b+1;
    printf("b = 3*(y-=.6)+2*b+1 : b=%d y=%.1lf\n",
    b, y);
    z = a/2;
    printf("z = a/2 : z = a/2 : z=%lf\n", z);
    z = (double)a/2;
    printf("z = (double)a/2 : z=%lf\n", z);
    y = (x = 5.7)/2;
    printf("y = (x = 5.7)/2 : x=%lf y=%lf\n", x, y);
    y = (int)x/2;
    printf("y = (int)x/2 : y=%f\n", y);
    z = (b-3)/2 - x/5 +(c/=2) + 1/4*z - y++ + ++b/3.;
    printf("z = (b-3)/2 - x/5 +(c/=2) + 1/4*z - y++ \
    + ++b/3. :\n\a=%d b=%d c=%d x=%lf y=%lf z=%lf\n",
    a,b,c,x,y,z);
    system("pause");
    return 0;
}

//2. Написать программу для вычисления значений следующих вы-
//ражений:
//a=5, c=5
//a=a+b-2
//c=c+1, d=c-a+d
//a=a*c, c=c-1
//a=a/10, c=c/2, b=b-1, d=d*(c+b+a)
//Выражения, записанные в одной строке, записывать одним опе-
//ратором-выражением. Переменные c и d объявить как целые, пере-
//менные a и b – как вещественные. Значения переменных b и d вводить
//с клавиатуры. После вычисления каждого выражения выводить на
//экран значения всех переменных.

int main_2(void)
{

}

//3. Набрать текст нижеприведенной программы. Проанализиро-
//вать выдаваемые программой результаты. Объяснить, почему они
//именно такие.

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main_3(void)
{
    char c;
    unsigned char uc;
    int i;
    unsigned u;
    short s;
    long l;
    float f;
    double d;
    printf("sizeof(c)=%d\tsizeof(uc)=%d\nsizeof(i)\
    =%d\tsizeof(u)=%d\tsizeof(s)=%d\tsizeof(l)=%d\n\
    sizeof(f)=%d\tsizeof(d)=%d\n\n", sizeof(c), sizeof(uc),
    sizeof(i), sizeof(u), sizeof(s), sizeof(l), sizeof(f),
    sizeof(d));
    uc=c=CHAR_MAX;
    printf("CHAR_MAX : c=%d uc=%d\n", c, uc);
    c++; uc++;
    printf("CHAR_MAX+1 : c=%d uc=%d\n", c, uc);
    uc=c=CHAR_MIN;
    printf("CHAR_MIN : c=%d uc=%d\n", c, uc);
    c=uc=UCHAR_MAX;
    printf("UCHAR_MAX : c=%d uc=%d\n", c, uc);
    c++; uc++;
    printf("UCHAR_MAX+1 : c=%d uc=%d\n", c, uc);
    uc=c=-5;
    printf("-5 : c=%d uc=%d\n", c, uc);
    c=-5; uc=5;
    printf("char and unsigned char -5>5 : %d\n\n",
    c>uc);
    c=s=SHRT_MAX;
    uc=s;
    printf("SHRT_MAX : c=%d uc=%d s=%d\n", c, uc, s);
    s++;
    printf("SHRT_MAX+1 : s=%d\n", s);
    c=s; uc=s;
    printf("%d : c=%d uc=%d\n", SHRT_MIN, c, uc);
    s=0; c=s; uc=s;
    printf("0 : c=%d uc=%d s=%d\n", c, uc, s);
    i=INT_MAX;
    l=i; u=i;
    printf("INT_MAX : i=%d u=%u l=%ld\n", i, u, l);
    i++; l++; u++;
    printf("INT_MAX+1 : i=%d u=%u l=%ld\n", i, u, l);
    i=INT_MIN;
    l=i; u=i;
    printf("INT_MIN : i=%d u=%u l=%ld\n", i, u, l);
    u=UINT_MAX;
    i=u; l=u;
    printf("UINT_MAX : i=%d u=%u l=%ld\n", i, u, l);
    u=i=-5;
    printf("-5 : i=%d u=%u\n", i, u);
    i=-5; u=5;
    printf("int and unsigned int -5>5 : %d\n", i>u);
    c=-5; u=5;
    printf("char and unsigned int -5>5 : %d\n\n",
    c>u);
    i=5.1;
    printf("i=5.1 : i=%d\n", i);
    i=5.9;
    printf("i=5.9 : i=%d\n", i);
    d=f=FLT_MAX;
    printf("FLT_MAX : f=%g d=%g\n", f, d);
    d=f=FLT_MIN;
    printf("FLT_MIN : f=%g d=%g\n", f, d);
    d=f=FLT_EPSILON;
    printf("FLT_EPSILON : f=%g d=%g\n", f, d);
    f=1e10;
    printf("1e10 : f=%f\n", f);
    f=1e11;
    printf("1e11 : f=%f\n", f);
    f=1234567890;
    printf("1234567890 : f=%f\n", f);
    d=DBL_MAX;
    printf("DBL_MAX : d=%g\n", d);
    d=DBL_MIN;
    printf("DBL_MIN : d=%g\n", d);
    d=DBL_EPSILON;
    printf("DBL_EPSILON : d=%g\n", d);
    d=1e15+1;
    printf("1e15+1 : d=%lf\n", d);
    d=1e16+1;
    printf("1e16+1 : d=%lf\n", d);
    f=10000*100000;
    f+=1;
    f-=4*250000000;
    printf("1 : f=%f\n", f);
    f=10000*100000+1-4*250000000;
    printf("1 : f=%f\n", f);
    d=10000*100000+1-4*250000000;
    printf("1 : d=%lf\n", d);
    d=1e20*1e20+1000-1e22*1e18;
    printf("1000 : d=%lf\n", d);
    system("pause");
    return 0;
}

int main(void)
{
    main_1();
    main_2();
    main_3();
    return 0;
}
