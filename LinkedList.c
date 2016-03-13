//
//  LinkedList.c
//
//  Created by Adil on 3/8/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#include "LinkedList.h"




Node* node_new(void* value){
    Node* n= (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr,"memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    n->_value = value;
    n->next = NULL;
    return n;
}


int list_empty(LinkedList* l){
    return l->size == 0;
}
int list_size(LinkedList* l){
    return l->size;
}


LinkedList* list_new(){
    LinkedList* l = (LinkedList*) malloc(sizeof(LinkedList));
    if (l == NULL) {
        perror("memory allocation error");
        exit(EXIT_FAILURE);
    }
    l->size = 0;
    l->firstNode = NULL;
    l->lastNode = NULL;
    return l;
}

void list_free(LinkedList* l){
    if (l != NULL) {
        if (l->size == 0) {
            free(l);
            return;
        }
        list_clean(l, &free);
        free(l);
    }
}


int list_insert(LinkedList* l, void* value, int atIndex){
    Node *n,*cur;
    if ( NULL == l) {
        perror("null list pointer");
        exit(EXIT_FAILURE);
    }
    if (atIndex !=0 && (atIndex < 0 || atIndex > l->size)) {
        perror("Index out Of bound error");
        return E_INDEX_OUT_OF_BOUND;
    }
    n = node_new(value);
    if (atIndex == 0) {
        n->next = l->firstNode;
        l->firstNode = n;
        l->size++;
        if (l->size == 1){
            l->lastNode = l->firstNode;
        }
            return E_OK;
    }
    if (atIndex == l->size) {
        l->lastNode->next = n;
        l->lastNode = n;
        l->size++;
        return E_OK;
    }
    
    cur=l->firstNode;
    while (atIndex > 1) {
        cur = cur->next;
        atIndex--;
    }
    n->next = cur->next;
    cur->next = n;
    return 0;
}

int list_add(LinkedList* l, void* value){
    return list_insert(l, value, l->size);
}

int list_delete(LinkedList* l, int atIndex, void(*freeCallback)(void*) ){
    if (list_empty(l) || atIndex < 0 || atIndex > list_size(l)-1) {
        return E_INDEX_OUT_OF_BOUND;
    }
    Node *nDel = NULL;
    Node *prev = NULL;
    if (atIndex == 0) {
        nDel = l->firstNode;
        if (list_size(l) == 1)
            l->firstNode = l->lastNode = NULL;
        else
            l->firstNode = nDel->next;
    }else{
        prev = l->firstNode;
        while (atIndex > 1) {
            prev = prev->next;
            atIndex--;
        }
        nDel = prev->next;
        prev->next = nDel->next;
        if (atIndex == list_size(l)-1 ) {
            l->lastNode = prev;
        }
    }
    
    l->size--;
    if (nDel != NULL) {
        if (nDel->_value != NULL)
            (*freeCallback)(nDel->_value);
        free(nDel);
    }
    return E_OK;
}

int list_clean(LinkedList* l, void(*freeCallback)(void*) ){
    int ret = E_NOT_FOUND;
    while (!list_empty(l)) {
        ret = list_delete(l, 0,freeCallback);
    }
    return ret;
}

void* list_get(LinkedList* l, int atIndex){
    if (list_empty(l) || atIndex < 0 || atIndex > list_size(l)-1) {
        return NULL;
    }
    Node *n= l->firstNode;
    while (atIndex > 0) {
        n = n->next;
        atIndex--;
    }
    return n->_value;
    
}

int list_replace(LinkedList* l, int atIndex, void* newElement, void(*freeCallback)(void*) ){
    if (list_empty(l) || atIndex < 0 || atIndex > list_size(l)-1) {
        return E_INDEX_OUT_OF_BOUND;
    }
    Node *n = node_new(newElement);
    Node *nDel = NULL;
    Node *prev = NULL;
    if (atIndex == 0) {
        nDel = l->firstNode;
        n->next = nDel->next;
        l->firstNode = n;
        if (list_size(l) == 1) {
            l->lastNode = n;
        }
    }else{
        prev = l->firstNode;
        while (atIndex > 1) {
            prev = prev->next;
            atIndex--;
        }
        nDel = prev->next;
        prev->next = n;
        n->next = nDel->next;
        if (atIndex == list_size(l)-1) {
            l->lastNode = n;
        }
    }
    if (nDel != NULL) {
        if (nDel->_value != NULL)
            (*freeCallback)(nDel->_value);
        free(nDel);
    }
    return E_OK;
}

