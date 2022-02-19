﻿// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "List.h" 
using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    lst::List<int> eda;
    eda.Dump();
    eda.Insert(0,10);
    eda.Dump();
    eda.Insert(1, 20);
    eda.Dump();
    eda.Insert(2, 30);
    eda.Dump();
    eda.Insert(2, 25);
    eda.Dump();
    eda.Insert(0, 5);
    eda.Delete(2);
    eda.PushBack(100);
    eda.PushFront(1);
    //cout << eda.TranslateIndex(4);
    //eda.Sorting();
    //eda.Dump();
    eda.GraphDump();


    lst::List<double> frr;
    frr.PushBack(10);
    frr.GraphDump("frr");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
