#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

void compress(FILE* file){

    return;
}

void decompress(FILE* file){

    return;
}

Node* makeTree(char* filename){
    Node* tree = NULL;
    List* list = NULL;
    List* temp;
    int buffer_length = 128, i;
    char buffer[buffer_length];
    FILE* file;
    file = fopen(filename,"r");


    if(file != NULL){
        // read file to find frequency of all characters
        while(fgets(buffer, buffer_length, file) != NULL){
            for(i = 0; i < strlen(buffer); i++){
                temp = findVal(list, (char) buffer[i]);
                if(temp == NULL){
                    list = prependList(list, makeNode((char) buffer[i]), (char) buffer[i], 1);
                }
                else{
                    temp->freq += 1;
                }
            }
        }

        // make tree by combining low frequencies
        while(listLength(list)>1){
            list = combineLows(list);
        }
        tree = list->node;
    }
    return tree;
}

Node* makeNode(char value){
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->freq = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

List* prependList(List* list, Node* node, char value, int frequency){
    List* newVal = (List*) malloc(sizeof(List));
    newVal->value = value;
    newVal->freq = frequency;
    newVal->next = list;
    newVal->prev = NULL;
    newVal->node = node;
    if(list!=NULL){
        list->prev = newVal;
    }
    return newVal;
}

List* removeFromList(List* list, char value){
    List* temp;
    temp = findVal(list, value);

    if(temp != NULL){
        if(temp == list){
            list = temp->next;
            if(list != NULL){
                list->prev = NULL;
            }
        }
        else{
            temp->prev->next = temp->next;
            if(temp->next != NULL){
                temp->next->prev = temp->prev;
            }
        }
    }
    free(temp);

    return list;
}

int listLength(List* list){
    int i = 0;
    List* temp = list;
    while(temp != NULL){
        temp =temp->next;
        i++;
    }
    return i;
}

List* findVal(List* list, char value){
    List* location;
    if(list->value == value){
        location = list;
    }
    else if(list->next = NULL){
        location = NULL;
    }
    else{
        location = findVal(list->next, value);
    }
    return location;
}

List* combineLows(List* list){
    char low1val;
    char low2val;
    int low1; // lowest frequency
    int low2; // second lowest
    List* temp = list->next;
    Node* newNode = (Node*) malloc(sizeof(Node));

    // compare the first two values of list to make low1 the lower frequency value
    if(list->freq < list->next->freq){
        low1val = list->value;
        low1 = list->freq;
        low2val = list->next->value;
        low2 = list->next->freq;
    }
    else{
        low1val = list->next->value;
        low1 = list->next->freq;
        low2val = list->value;
        low2 = list->freq;
    }

    // if list is larger than 2, find the two lowest frequencies
    if(list->next->next != NULL){
        // loop until end of list
        while(temp->next != NULL){
            // lower than the lower frequency
            if(temp->next->freq < low1){
                low2val = low1val;
                low2 = low1;
                low1val = temp->next->value;
                low1 = temp->next->freq;
            }
            // lower than the higher frequency
            else if(temp->next->freq < low2){
                low2val = temp->next->value;
                low2 = temp->next->freq;
            }
        }
    }
    // get the nodes for the corresponding values and store in left and right
    newNode->left = findVal(list, low2val)->node;
    newNode->right = findVal(list, low1val)->node;
    // remove from list
    list = removeFromList(list, low1val);
    list = removeFromList(list, low2val);
    // add new node to list with a frequency of low1+low2
    list = prependList(list, newNode, low1val, low1+low2);

    return list;
}
