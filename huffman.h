
#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct node{
    char value;
    int freq;
    struct node* left;
    struct node* right;
} Node;

typedef struct list{
    char value;
    int freq;
    struct list* next;
    struct list* prev;
    struct node* node;
} List;

void compress(FILE* file);
void decompress(FILE* file);
Node* makeTree(char* filename);
Node* makeNode(char value);
List* prependList(List* list, Node* node, char value, int frequency);
List* removeFromList(List* list, char value);
int listLength(List* list);
List* findVal(List* list, char value);
List* combineLows(List* list);


#endif /* end of include guard: HUFFMAN_H
 */
