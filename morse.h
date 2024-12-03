#ifndef MORSE_H
#define MORSE_H
#include "binary_tree.h"

Morse morse_cpy(Morse morse);
Morse* morse_Linked_List(Morse* pointer, int length, Morse new_Morse);
Morse create_Morse(char* string);
void free_Morse(Morse* morse_Array, int length);
void encode_Morse(Node* morse_Tree, char* read_Input);
bool control_Morse_Code(char* morse);
void decode_Morse(Node* tree, char* input);
Morse* read_Morse_From_File(char* fileName, int* length);



#endif //MORSE_H
