#include <stdio.h>
#include <string.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////////
//    � ����� ���������� �������� � ����������� �����������:
//    �������, ��� ��������, ���, ����������� (�������, ������), ���
//    ����������� �� ������. ����� ������ �������� ���������� �����
//    ������. ������� ������ ������� ������������ (�� 28 ���) �
//    ������ ������������.

//////////////////////////////////////////////////////////////////////////////////////////

#define MAX_STUFFS 100
#define MAX_STUFF_LAST_NAME 10

char file_name[] = "data.txt";
char input_format[] = "�������=%s ���_��������=%u ���=%c �����������=%c ���_������=%u";
char output_format[] = "%s,\t %u�.�., ���: %s, �����������: %s, �������� �: %u�.";

// ������ ������ � �����:
//    �������=������� ���_��������=2005 ���=� �����������=� ���_������=2021
//    �������=�������� ���_��������=2001 ���=� �����������=� ���_������=2019
//
//////////////////////////////////////////////////////////////////////////////////////////

struct Stuff
{
    char      last_name[ MAX_STUFF_LAST_NAME ];
    unsigned  birthday_year;
    char      gender;         // M-������� �-�������
    char      education;      // �-������� �-������
    unsigned  job_year;
};

//////////////////////////////////////////////////////////////////////////////////////////

void print_stuff(struct Stuff* pStuff ) {
    if( !pStuff )
        return;

    printf( output_format,
            pStuff->last_name,
            pStuff->birthday_year,
            pStuff->gender == '�'? "�������" : "�������",
            pStuff->education == '�'? "�������" : "������",
            pStuff->job_year );
}

//////////////////////////////////////////////////////////////////////////////////////////

int main_4() {
    setlocale(0,"Russian");

    FILE* input_file;
    input_file = fopen(file_name,"r");
    if (input_file == NULL) {
        printf("\nFailed to open file for reading: %s.", file_name);
        return 1;
    }
    printf("\n%s opened for reading", file_name);

    struct Stuff stuff[ MAX_STUFFS ];

    for (int i=0; i < MAX_STUFFS; i++) {
        if (feof(input_file) == EOF)
            break;

        if (fscanf(input_file, input_format,
            stuff[i].last_name, &stuff[i].birthday_year,
            &stuff[i].gender, &stuff[i].education, &stuff[i].job_year )
            != 5){
            break;
//            printf("\nFailed to read file data (%d).", i+1);
//            return 1;
        }
        printf("\n%d: ", i+1);
        print_stuff( &stuff[i] );
        fgetc(input_file);// skip '\n'
    }

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
