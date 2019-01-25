
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#include "linkedlist.h"

void list_new(list *list, size_t elementSize, freeFunction freeFn){
    list->logicalLength = 0;
    list->elementSize = elementSize;
    list->head = malloc(sizeof(listNode));
    list->tail = malloc(sizeof(listNode));
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->freeFn = freeFn;
}

void list_destroy(list *list){
    while(list->head->next != list->tail){
        listNode *currNode = list->head->next;
        list->head->next = currNode->next;
        currNode->next->prev = list->head;
        if(list->freeFn) list->freeFn(currNode->data);
        free(currNode->data);
        free(currNode);
        list->logicalLength--;
    }
}

void list_prepend(list *list, void *element){
    listNode *newNode = malloc(sizeof(listNode));
    newNode->data = malloc(sizeof(list->elementSize));
    memcpy(newNode->data, element, list->elementSize);
    newNode->next = list->head->next;
    list->head->next = newNode;
    newNode->prev = list->head;
    newNode->next->prev = newNode;
    list->logicalLength++;
}

void list_append(list *list, void *element){
    listNode *newNode = malloc(sizeof(listNode));
    newNode->data = malloc(sizeof(list->elementSize));
    memcpy(newNode->data, element, list->elementSize);
    newNode->prev = list->tail->prev;
    newNode->next = list->tail;
    list->tail->prev = newNode;
    newNode->prev->next = newNode;
    list->logicalLength++;
}

void list_for_each(list *list, listIterator iterator){}

void list_head(list *list, void *element, bool removeFromList){
    listNode *currNode = list->head->next;
    memcpy(element, currNode->data, list->elementSize);
    if(removeFromList == TRUE){
        list->head->next = currNode->next;
        currNode->next->prev = list->head;
        list->logicalLength--;
        //if(list->freeFn) list->freeFn(currNode->data);
        free(currNode->data);
        free(currNode);
    }
}
void list_tail(list *list, void *element){}

unsigned int list_size(list *list){
    return list->logicalLength;
}