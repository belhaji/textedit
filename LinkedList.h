//
//  LinkedList.h
//
//  Created by Adil on 3/8/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h


#define E_OK                    0
#define E_NOT_FOUND             1
#define E_INDEX_OUT_OF_BOUND    2
#define E_NULL_VALUE            3

#define FREE_CALLBACK(func) ((void(*)(void*))func)


typedef struct __node{
    void* _value;
    struct __node* next;
} Node;

typedef struct {
    int size;
    Node *firstNode;
    Node *lastNode;
} LinkedList;


Node* node_new(void* value);



LinkedList* list_new();

void list_free(LinkedList* l);

int list_empty(LinkedList* l);

int list_size(LinkedList* l);

int list_insert(LinkedList* l, void* value, int atIndex);

int list_add(LinkedList* l, void* value);

int list_delete(LinkedList* l, int atIndex,void(*freeCallback)(void*) );

int list_clean(LinkedList* l, void(*freeCallback)(void*));

void* list_get(LinkedList* l, int atIndex);

int list_replace(LinkedList* l, int atIndex, void* newElement, void(*freeCallback)(void*) );




#endif /* LinkedList_h */
