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

int main_2()
{
    char s[]= "\t12f\n  11x22 44y552";

    char delimiters[]="\n\t ";
    char* max_token = NULL;
    int max_length = 0;

    char* token = strtok(s, delimiters);
    while (token != NULL)
    {
        int length = strlen(token);
        if (length >= max_length)
        {
            max_length = length;
            max_token = token;
        }
        token = strtok( NULL, delimiters );
    }

    if (max_token != NULL)
        printf("\nMax word: \"%s\"\n", max_token);
    else
        printf("\nMax word: not found\n");

//    char max_word[1000]; // word buffer
//    int max_word_length = 0;
//    int word_begin=0;
//    int word_end=0;
//    int string_len = strlen(s);
//    for (int i = 0; i < string_len; i++)
//    {
//        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
//            continue;
//        // word started
//        word_begin = i;
//        for (i++; i < string_len; i++)
//        {
//            char c = s[i];
//            if (c == ' ' || c == '\t' || c == '\n')
//                break; // delimiter detected
//        }
//        word_end = i;
//        int word_length = word_end - word_begin;
//        if (word_length > max_word_length)
//        {
//            max_word_length = word_length;
//            // save max word
//            strncpy(max_word, &(s[word_begin]), max_word_length);
//            max_word[word_end] = '\0';
//        }
//    }
//
//    if( max_word_length > 0 )
//        printf("\nMax word: \"%s\"\n", max_word);
//    else
//        printf("\nMax word: not found\n");

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    main_1();
//    main_2();
//do {
      main_2();
//} while(1);
    return 0;
}
