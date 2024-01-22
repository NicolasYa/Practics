#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////
//    ¬ файле содержатс€ сведени€ о сотрудниках лаборатории:
//    фамили€, год рождени€, пол, образование (среднее, высшее), год
//    поступлени€ на работу. Ќайти самого старшего сотрудника среди
//    мужчин. ¬ывести список молодых специалистов (до 28 лет) с
//    высшим образованием.

//////////////////////////////////////////////////////////////////////////////////////////

#define MAX_STUFFS 100
#define MAX_STUFF_LAST_NAME 15

char file_name[] = "staffs.dat";
char text_input_format[] = "%s %u %c %c %u";
char text_output_format[] = "%15s,\tyear of birth: %u,\tgender: %s,\teducation: %s,\tjob started: %u";

//////////////////////////////////////////////////////////////////////////////////////////

struct Stuff
{
    char      last_name[ MAX_STUFF_LAST_NAME ];
    unsigned  birthday_year;
    char      gender;         // m/f
    char      education;      // h/s
    unsigned  job_year;
};

//////////////////////////////////////////////////////////////////////////////////////////

void input_stuff(struct Stuff* pStuff) {
    if( !pStuff ) {
        return;
    }
    do {
        printf("\nEnter data as:\n"
           "<Last name> <year of birthday> <gender(m/f)> <education(h/m)> <year of job started>\n");
        if (scanf(text_input_format,
                  pStuff->last_name,
                  &pStuff->birthday_year,
                  &pStuff->gender,
                  &pStuff->education,
                  &pStuff->job_year ) == 5 ) {
            break;
        }
        printf("\nIncorrect data, please retry");
    } while (1);
}

//////////////////////////////////////////////////////////////////////////////////////////

void print_stuff(struct Stuff* pStuff) {
    if (!pStuff) {
        return;
    }
    printf( text_output_format,
            pStuff->last_name,
            pStuff->birthday_year,
            pStuff->gender == 'm'? "male" : "female",
            pStuff->education == 'h'? "higher" : "secondary",
            pStuff->job_year );
}

//////////////////////////////////////////////////////////////////////////////////////////

int main_4() {
    struct Stuff stuff[ MAX_STUFFS ];
    int stuff_count = 0;

    printf("\nEnter staff count:\n");
    if (scanf("%u", &stuff_count) != 1 || stuff_count > MAX_STUFFS) {
        printf("\nError: Incorrect count");
        return 1;
    }

    for (int i=0; i < stuff_count; i++) {
        input_stuff(&stuff[i]);
    }

    FILE* output_file = fopen(file_name,"wb");
    if (!output_file) {
        printf("\nFailed to open file for writing: %s.", file_name);
        return 1;
    }

    fwrite( &stuff_count, sizeof stuff_count, 1, output_file);
    fwrite( stuff, sizeof(struct Stuff), stuff_count, output_file);
    if (fclose(output_file) != 0) {
        printf("\nFailed to close file after writing: %s.", file_name);
        return 1;
    }

    FILE* input_file = fopen(file_name,"rb");
    if (!input_file) {
        printf("\nFailed to open file for reading: %s.", file_name);
        return 1;
    }
    printf("\n%s opened for reading", file_name);

    // reset data
    memset( &stuff[0], 0, sizeof(struct Stuff)*stuff_count);
    stuff_count = 0;

    if (fread( &stuff_count, sizeof stuff_count, 1, input_file) != 1) {
        printf("\nFailed to read from: %s.", file_name);
        return 1;
    }

    if( fread( stuff, sizeof(struct Stuff), stuff_count, input_file) != stuff_count) {
        printf("\nFailed to read from: %s.", file_name);
        return 1;
    }

    if (fclose(input_file) != 0) {
        printf("\nFailed to close file after reading: %s.", file_name);
        return 1;
    }

    printf("\nReaded %d records:", stuff_count);

    for (int i=0; i < stuff_count; i++) {
        printf("\n%d: ", i+1);
        print_stuff( &stuff[i] );
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
//do {
      main_4();
//} while(1);
    return 0;
}
