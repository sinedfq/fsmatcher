#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char* concat(char* str1, char* str2)
{
    char* strResult;
    strResult = malloc(sizeof(char) * 100);
    snprintf(
            strResult,
            sizeof(char) * 100,
            "%s/%s",
            str1,
            str2); // конкатенация строк way и dir->d_name и сохранение их в
                   // переменную temp, для получения полного имени файла
    return strResult;
}

int checkValid(char *string)
{
    for(int i = 0; i < strlen(string); i++){
        if(string[i] == '*' && i != 0){
            if (string[i-1] != string[i] && string[i+1] != string[i]){
                return 1;
            }
        }
    }
}

int compareStrings(char* str1, char* str2) // функция сравнения строк
{
    int flag = 0;
    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] == str2[i]) {
            flag = 1;
        } else {
            return 0;
        }
    }
    return flag;
}

int alreadyExist(
        char symbol,
        char* alph) // функция, которая проверяет если ли элемент в алфавите
{
    for (int i = 0; i < strlen(alph); i++) {
        if (alph[i] == symbol) {
            return 1;
        }
    }
    return 0;
}

int getIndex(
        char symbol,
        char* alhp) // функция, которая возвращает индекс элемента в алфавите
{
    for (int i = 0; i < strlen(alhp); i++) {
        if (symbol == alhp[i]) {
            return i;
        }
    }
}

void copyFromElement(int startElement, char* to, char* from)
{
    for (int k = startElement; k < strlen(from); k++) {
        to[k - startElement] = from[k];
    }
}

void copyToElement(int finalElement, char* to, char* from)
{
    for (int k = 0; k < finalElement; k++) {
        to[k] = from[k];
    }
}