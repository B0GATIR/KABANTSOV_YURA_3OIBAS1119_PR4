﻿#include <iostream>
#include <string>
#include <Windows.h>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <iterator>

using namespace std;

//Преобразуем массив char`ов строки text в динамический массив unsignedText с типом unsigned char
//так как обычный char имеет диапозон от -128 до 128, а unsigbed char от 0 до 255, следовательно удобнее делать преобразования
list<unsigned char> getUnsignedCharList(string text)
{
    list<unsigned char>unsignedText;
    int i = 0;
    do
    {
        unsignedText.push_back(text[i]);
        ++i;
    } while (i < text.size());
    return unsignedText;
}

//Данная процедура производит вывод содержимого контейнеров динамического массива s
void coutUnsignedCharList(list<unsigned char> s)
{
    for (auto i : s)
    {
        cout << static_cast<unsigned char>(i);
    }
}
//Процедура производит шифрование каждого символа в динамическом массив s с заданным ключом n
void codeChezar(list<unsigned char> s, int n, bool sl)
{
    //Если переменная sl = true, то производим шифрование, иначе дешифрование символов динамического масисва s по ключу n
    if (sl)
    {
        //Цикл перебор содержимого каждого контейнера динамического массива s
        for (auto& i : s)
        {
            //Проверка, является ли буква большой
            if (i >= 192 && i <= 223)
            {
                //Условие следит, что при сдвиге на n позиций, например большая буква Ю не превратилась
                //в маленькую а. В случае такой ситуации ASCII-код буквы вычисляется по формуле: 
                //ASCII-код буквы + n - ASCII-код последней большой буквы + (ASCII-код первой большой буквы - 1)
                if (i + n > 223)
                {
                    i = (i + n) - 223 + 191;
                }
                else
                {
                    //Иначе сдвиг на n
                    i = i + n;
                }
            }
            //Проверка, является ли буква маленькой
            if (i >= 224 && i <= 255)
            {
                //Условие следит, что при сдвиге на n позиций, например маленькая буква ю не вышла за 
                //границы таблицы ASCII. В случае такой ситуации ASCII-код буквы вычисляется по формуле: 
                //ASCII-код буквы + n - ASCII-код последней маленькой буквы + (ASCII-код первой маленькой буквы - 1)
                if (i + n > 255)
                {
                    i = (i + n) - 255 + 223;
                }
                else
                {
                    //Иначе сдвиг на n
                    i = i + n;
                }
            }
        }
    }
    else
    {
        //Цикл перебор содержимого каждого контейнера динамического массива s
        for (auto& i : s)
        {
            //Проверка, является ли буква большой
            if (i >= 192 && i <= 223)
            {
                //Условие следит, что при сдвиге на n позиций, например большая буква А не вышла по значению ASCII-кода
                //за 192. В случае такой ситуации ASCII-код буквы вычисляется по формуле: 
                //(ASCII-код последней большой буквы + 1) - (ASCII-код первой большой буквы - (ASCII-код буквы - n))
                if (i - n < 192)
                {
                    i = 224 - (192 - (i - n));
                }
                else
                {
                    //Иначе сдвиг на n
                    i = i - n;
                }
            }
            //Проверка, является ли буква маленькой
            if (i >= 224 && i <= 255)
            {
                //Условие следит, что при сдвиге на n позиций, например маленькая буква А не вышла по значению ASCII-кода
                //за 224. В случае такой ситуации ASCII-код буквы вычисляется по формуле: 
                //(ASCII-код последней маленькой буквы + 1) - (ASCII-код первой маленькой буквы - (ASCII-код буквы - n))
                if (i - n < 224)
                {
                    i = 256 - (224 - (i - n));
                }
                else
                {
                    //Иначе сдвиг на n
                    i = i - n;
                }
            }
        }
    }

    coutUnsignedCharList(s);
}

void codeChezarMain() {
    string text;
    int key;
    int ans;
    bool selector = true;

    cout << "Производить шифрование [1] или дешифрование [0]?" << endl;
    cin >> ans;
    cin.ignore();
    if (ans == 0)
    {
        selector = false;
        cout << "Введите сообщение которое хотите дешифровать:" << endl;
        getline(cin, text);
    }
    else
    {
        cout << "Введите сообщение которое хотите зашифровать:" << endl;
        getline(cin, text);
    }

    cout << "Введите ключ " << endl;
    cin >> key;
    //Преобразование массива char`ов строки text в динамический массив unsignedText с типом unsigbed char
    list <unsigned char>unsignedText = getUnsignedCharList(text);
    //Производим шифрование или дешифрование
    codeChezar(unsignedText, key, selector);
}

void codeLozungMain()
{
    cout << "Не работает!" << endl;
}

void polebBox()
{
    cout << "Введите сообщение:" << endl;
    cin.ignore();
    string text;
    getline(cin, text);

    unsigned char box[6][6];
    list<unsigned char> message = getUnsignedCharList(text);
    string res;

    int charCode = 192;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (charCode < 224)
            {
                box[i][j] = charCode;
            }
            else
            {
                box[i][j] = 0;
            }
            charCode++;
        }
    }

    for (auto& l : message)
    {
        bool flag = false;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (l == box[i][j])
                {
                    res += to_string(i + 1) + to_string(j + 1) + " ";
                    flag = true;
                }
            }
        }
        if (flag == false)
        {
            res += l;
            res += " ";
        }
    }

    cout << res;
}

int main()
{
    //Команды для корректного отображения русских символов
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int ans;

    cout << "Выберите нужный шифр. \n\nШифр Цезаря [1]\nЛозунговый шифр [2]\nПолибианский квадрат [3]" << endl;
    cin >> ans;

    switch (ans)
    {
    case 1: codeChezarMain(); break;
    case 2: codeLozungMain(); break;
    case 3: polebBox(); break;
    default: break;
    }

    return 0;
}