#ifndef LABA3_DYNLIST_H
#define LABA3_DYNLIST_H

typedef int valueType;
typedef struct array_node {
    struct array_node *next;
    valueType value;
} dynArrNode;

typedef struct array {
    int size;
    dynArrNode *head;
    dynArrNode *tail;
} dynArr;

dynArr *createList();
void pushToListBegin(dynArr *array, int number);
void pushToListEnd(dynArr *array, int number);
valueType popFromListBegin(dynArr *array);

#endif //LABA3_DYNLIST_H
