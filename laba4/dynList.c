#include "dynList.h"

dynArr *createList() {
    dynArr *array = malloc(sizeof(dynArr));
    array->size = 0;
    array->head = NULL;
    array->tail = array->head;
    return array;
}

void pushToListBegin(dynArr *array, int number) {
    dynArrNode *temp = malloc(sizeof(dynArrNode));
    temp->value = number;
    temp->next = array->head;

    array->head = temp;
    array->size += 1;
}

void pushToListEnd(dynArr *array, int number) {
    dynArrNode *temp = malloc(sizeof(dynArrNode));
    temp->value = number;
    if (array->tail != NULL) {
        array->tail->next = temp;
    }
    else {
        array->head = temp;
    }
    array->tail = temp;
    array->size += 1;
}

valueType popFromListBegin(dynArr *array) {
    if (array->size == 0) {
        return -1;
    }
    dynArrNode *temp = array->head;
    valueType retValue = temp->value;

    array->size -= 1;
    array->head = temp->next;

    free(temp);
    if (array->size == 0) {
        array->head = NULL;
        array->tail = NULL;
    }
    return retValue;
}

valueType getValueByIndex(dynArr *array, int index) {
    if ((index >= array->size) || (index < 0)) {
        return -50;
    }
    dynArrNode *temp = array->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->value;
}

int changeValueByIndex(dynArr *array, int index, valueType value) {
    if ((index >= array->size) || (index < 0)) {
        return -1;
    }
    dynArrNode *temp = array->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->value = value;
    return 0;
}
