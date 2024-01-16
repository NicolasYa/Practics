#include <stdio.h>

int main() {
    FILE *file;
    int n = 5; // количество чисел
    float numbers[n];
    float sum = 0;
    float average;

    // Открытие бинарного файла для записи
    file = fopen("binary_file.bin", "wb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // Ввод чисел и запись в бинарный файл
    printf("Enter %d float numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &numbers[i]);
        sum += numbers[i];
    }

    average = sum / n; // Вычисление среднего арифметического

    // Нормировка компонентов файла вычитанием среднего арифметического
    for (int i = 0; i < n; i++) {
        numbers[i] -= average;
    }

    // Запись вещественных чисел в бинарный файл
    fwrite(numbers, sizeof(float), n, file);

    // Закрытие бинарного файла
    fclose(file);

    // Открытие бинарного файла для чтения
    file = fopen("binary_file.bin", "rb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // Чтение содержимого бинарного файла и вывод на экран
    printf("Content of binary file:\n");
    for (int i = 0; i < n; i++) {
        float num;
        fread(&num, sizeof(float), 1, file);
        printf("%.2f ", num);
    }
    printf("\n");

    // Закрытие бинарного файла
    fclose(file);

    return 0;
}
