#include "binary_tree.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"

/*
@brief: A bináris fa által foglalt memóriaterületet szabadítja fel
@param: tree: A felszabadítandó fa
*/

void free_Tree(Node* tree)
{
    if (tree == NULL) return;
    free_Tree(tree->left);
    free_Tree(tree->right);
    free(tree);
}

/*
@brief : A bináris fa építéséhez szükséges függvény, amely a megadott string alapján épít egy bináris fát, nincs visszatérési értéke, de dinamukusan foglalja le a memóriacíme az első paraméternek megadaott memóriacímhez kapolcsólódik az összes többi ága a fának
@param : node: A fa aktuális csúcsa
@param : string: Egy karakternek megfeleltethető morze kód, ami alapján építi fel a fát 
@param : value: A fa megfelelő csúcsának az értéke
*/

void build_Binary_tree(Node* node, char* string, char value)
{
    if (string[0] == '\0')
    {
        node->value = value;
    }else
    {
        if (string[0] == '.'){
            if (node->left == NULL)
            {
                node->left = malloc(sizeof(Node));
                if (node->left == NULL)
                {
                    printf("\nNem sikerült memóriát lefoglalni\n");
                } else
                {
                    node->left->left = NULL;
                    node->left->right = NULL;
                    node->left->value = '\0';
                }
            }
            build_Binary_tree(node->left, &string[1], value);
        }else
        {
            if (node->right == NULL)
            {
                node->right = malloc(sizeof(Node));
                if (node->right == NULL)
                {
                    printf("\nNem sikerült memóriát lefoglalni\n");
                } else
                {
                    node->right->left = NULL;
                    node->right->right = NULL;
                    node->right->value = '\0';
                }
            }
            build_Binary_tree(node->right, &string[1], value);
        }
    }
}

/*
@brief segédfüggvény, melynek feladata, hogy előkészítse az adatokat a bináris fa felépítéséhez, dinamukisan foglalja a fa memóriaterületét
@param morse_Array: A morze kódokat tartalmazó tömb
@param length: A tömb hossza
@return: A felépített bináris fa gyökerére mutató pointer
*/

Node* forward_Morse_Data(Morse* morse_Array, int length)
{
    Node* tree = malloc(sizeof(Node));
    if (tree == NULL) return memory_error();
    tree->left = NULL;
    tree->right = NULL;
    tree->value = '\0';
    for (int i = 0; i < length; i++)
    {
        build_Binary_tree(tree, morse_Array[i].value, morse_Array[i].key);
    }
    return tree;
}

/*
@brief: A bináris fa rekurzív bejárásával megkeresi a megfelelő karaktert a megadott morze kód alapján, dinaikusan foglalja a karakterláncot
@param: node: A fa aktuális csúcsa
@param: morse_Code: üres string, amitből majd a függvény csinálja keresett karakter morze kódját
@return: A visszatérési értéke a karakternek megfelelő útvonal, a morze kód, a karakterlánc első karakterének pointere
*/

char* reverse_Search_In_Morse_Tree(Node* node, char value,char* morse_Code)
{
    if (!node) return NULL;
    if (node->value == value) {
        return masolat(morse_Code);
    }
    if (node->left) {
        char* left_path = add_Char_Without_Free_Memory(morse_Code, '.');
        char* result = reverse_Search_In_Morse_Tree(node->left, value, left_path);
        free(left_path);

        if (result) return result;
    }
    if (node->right) {
        char* right_path = add_Char_Without_Free_Memory(morse_Code, '-');
        char* result = reverse_Search_In_Morse_Tree(node->right, value, right_path);
        free(right_path);

        if (result) return result;
    }
    return NULL;
}


/*
@brief megkeresi a paraméterül kapott karakter morze kódját
@param character az a karakter aminek keressük a morze kódját
@param binary_Tree a bináris fa amiben keressük a karaktert
@return A karakter megtalálásának sikerességét adja vissza, true: van a fában, false: nincs a fában
*/

bool find_Morze(char character, Node* binary_Tree)
{
    if (character == ' ') printf("/ ");
    else
    {
        char* morse = reverse_Search_In_Morse_Tree(binary_Tree,  toupper(character), "\0");
        if (morse == NULL) {printf("\nHibatörtént! Ismeretlen karakter: %c\n", character); return false;}
        printf("%s ", morse);
        free(morse);
    }
    return true;
}

/*
@brief Megkeresi a rekurzívan fában a paraméternek kapott karakterláncot
@param node A fa aktuális csúcsa
@param string a keresendő morze kód
return A morze kódnak megfelelő karakter, ha nincs \0
*/

char search_In_tree(Node* node, char* string)
{
    if (node != NULL)
    {
        if (string[0] == '\0') return node->value;
        else if (string[0] =='.') return search_In_tree(node->left, &string[1]);
        else if (string[0] =='-') return search_In_tree(node->right, &string[1]);
    }
    return '\0';
}
