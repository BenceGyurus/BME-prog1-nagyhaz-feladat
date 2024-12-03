#include "functions.h"
#include <stdbool.h>
#include "binary_tree.h"
#include "morse.h"
#include <stdlib.h>
#include <stdio.h>
#include "debugmalloc.h"


/*
@brief lemásolja a paraméterül kapott Morse struktúrát egy új dinamikisan foglalt memóriacímre
@param a lemásolandó Morse struktúra
return az új memóriacím
*/

Morse morse_cpy(Morse morse)
{
    Morse new_Morse;
    new_Morse.key = morse.key;
    new_Morse.value = masolat(morse.value);
    free(morse.value);
    return new_Morse;
}

/*
@brief egy dinamukisa foglalt Morse struktúrájú tömböt és egy Morse struktúrát fűz össze egy új dinamukusan foglalt tömbben
@param a meglévő tömb pointere
@param a hozzáfűzendő Morse struktúra
@return az új tömb memóriacíme
*/

Morse* morse_Linked_List(Morse* pointer, int length, Morse new_Morse){
    Morse* new_Morse_Array = malloc(sizeof(Morse)*(length+1));
    for (int i = 0; i < length; i++)
    {
        new_Morse_Array[i] = morse_cpy(pointer[i]);
    }
    free(pointer);
    new_Morse_Array[length] = morse_cpy(new_Morse);
    return new_Morse_Array;
}


/*
@brief A függvény egy karakterláncból csinál `Morse` típusú struktúrát, ezt dinamukisan foglalja le
@param A paraméterként kapott karakterláncot úgy bontja szét, hogy a struktúra kulcsa (`key`) az első nem space karakter lesz, majd minden ezt követő nem space karakter a string végéig az értéke (`value`) lesz a struktúrának
@return Az elkészített Morse struktúrára memóriacíme
*/

Morse create_Morse(char* string)
{
    Morse morse;
    morse.value = malloc(1 * sizeof(char));
    if (morse.value == NULL) return morse;
    morse.value[0] = '\0';
    bool key = false;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ' && !key)
        {
            key = true;
            morse.key = string[i];
        }else if (key == true && string[i] != ' ') morse.value = add_Char_To_String(morse.value, string[i]);
    }
    return morse;
}

/*
@brief felszabadítja a morse struktúrából álló dinamikusan foglalt tömböt és a bennük lévő dinamikusa foglalt karakterláncot
@param morse_Array a felszabadítandó karakterlánc
@param length a tömb hossza 
*/

void free_Morse(Morse* morse_Array, int length)
{
    for (int i = 0; i<length; i++)
    {
        free(morse_Array[i].value);
    }
    free(morse_Array);
}


/*
@breif Végigmegy a függvény a paraméterül kapott karakterlánc össze karakterén megkeresi a bináris fában a neki megfelelő morse kódot
@param morse_Tree bináris fa, amiben szeretnénk keresni a karaktereket
@param a karakterlánc, amit szerenénk kódolni
*/


void encode_Morse(Node* morse_Tree, char* read_Input)
{
    for (int i = 0; read_Input[i] != 0; i++)
    {
        if (!find_Morze(read_Input[i], morse_Tree)) break;
    }
}

/*
@brief **Ellenőrzi, hogy csak a megengedett karakterek (`.` `-` `/` ` `) vannak-e a paraméternek kapott karakterláncban
@param az ellenőrizendő karakterlánc
@return az ellenőrzés eredménye true: a feltételnek megfelel, false: nem felel meg a feltételnek
*/

bool control_Morse_Code(char* morse)
{
    for (int i = 0; morse[i] != '\0'; i++)
    {
        if (morse[i] != ' ' && morse[i] != '.' && morse[i] != '-' && morse[i] != '/') {printf("A dekódolandó szöveg nem tartalmazhat a szóköztől, '.'-tól '-'-től és '/'-től különböző karaktert." ); return false;}
    }
    return true;
}

/*
@brief Előkészíti a keresést a bináris fában, ellenőrzi a kapott bemenetet
@param tree A bináris fa amiben szeretnénk keresni
@param input A dekódolandó morse kód
 */

void decode_Morse(Node* tree, char* input)
{
    if (control_Morse_Code(input))
    {
        char* word = malloc(sizeof(char));
        word[0] = '\0';
        for (int i = 0; input[i] != '\0'; i++)
        {
            if (input[i] == '/') printf(" ");
            else if (input[i] == ' ' && word[0] != '\0')
            {
                printf("%c", search_In_tree(tree, word));
                free(word);
                word = malloc(sizeof(char));
                word[0] = '\0';
            }else if (input[i] != ' ')
            {
                word = add_Char_To_String(word, input[i]);
            }
        }
        if (word[0] != '\0') printf("%c", search_In_tree(tree, word));
        free(word);
        printf("\n");
    }
}

/*
@brief Beolvas egy fájlt amiből kiolvasott értékekből generál egy tömböt aminek elemei `Morze` struktúrájú elemei vannak, ebből egy tömböt csinál aminek a memóriát dinamikusan foglalja le
@param fileName A beolvasandó fájl neve
@param length a majd visszaadott tömb hosszához kapott pointer, ebbe kerül bele a fájl hossz
@return A fájlból beolvasott, morze kódokat tartalmazó dinamikusan foglalt tömb első elemének memóriacíme
*/

Morse* read_Morse_From_File(char* fileName, int* length){
    FILE* file = fopen(fileName, "r");
    if (file == NULL){ perror("Nem sikerült a fájlt megnyitni"); return NULL;}
    char* data = malloc(1 * sizeof(char));
    if (data == NULL) {return memory_error();}
    data[0] = '\0';
    char readChar;
    Morse* morse_Array = malloc(sizeof(Morse));
    if (morse_Array == NULL) return memory_error();
    int morse_Length = 0;
    while (fread(&readChar, sizeof(char), 1, file) == 1)
    {
        if (readChar != '\n')
        {
            data = add_Char_To_String(data, readChar);
        }else
        {
            Morse morse = create_Morse(data);
            morse_Array = morse_Linked_List(morse_Array, morse_Length, morse);
            free(data);
            data = malloc(1 * sizeof(char));
            if (data == NULL) return memory_error();
            data[0] = '\0';
            morse_Length++;
        }

    }
    *length = morse_Length;
    free(data);
    fclose(file);
    return morse_Array;
}