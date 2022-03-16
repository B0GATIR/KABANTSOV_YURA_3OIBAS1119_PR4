#include <iostream>
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
    /*Создал таблицу 6х6*/
    unsigned char box[6][6];
    /*Преообразовал каждый символ сообщения в unsigned char*/
    list<unsigned char> message = getUnsignedCharList(text);
    /*Зашифрованное сообщение*/
    string res;
    /*Переменная хранит аски код буквы "А"*/
    int charCode = 192;
    /*Цикл заполняет таблицу 6х6 буквами русского алфавита*/
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
    /*Цикл ище для каждого символа сообщения позицию строки и столбца, которые являются символом шифра*/
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
        /*Проверка, прошёл ли символ шифрофку*/
        if (flag == false)
        {
            res += l;
            res += " ";
        }
    }
    /*Вывод зашифрованного сообщения*/
    cout << "Зашифрованное сообщение:\n" << res;
}

void polebBoxMain()
{
    cout << "Введите сообщение:" << endl;
    cin.ignore();
    string text;
    getline(cin, text);
    /*Создал таблицу 6х6*/
    unsigned char box[6][6];
    /*Преообразовал каждый символ сообщения в unsigned char*/
    list<unsigned char> message = getUnsignedCharList(text);
    /*Зашифрованное сообщение*/
    string res;
    /*Переменная хранит аски код буквы "А"*/
    int charCode = 192;
    /*Цикл заполняет таблицу 6х6 буквами русского алфавита*/
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
    /*Цикл выводит заполненную таблицу 6х6*/
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << box[i][j] << " ";
        }
        cout << endl;
    }
    /*Цикл ище для каждого символа сообщения позицию строки и столбца, которые являются символом шифра*/
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
        /*Проверка, прошёл ли символ шифрофку*/
        if (flag == false)
        {
            res += l;
            res += " ";
        }
    }
    /*Вывод зашифрованного сообщения*/
    cout << "Зашифрованное сообщение:\n" << res;
}

void codeTrisimusMain()
{
    cout << "Не работает!" << endl;
}

void codePlayfairMain()
{
    cout << "Не работает!" << endl;
}

void codeOmofonMain()
{
    cout << "Введите сообщение:" << endl;
    cin.ignore();
    string text;
    getline(cin, text);
    /*Создал массив букв русского алфавита*/
    unsigned char ABC[31];
    /*Создал таблицу 31х2 с омофонами для каждой буквы*/
    int omofonABC[31][2];
    /*Преообразовал каждый символ сообщения в unsigned char*/
    list<unsigned char> message = getUnsignedCharList(text);
    /*Зашифрованное сообщение*/
    string res;
    /*Переменная хранит аски код буквы "А"*/
    int charCode = 192;
    /*Цикл заполняет массив буквами русского алфавита*/
    for (int i = 0; i < 31; i++)
    {
        ABC[i] = charCode;
        charCode++;
    }

    /*Цикл заполняет таблицу омофонами*/
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            omofonABC[i][j] = rand() % 200 + 100;
        }
        charCode++;
    }
    /*Цикл выводит список букв русского алфавита и соответствующие им строки таблицы с омофонами*/
    for (int i = 0; i < 31; i++)
    {
        cout << static_cast<unsigned char>(ABC[i]) << " ";
        for (int j = 0; j < 2; j++)
        {
            cout << omofonABC[i][j] << " ";
        }
        cout << endl;
    }
    /*Цикл ищет в списке шифруемый символ и подбирает случайный омофон*/
    for (auto& l : message)
    {
        bool flag = false;
        for (int i = 0; i < 31; i++)
        {
            if (l == ABC[i])
            {
                flag = true;
                res += to_string(omofonABC[i][rand() % 2 + 0]) + " ";
            }
        }
        /*Проверка, прошёл ли символ шифрофку*/
        if (flag == false)
        {
            res += l;
            res += " ";
        }
    }
    /*Вывод зашифрованного сообщения*/
    cout << "Зашифрованное сообщение:\n" << res;
}

void codeVishenerMain()
{
    cout << "Введите сообщение:" << endl;
    cin.ignore();
    string text;
    getline(cin, text);
    cout << "Введите ключ:" << endl;
    string key;
    getline(cin, key);
    /*Создал динамический таблицу 32хkey.size() + 1*/
    unsigned char **tableV = new unsigned char*[33];
    for (int i = 0; i < 33; i++)
    {
        tableV[i] = new unsigned char[key.size() + 1];
    }
    /*Преообразовал каждый символ сообщения в unsigned char*/
    list<unsigned char> message = getUnsignedCharList(text);
    list<unsigned char> parol = getUnsignedCharList(key);
    /*Зашифрованное сообщение*/
    string res;
    /*Переменная хранит аски код буквы "А"*/
    int charCode = 192;
    /*Цикл заполняет нулевую массив буквами русского алфавита*/
    for (int i = 1; i < 33; i++)
    {
        tableV[0][i] = charCode;
        charCode++;
    }
    for (int i = 1; i < key.size() + 1; i++)
    {
        tableV[i][0] = static_cast<unsigned char>(key[i - 1]);
    }
    /*Заполнение таблицы*/
    for (int i = 1; i < key.size() + 1; i++)
    {
        charCode = tableV[i][0] + 1;
        for (int j = 1; j < 33; j++)
        {
            if (charCode > 223)
            {
                charCode = 192;
            }
            tableV[i][j] = charCode;
            charCode++;
        }
    }
    int i = 0;
    int newRange = message.size() - parol.size();
    auto j = parol.begin();
    while (i < newRange)
    {
        if (j == parol.end())
        {
            j = parol.begin();
        }
        parol.push_back(*j);
        advance(j, 1);
        i++;
    }
    /*Вывод таблицы*/
    for (int i = 0; i < key.size() + 1; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            cout << tableV[i][j] << " ";
        }
        cout << endl;
    }
    /*Вывод сообщения и пароля*/
    cout << endl;
    for (auto& i : message)
    {
        cout << i;
    }
    cout << endl;
    for (auto& i : parol)
    {
        cout << i;
    }
    /**/
    i = 0;
    auto mI = message.begin();
    auto pI = parol.begin();
    while (i < message.size())
    {
        for (int j = 1; j < 33; j++)
        {
            if (*mI == tableV[0][j])
            {
                for (int l = 1; l < key.size() + 1; l++)
                {
                    if (*pI == tableV[l][0])
                    {
                        res += tableV[l][j];
                        break;
                    }
                }
                break;
            }
        }
        if (*mI < 192 || *mI > 223)
        {
            res += static_cast<unsigned char>(*mI);
        }
        advance(mI, 1);
        advance(pI, 1);
        i++;
    }
    cout << endl << endl;
    cout << "Зашифрованное сообщение:\n" << res;
}

int main()
{
    //Команды для корректного отображения русских символов
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int ans;

    cout << "Выберите нужный шифр. \n\nШифр Цезаря+ [1]\nЛозунговый шифр [2]\nПолибианский квадрат+ [3]\nШифрующая система Трисемуса [4]\nШифра Playfair [5]\nСистема омофонов+ [6]\nШифр Виженера+ [7]" << endl;
    cin >> ans;

    switch (ans)
    {
    case 1: codeChezarMain(); break;
    case 2: codeLozungMain(); break;
    case 3: polebBoxMain(); break;
    case 4: codeTrisimusMain(); break;
    case 5: codePlayfairMain(); break;
    case 6: codeOmofonMain(); break;
    case 7: codeVishenerMain(); break;
    default: break;
    }

    return 0;
}