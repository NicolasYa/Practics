#include <stdio.h>

int main() {
    FILE *file;
    int n = 5; // ���������� �����
    float numbers[n];
    float sum = 0;
    float average;

    // �������� ��������� ����� ��� ������
    file = fopen("binary_file.bin", "wb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // ���� ����� � ������ � �������� ����
    printf("Enter %d float numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &numbers[i]);
        sum += numbers[i];
    }

    average = sum / n; // ���������� �������� ���������������

    // ���������� ����������� ����� ���������� �������� ���������������
    for (int i = 0; i < n; i++) {
        numbers[i] -= average;
    }

    // ������ ������������ ����� � �������� ����
    fwrite(numbers, sizeof(float), n, file);

    // �������� ��������� �����
    fclose(file);

    // �������� ��������� ����� ��� ������
    file = fopen("binary_file.bin", "rb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // ������ ����������� ��������� ����� � ����� �� �����
    printf("Content of binary file:\n");
    for (int i = 0; i < n; i++) {
        float num;
        fread(&num, sizeof(float), 1, file);
        printf("%.2f ", num);
    }
    printf("\n");

    // �������� ��������� �����
    fclose(file);

    return 0;
}
