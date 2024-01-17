#include <stdio.h>

int main() {
    FILE *file;
    const int n = 5; // количество чисел
    float numbers[n];
    float sum = 0;
    float average;

    // Открытие бинарного файла для записи
    file = fopen("binary_file.bin", "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    printf("binary_file.bin opened for writing\n");

    // Ввод чисел и запись в бинарный файл
    printf("Enter %d float numbers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%f", &numbers[i]) != 1)
        {
            printf("\nIncorrect value entered");
            return 1;
        }
        sum += numbers[i];
    }

    average = sum / n; // Вычисление среднего арифметического

    // Нормировка компонентов файла вычитанием среднего арифметического
    for (int i = 0; i < n; i++) {
        numbers[i] -= average;
    }

    printf("Average: %.2f\n", average);
    printf("Normalized numbers:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", numbers[i]);
    }
    printf("\n");

    // Запись вещественных чисел в бинарный файл
    if (fwrite(numbers, sizeof(float), n, file) != n) {
        printf("Write to file failed.\n");
        return 1;
    }

    // Закрытие бинарного файла
    fclose(file);

    // Открытие бинарного файла для чтения
    file = fopen("binary_file.bin", "rb");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return 1;
    }
    printf("binary_file.bin opened for reading\n");

    // Чтение содержимого бинарного файла и вывод на экран
    if (fread(numbers, sizeof(float), n, file) != n) {
        printf("Read failed.\n");
        return 1;
    }

    printf("Content of binary_file.bin:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", numbers[i]);
    }
    printf("\n");

    // Закрытие бинарного файла
    fclose(file);
    return 0;
}
