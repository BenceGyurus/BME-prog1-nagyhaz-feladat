#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"

void* memory_error()
{
    perror("Nem sikerült memóriát lefoglalni");
    return NULL;
}

/*
@breif A függvény egy paraméterül kapott stringet másol, ennek dinamikusan foglalja le memóriacímét
@param string A másolandó string
@return A másolt karakter memóriacíme
*/

char* masolat(char* string)
{
    int length = strlen(string);
    char* memoria = malloc(length + 1);
    if (memoria == NULL) return memory_error();
    strcpy(memoria, string);
    memoria[length] = '\0';
    return memoria;
}

/*
@brief A függvény egy paraméterül kapott stringet és egy szintén paraméterül kapott karaktert összefűz egy és ezeknek egy új memória címet foglal le
@param nem kötelezően dinamikusan foglalat `char` pointer, amihez szeretnénk a karaktert hozzáfűzni
@param new_char a hozzáfűzendő karakter
@return Az összefűzött string első elemére mutató pointer
*/

char* add_Char_Without_Free_Memory(const char* path, char new_char) {
    int len = strlen(path);
    char* new_path = malloc(sizeof(char)*(len + 2));
    if (!new_path) return memory_error();
    strcpy(new_path, path);
    new_path[len] = new_char;
    new_path[len + 1] = '\0';

    return new_path;
}

/*
@brief A függvény egy paraméterül kapott stringet és egy szintén paraméterül kapott karaktert összefűz egy és ezeknek egy új memória címet foglal le
@param string1 Az a string amihez szeretnénk hozzáfűzni a karaktert, ennek egy dinamukusan foglalt memóriacímnek kell lennie
@param character A string1-hez hozzáfűzendő karakzer
@return Az összefűzött karakterlánc pointere
 */

char* add_Char_To_String(char* string1, char character){
    int i = strlen(string1);
    char* result = malloc((i + 2) * sizeof(char));
    if (result == NULL) return memory_error();
    strcpy(result, string1);
    free(string1);
    result[i] = character; result[i+1] = '\0';
    return result;
}

/*
@brief Addig olvas be a függvény a szabványos bemenetről amíg a felhasználó nem üt enter-t, dinamikusan foglalja le ezt
@return A beolvasott karakterlánc legelső elemének pointere
*/

char* read_From_Input()
{
    char be;
    int length = 1;
    char* result = malloc(length * sizeof(char));
    if (result == NULL) return memory_error();
    result[0] = '\0';
    while (scanf("%c", &be) != EOF && be != '\n')
    {
        result = add_Char_To_String(result, be);
        if (result == NULL)
            return NULL;
    }
    return result;
}
