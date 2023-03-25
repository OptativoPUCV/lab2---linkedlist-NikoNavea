#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *lista = (List*) malloc(sizeof(List));

  if(lista == NULL) exit(EXIT_FAILURE);
  lista->head = NULL;
  lista->tail = NULL;
  
  return lista;
}

void * firstList(List * list) {
  if(list->tail == NULL) return NULL;
  list->current = list->head;
  
  return list->head->data;
}

void * nextList(List * list) {
  if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
  list->current = list->current->next;
  
  return list->current->data;
}

void * lastList(List * list) {
  if(list == NULL || list->tail == NULL) return NULL;
  
  list->current = list->tail;
  
  return list->tail->data;
}

void * prevList(List * list) {
  if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
  
  list->current = list->current->prev;
  
  return list->current->data;
}

void pushFront(List * list, void * data) {
  if(list == NULL) return;
  Node* n = createNode(data);
  n->next = list->head;
  if(list->head == NULL){
    list->head = n;
    list->current = n;
    list->tail = n;
  }
  else{
    n->next = list->head;
    list->head->prev = n;
    list->head = n;
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list == NULL || list->current == NULL) return;
  Node* n = createNode(data);
  if(list->current == list-> tail) {
    n->prev = list->current;
    list->current->next = n;
    list->tail = n;
  }
  else{
    n->prev = list->current;
    n->next = list->current->next;
    list->current->next->prev = n;
    list->current->next = n;
  }
}

void * popFront(List * list) {
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list == NULL || list->current == NULL) return;
  void* dato = list->current->dato;
  if(list->current->prev != NULL){
    list->prev->next = list->next;
  }
  else{
    list->head = list->current->next;
  }
  if(list->current->next == NULL){
    list->current->next->prev = list->current->prev;
  }
  return dato;
}

void cleanList(List * list) {
  while (list->head != NULL) {
    popFront(list);
  }
}