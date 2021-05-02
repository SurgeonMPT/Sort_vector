#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>

using namespace std;

//Структура даты
struct Date {
    int day;
    int month;
    int year;
};

//Структура информации
struct Info {
    char name[255];
    char surname[255];
    char lastname[255];
    char phone[255];
    Date date;
};

//Сортировка вектора От а до я. От 1 до 9 (По номеру ASCII символа)
vector<Info> sortInfo(vector<Info> info_s)
{
    system("cls");

    vector<Info> sort_info_s;
    vector<int> ignore_index;

    bool is_equil = false; //Одинаковые слова
    bool check_index = false; //Проверка заблокированного индекса
    int max = -1; //Максимальный элемент
    int is_last_i = 0;

    //Размерность больше 1
    if (info_s.size() > 1)
    {
        //Пока все элементы не будут рассмотрены
        while (ignore_index.size() < info_s.size())
        {
            max = -1;

            //Прохождение по индексам
            for (int i = 0; i < info_s.size(); i++)
            {
                //Проверка. Рассмотрен ли индекс?
                check_index = false;
                for (int j = 0; j < ignore_index.size(); j++) {
                    if (i == ignore_index.at(j)) {
                        check_index = true;
                    }
                }

                //Сортировка, пока не будут рассмотрены все индексы
                if (check_index == false)
                {
                    if (max == -1)
                    {
                        max = i;
                    }

                    is_equil = true;
                    for (int j = 0; j < sizeof(info_s.at(i).surname) / sizeof(char); j++)
                    {
                        if (j < sizeof(info_s.at(max).surname))
                        {
                            if ((char)info_s.at(max).surname[j] > (char)info_s.at(i).surname[j])
                            {
                                if (is_equil)
                                {
                                    max = i;
                                    is_equil = false;
                                    j = sizeof(info_s.at(i).surname) / sizeof(char);
                                }
                            }
                            else
                            if ((char)info_s.at(max).surname[j] < (char)info_s.at(i).surname[j])
                            {
                                is_equil = false;
                            }
                        }     
                    }

                    //Если surname не дал точного ответа, проверить различие по имени
                    if (is_equil)
                    {
                        for (int j = 0; j < sizeof(info_s.at(i).name) / sizeof(char); j++)
                        {
                            if (j < sizeof(info_s.at(max).name))
                            {
                                if ((char)info_s.at(max).name[j] > (char)info_s.at(i).name[j])
                                {
                                    if (is_equil)
                                    {
                                        max = i;
                                        is_equil = false;
                                        j = sizeof(info_s.at(i).name) / sizeof(char);
                                    }
                                }
                                else
                                    if ((char)info_s.at(max).name[j] < (char)info_s.at(i).name[j])
                                    {
                                        is_equil = false;
                                    }
                            }
                        }
                    }
                }
            }
            
            //В конечном итоге, добавить элемент с учетом сортировки
            sort_info_s.push_back(info_s.at(max));
            ignore_index.push_back(max);
            max = -1;
        }
    }

    return sort_info_s;
}

//Добавление данных
string addInfo()
{
    system("cls");
    string enter;

    //Чтение
    vector<Info> info_s;

    fstream in("Info.txt", ios::binary | ios::in);

    Info info;
    while (in.read((char*)&info, sizeof info))
    {
        info_s.push_back(info);
    }
    in.close();

    cout << "Введите ФИО => ";
    cin >> info.surname >> info.name >> info.lastname;

    cout << "Введите Телефон => ";
    cin >> info.phone;

    cout << "Введите дату рождения => ";
    cin >> info.date.day >> info.date.month >> info.date.year;

    info_s.push_back(info);

    //Запись в файл
    FILE* tpr;
    errno_t file;
    file = fopen_s(&tpr, "Info.txt", "wb+");
    for (int i = 0; i < info_s.size(); i++) {
        fwrite(&info_s.at(i), sizeof(info_s.at(i)), 1, tpr);
    }
    fclose(tpr);

    return enter;
}

//Просмотр данных
string showInfo()
{
    system("cls");

    vector<Info> info_s;

    fstream in("Info.txt", ios::binary | ios::in);

    Info info;
    while (in.read((char*)&info, sizeof(info)))
    {
        info_s.push_back(info);
    }
    in.close();

    info_s = sortInfo(info_s);

    for (int i = 0; i < info_s.size(); i++)
    {
        cout << "<======== Элемент " << i << " ========> " << endl;
        cout << "ФИО: " << info_s.at(i).surname << " " << info_s.at(i).name << " " << info_s.at(i).lastname << endl;
        cout << "Телефон: " << info_s.at(i).phone << endl;
        cout << "Дата рождения: " << info_s.at(i).date.day << "." << info_s.at(i).date.month << "." << info_s.at(i).date.year << endl;
    }

    if (info_s.size() == 0)
    {
        cout << "Список пуст" << endl;
    }
    system("pause");
    return "";
}

//Функция главного меню
string mainMenu() {
    string enter;
    bool check_enter = false;
    vector<string> array_menu = { "Добавить", "добавить", "1", "Список", "список", "2", "Выход", "выход", "3" };

    while (!check_enter)
    {
        system("cls");

        cout << "<========== Меню ==========>" << endl;
        cout << "Добавить" << endl;
        cout << "Список" << endl;
        cout << "Выход" << endl;
        cout << endl << "Ваш выбор => ";
        cin >> enter;

        for (int i = 0; i < array_menu.size(); i++) {
            if (enter == array_menu.at(i)) {
                check_enter = true;
            }
        }
    }
    return enter;
}

//Главная функция
int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    string enter;
    while (enter != "Выход" && enter != "выход" && enter != "3")
    {
        enter = mainMenu();

        if (enter == "Добавить" || enter == "1")
        {
            enter = addInfo();
        }

        if (enter == "Список" || enter == "список" || enter == "2")
        {
            enter = showInfo();
        }
    }

    system("pause");
    return 0;
}