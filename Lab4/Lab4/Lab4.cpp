#include <iostream>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::swap;

// функция проверки ввода
bool enter_check(int &num, int limit)
{
    if (cin.fail() || cin.peek() != '\n' || num > limit || num < 1)
    {
        cout << "Некорректный ввод. Введенное число должно быть целым, большим нуля и меньшим " << limit << endl;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        return false;
    }

    return true;
}

struct Worker
{
    int distance; 
    int id;
    int id_of_taxi; // номер подходящего такси
};

struct Taxi
{
    int tariff;
    int id;
};

int main()
{
    setlocale(LC_ALL, "Russian");

    int number_of_workers = 0;

    while (true)
    {
        cout << "Введите число сотрудников: " << endl;
        cin >> number_of_workers;

        if (enter_check(number_of_workers, 1000))
        {
            break;
        }
    }

    Worker* employees = new Worker[number_of_workers];

    // заполняется поле distance - расстояние до дома, для каждого сотрудника
    for (int i = 0; i < number_of_workers; i++)
    {
        while (true)
        {
            cout << "Введите расстояние для " << i + 1 << " сотрудника: " << endl;
            cin >> employees[i].distance;

            if (enter_check(employees[i].distance, 1000))
            {
                break;
            }
        }
        employees[i].id = i;
    }

    // сортировка по возрастанию расстояния
    for (int i = 0; i < number_of_workers; i++)
    {
        bool flag = true;
        for (int j = 0; j < number_of_workers - (i + 1); j++)
        {
            if (employees[j].distance > employees[j+1].distance)
            {
                flag = false;
                swap(employees[j], employees[j + 1]);
            }
        }
        if (flag)
        {
            break;
        }
    }

    Taxi* tri_desyatki = new Taxi[number_of_workers];

    // заполняется поле tariff для каждого такси
    for (int i = 0; i < number_of_workers; i++)
    {
        while (true)
        {
            cout << "Введите тариф для " << i + 1 << " такси: " << endl;
            cin >> tri_desyatki[i].tariff;

            if (enter_check(tri_desyatki[i].tariff, 10000))
            {
                break;
            }
        }
        tri_desyatki[i].id = i + 1;
    }

    // сортировка по убыванию стоимости тарифа
    for (int i = 0; i < number_of_workers; i++)
    {
        bool flag = true;
        for (int j = 0; j < number_of_workers - (i + 1); j++)
        {
            if (tri_desyatki[j].tariff < tri_desyatki[j+1].tariff)
            {
                flag = false;
                swap(tri_desyatki[j], tri_desyatki[j + 1]);
            }
        }
        if (flag)
        {
            break;
        }
    }

    // сотруднику с наименьшим расстоянием назначается такси с наибольшим тарифом
    for (int i = 0; i < number_of_workers; i++)
    {
        employees[i].id_of_taxi = tri_desyatki[i].id;
    }

    delete [] tri_desyatki;

    int* output = new int[number_of_workers];

    // выставляем номера подходящих такси по порядку 
    for (int i = 0; i < number_of_workers; i++)
    {
        output[employees[i].id] = employees[i].id_of_taxi;
    }

    for (int i = 0; i < number_of_workers; i++)
    {
        cout << output[i] << " ";
    }

    delete [] employees;
    delete [] output;
    _getch();
    return 0;
}