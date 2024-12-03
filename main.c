#include "debugmalloc.h"
#include <stdio.h>
#include "functions.h"
#include "morse.h"
#include "binary_tree.h"


// Ebben a felsorolás típusban tárolja a program, hogy éppen melyik funkció van kiválasztva.
typedef enum FunctionEnum {
    encode,
    decode,
    none
} FunctionEnum;

/*
@brief Vezérli a programot, innen indít minden függvényt
@param numberOfArgs megadja hány elemű lesz az `arguments` karakter típusú pointer pointere
@param terminálból kapott paraméterek tömbje
@return 0;
 */

int main(int numberOfArgs, char** arguments)
{
    int morse_Length;
    Morse* morse_Array = read_Morse_From_File("szotar.txt", &morse_Length);
    FunctionEnum inFunction = none;
    if (morse_Array != NULL && morse_Length > 0)
    {

        Node* tree = forward_Morse_Data(morse_Array, morse_Length);
        if (numberOfArgs == 1)
        {
            printf("\nEnkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: ");
            char* function = read_From_Input();
            while ((strcmp(function, "/e") && inFunction == none) || inFunction != none)
            {
                if (toupper(function[0]) == 'E' && function[1] == '\0' && inFunction == none) inFunction = encode;
                else if (toupper(function[0]) == 'D' && function[1] == '\0' && inFunction == none) inFunction = decode;
                else if (inFunction == encode) {encode_Morse(tree, function);inFunction = none; }
                else if (inFunction == decode) {decode_Morse(tree, function); inFunction = none;}
                else
                {
                    printf("Kérem válasszon funkciót!\n");
                }
                if (inFunction == none) printf("\nEnkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: ");
                else if (inFunction == encode) printf("\nÍrja be a kódolandó szöveget >>");
                else printf("\nÍrja be a dekódolandó morze kódot >>");

                free(function);
                function = read_From_Input();
                if (function == NULL) printf("Nem sikerült beolvasni a bemenetet\n");
            }
            free(function);
        }
        else
        {   if (numberOfArgs == 3)
        {
            if (arguments[1][0] && arguments[1][1] && arguments[1][0] == '-'  && toupper(arguments[1][1]) == 'E') { encode_Morse(tree, arguments[2]);}
            else if (arguments[1][0] && arguments[1][1] && arguments[1][0] == '-'  && toupper(arguments[1][1]) == 'D') { decode_Morse(tree, arguments[2]);}
            else printf("\nHibás bemenet\n");
        }else printf("\nHibás bemenet\n");
        }
        free_Tree(tree);
        free_Morse(morse_Array, morse_Length);
    }
    return 0;
}
