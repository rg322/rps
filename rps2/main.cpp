#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "shaker_sort.h"

using namespace std;

//ввод массива с клавиатуры
vector<int> inputArray()
{
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    //очистка буфера после ввода числа
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);
    cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return arr;
}

//генерация случайного массива
vector<int> generateArray()
{
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 100; //числа от 0 до 99

    return arr;
}

//загрузка массива из файла
vector<int> loadArrayFromFile(const string& filename)
{
    ifstream file(filename);
    vector<int> arr;
    int value;

    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл!\n";
        return arr;
    }

    while (file >> value)
        arr.push_back(value);

    file.close();
    return arr;
}

//сохранение массива в файл
void saveArrayToFile(const vector<int>& arr, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Ошибка: не удалось сохранить файл!\n";
        return;
    }

    for (int num : arr)
        file << num << " ";
    file.close();
}

//вывод массива на экран
void printArray(const vector<int>& arr)
{
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

//unit тесты

//функция для проверки отсортированности массива
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

//функция запуска unit-тестов
void runUnitTests() {
    cout << "\n=== UNIT ТЕСТЫ ШЕЙКЕРНОЙ СОРТИРОВКИ ===" << endl;

    int passed = 0;
    int total = 0;

    //тест 1: случайный массив
    total++;
    vector<int> test1 = { 5, 3, 8, 1, 2 };
    shakerSort(test1);
    if (isSorted(test1)) {
        cout << "Тест 1 (случайный массив): ПРОЙДЕН" << endl;
        passed++;
    }
    else {
        cout << "Тест 1 (случайный массив): ОШИБКА" << endl;
    }

    //тест 2: уже отсортированный
    total++;
    vector<int> test2 = { 1, 2, 3, 4, 5 };
    shakerSort(test2);
    if (isSorted(test2)) {
        cout << "Тест 2 (отсортированный): ПРОЙДЕН" << endl;
        passed++;
    }
    else {
        cout << "Тест 2 (отсортированный): ОШИБКА" << endl;
    }

    //тест 3: обратный порядок
    total++;
    vector<int> test3 = { 5, 4, 3, 2, 1 };
    shakerSort(test3);
    if (isSorted(test3)) {
        cout << "Тест 3 (обратный порядок): ПРОЙДЕН" << endl;
        passed++;
    }
    else {
        cout << "Тест 3 (обратный порядок): ОШИБКА" << endl;
    }

    //тест 4: один элемент
    total++;
    vector<int> test4 = { 42 };
    shakerSort(test4);
    if (test4.size() == 1 && test4[0] == 42 && isSorted(test4)) {
        cout << "Тест 4 (один элемент): ПРОЙДЕН" << endl;
        passed++;
    }
    else {
        cout << "Тест 4 (один элемент): ОШИБКА" << endl;
    }

    //тест 5: пустой массив
    total++;
    vector<int> test5 = {};
    shakerSort(test5);
    if (test5.empty()) {
        cout << "Тест 5 (пустой массив): ПРОЙДЕН" << endl;
        passed++;
    }
    else {
        cout << "Тест 5 (пустой массив): ОШИБКА" << endl;
    }

    cout << "===============================" << endl;
    cout << "РЕЗУЛЬТАТ: " << passed << "/" << total << " тестов пройдено" << endl;
    cout << "===============================" << endl;
}

//функция для безопасного ввода числа
int safeInput() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            //если ввод не число - очищаем ошибку и буфер
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод! Пожалуйста, введите число: ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

//основная функция программы
int main()
{
    setlocale(LC_ALL, "Russian");

    int choice;

    //бесконечный цикл меню
    while (true) {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Ввод с клавиатуры" << endl;
        cout << "2. Генерация случайных чисел" << endl;
        cout << "3. Загрузка из файла" << endl;
        cout << "4. Запуск unit-тестов" << endl;
        cout << "5. Выход" << endl;
        cout << "Ваш выбор: ";

        //используем безопасный ввод
        choice = safeInput();

        vector<int> arr;

        if (choice == 1) {
            arr = inputArray();
        }
        else if (choice == 2) {
            arr = generateArray();
        }
        else if (choice == 3) {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            arr = loadArrayFromFile(filename);
        }
        else if (choice == 4) {
            runUnitTests();
            continue;
        }
        else if (choice == 5) {
            cout << "Программа завершена.\n";
            break;
        }
        else {
            cout << "Неверный выбор! Пожалуйста, выберите от 1 до 5.\n";
            continue;
        }

        //проверка что массив не пуст (только для вариантов 1-3)
        if (choice >= 1 && choice <= 3 && arr.empty()) {
            cout << "Массив пуст или не удалось загрузить данные.\n";
            continue;
        }

        //если выбран вариант 1-3 и массив не пуст - сортируем и показываем
        if (choice >= 1 && choice <= 3) {
            cout << "\nИсходный массив:\n";
            printArray(arr);

            //сортировка
            shakerSort(arr);

            cout << "\nОтсортированный массив:\n";
            printArray(arr);

            //предложение сохранить результаты
            cout << "\nСохранить массив в файл? (y/n): ";
            char saveChoice;
            cin >> saveChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (saveChoice == 'y' || saveChoice == 'Y') {
                saveArrayToFile(arr, "sorted.txt");
                cout << "Массив сохранён в файл sorted.txt\n";
            }
        }
    }

    return 0;
}