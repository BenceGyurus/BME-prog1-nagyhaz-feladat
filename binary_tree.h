
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdbool.h>

typedef struct Node {
    char value;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Morse {
    char key;
    char* value;
} Morse;

void free_Tree(Node* tree);
void build_Binary_tree(Node* node, char* string, char value);
Node* forward_Morse_Data(Morse* morse_Array, int length);
char* reverse_Search_In_Morse_Tree(Node* node, char value, char* morse_Code);
bool find_Morze(char character, Node* binary_Tree);
char search_In_tree(Node* node, char* string);

#endif // BINARY_TREE_H
