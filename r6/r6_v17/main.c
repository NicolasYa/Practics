#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////////

int replace_N_symbols(char* str, unsigned str_size, unsigned replaced)
{
    if (str == NULL)
    {
        printf("\nInternal error: NULL string");
        return 0;
    }

    if (str_size < 2 * replaced)
    {
        printf("\nError: string too small");
        return 0;
    }

    for(int i = 0, j = str_size - replaced; i < replaced; i++,j++)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }

    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main_1()
{
    const int MaxStringLength = 20;

    char input_string[MaxStringLength + 1];

    printf("\nEnter N:");
    int N = 0;
    if (scanf( "%d", &N ) != 1)
    {
        printf( "Error: incorrect value entered\n" );
        while (getchar() != '\n');
        return 1;
    }
    while (getchar() != '\n');

    printf("\nEnter string >= %d symbols and max of %d symbols\n", N*2, MaxStringLength);
    int i = 0;
    while (i < MaxStringLength)
    {
         char ch = getchar();
         if (ch == '\n')
            break;
         input_string[i++]=ch;
    }
    input_string[i]='\0';

    printf("\nBefore:\"%s\"\n", input_string );

    if (!replace_N_symbols(input_string, strlen(input_string), N ))
    {
        return 1;
    }

    printf("\nAfter: \"%s\"\n", input_string);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main_1_simple()
{
    char s[]= "11x22 33 44y55";
    int N = 2;
    int length = strlen(s);

    if (length < 2*N)
    {
        printf("\nError: string too small");
        return 0;
    }

    printf("\nN: %d\nBefore:\"%s\"\n", N, s );

    for(int i = 0, j = length-N; i < N; i++,j++)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }

    printf("\nAfter: \"%s\"\n", s);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//    main_2();
//do {
      main_1_simple();
//} while(1);
    return 0;
}
