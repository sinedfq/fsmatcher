#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "functions.h"
// форматирование SHIFT + ALT + F

struct dirent* dir;

const char mass[3] = {'*', '\\', '.'};

int reverseLoop(
        char* string,
        char* buffer,
        int len) // функция поиска обратных петель для конечного автомата
{
    if (len > strlen(buffer)) { //если длина len больше чем длина буффера то выход
        return 0;
    }
    int resultMatch = 0; // текущее состояние
    char suffix[len]; // суффикс, т.е то кол-во len символов с конца строчки
                      // buffer
    char preffix[len]; // преффикс, т.е первые len символов строчки string
    int startElement = strlen(buffer) - len; // начальный элемент суффикса
    copyToElement(len, preffix, string); // копируем len символов из начала строки
    copyFromElement(startElement, suffix, buffer); // копируем с startElement до конца строки
    if (compareStrings(preffix, suffix) == 1) { // функция compareStrings - сравнение 2 строчек, если строчки совпадают
        resultMatch = len; // то мы присваиваем len нашему состоянию
    }
    len++; // далее мы проверяем максимальную длину, т.е проверяем наш суффикс и
           // преффикс с еще 1 элементом
    int temp = reverseLoop(string, buffer, len);
    if (temp > resultMatch) { // если после рекурсии нашлось значение, которое
                              // больше текущего
        resultMatch = temp; // то мы присваиваем это значение resultMatch
    }
    return resultMatch;
}

int smatcher( // функция smatcher сравнивает строку из файла с конечным
              // автоматом
        int stateCount, // кол-во состояний
        int alphlen,    // кол-во символов алфавита
        int KA[stateCount][alphlen], // сам конечный автомат
        char* pattern,               // строка из файла
        char* alph)                  // алфавит
{
    int curState = 0;
    int maxCurState = 0;
    int index;
    for (int i = 0; i < strlen(pattern); i++) {
        index = getIndex(
                pattern[i],
                alph); // тут мы получаем index текущего символа из строки файла
        curState = KA[curState]
                     [index]; // присваиваем это значение к текущему состоянию
        if (curState == stateCount) { // если мы прошли все состояния, то выход
            return curState;
        } else {
            if (curState
                > maxCurState) { // тут идет проверка на макисмальное состояние
                maxCurState = curState;
            }
        }
    }
    return maxCurState;
}

int tableCreate(
        int count,
        char alph[count],
        char* pattern) // создание конечного автомата
{
    int alphLen = strlen(alph); // длина алфавита

    int stateCount = strlen(pattern); // кол-во состояний

    int KA[stateCount][alphLen]; // конечный автомат

    for (int i = 0; i < stateCount; i++) { // инициализация массива
        for (int j = 0; j < alphLen; j++) {
            KA[i][j] = 0;
        }
    }
    int i = 0;
    char* buffer = malloc(sizeof(char) * 100); // строка, в которую мы будем помещать строку с неправильным символом
    for (i = 0; i < stateCount; i++) { // проходим по каждому состоянию
        copyToElement(i, buffer, pattern); // копируем символы из строки в буффер
        int resultMatch = 0;
        for (int j = 0; j < alphLen; j++) { // проходим по буквам алфавита
            if (alph[j] == pattern[i]) { // если буква алфавита равна букве шаблона, то
                KA[i][j] = i + 1;       // мы делаем переход на следующее состояние 
                buffer[i] = alph[j];
            } else {
                buffer[i] = alph[j]; // добавление неверной буквы алфавита
                for (int element = 1; element < strlen(buffer); element++) {
                    int len = 1; // кол-во элементов которые мы будем далее сравнивать 
                    KA[i][j] = reverseLoop(pattern, buffer, len); // делаем обратные петли для текущего buffer'a
                }
            }
        }
    }
    printf("\n");
    for (int i = 0; i < alphLen; i++) {
        for (int j = 0; j < stateCount; j++) {
            printf("%-3d ", KA[j][i]); // вывод получившегося конечного автомата
        }
        printf("\n");
    }
}

void alphCreate(char* pattern) // создание алфавита из букв шаблона
{
    int len = strlen(pattern) - 1; // -1 добавлено из-за символа \0
    char alph[len];
    int count = 0;

    for (int i = 0; i < len; i++) {
        char symbol = pattern[i];
        if (alreadyExist(symbol, alph)) { // тут происходит проверка если этот
                                          // символ уже в массиве
            continue;
        }

        alph[count] = symbol; // если нет то добавляем и добавляем count (длина
                              // массива который у нас получиться)
        count++;
    }

    char alphResult[count];
    int i;
    for (i = 0; i < count; i++) {
        alphResult[i] = alph[i]; // формирование нужного нам массива
    }
    alphResult[i] = '\0';

    // for(int i = 0; i < count; i++){
    //     printf("SYMBOL [%c] INDEX[%d]\n", alphResult[i], i);
    // }

    tableCreate(count, alphResult, pattern);
}


char readFile(
        char* patternsFile,
        char* way,
        FILE** fp) // функция, которая считывает данные из файла и записывает их
                   // в переменную patternsFile
{
    while (!feof(*fp)) {
        fgets(patternsFile, sizeof(char) * 100, *fp);
    }
}

void inputWay(char* way, char* pattern) // Функция которая проверяет папка это или нет
{
    DIR* directory = opendir(way);
    if (directory
        != NULL) { // эти это каталог, то функция пишет полное имя каталога
        printf("Каталог: %s\n", way);
        while ((dir = readdir(directory))
               != NULL) { // начинает считывать файла, пока не дойдет до
                          // последнего
            if (strcmp(dir->d_name, ".") != 0
                && strcmp(dir->d_name, "..") != 0) {
                inputWay(concat(way, dir->d_name), pattern); // далее вызывает эту же функцию заново, но с
                                  // конкатенированным полным именем до файла
            }
        }
        closedir(directory);
    } else {
        FILE* fp = fopen(way, "r");
        if (fp != NULL) { // если удалось открыть файл
            char* patternsFile; // то мы создаем переменную patternsFile
            patternsFile = malloc(sizeof(char) * 100);
            printf("Отдельный файл: %s\n", way);
            readFile(patternsFile,way,&fp); // и далее вызываем функцию, которая считывает информацию из этого файла
            
        }
        fclose(fp);
    }
}

int main(void)
{
    char* way;
    way = malloc(sizeof(char) * 100);

    char* pattern;

    printf("Введите подсроку:");
    fgets(pattern, sizeof(char) * 100, stdin);

    int* alphabet = malloc(sizeof(int) * 100);
    alphCreate(pattern);

    printf("Введите путь: ");
    scanf("%s", way);
    inputWay(way, pattern);
}