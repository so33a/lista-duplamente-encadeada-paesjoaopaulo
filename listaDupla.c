#include <stdio.h>
#include <stdlib.h>
#include "listaDupla.h"

link novoNo (int item, link prev, link next) {
  link aux = malloc(sizeof(struct node));
  if (aux == NULL) {
    printf ("Erro ao alocar um novo no\n");
    exit(-1);
  }
  aux->item = item;
  aux->prev = prev;
  aux->next = next;
  return aux;
}


ListaDupla inicializa() {
  ListaDupla aux;
  aux = malloc(sizeof *aux);
  aux->z = novoNo(0, NULL, NULL);
  aux->head = aux->z;
  aux->z->next = aux->head;
  aux->z->prev = aux->head;
  return aux;
}

void insereDepois (ListaDupla l, link x, link t) {
  if (x == NULL) {
    l->head = t;
    t->next = l->z;
    t->prev = l->z;
    l->z->prev = t;
    l->z->next = t; 
  } else {
    t->next = x->next;
    t->prev = x;
    x->next = t;
    t->next->prev = t;
  }
}

link removeNo (link x) {
  x->prev->next = x->next;
  x->next->prev = x->prev;
  return x;
}
void imprimeReverso(ListaDupla l) {
  link t = l->z->prev;
  while ( t != l->z ) {
    printf ("%d ", t->item);
    t = t->prev;
  }
  printf("\n");
}


void imprime(ListaDupla l) {
  link t = l->head;
  while ( t != l->z ) {
    printf ("%d ", t->item);
    t = t->next;
  }
  printf("\n");
}

link buscar(ListaDupla l, int item) {
  link t = l->head;
  while ( t != l->z ) {
    if(t->item == item)
      return t;
    t = t->next;
  }
  return NULL;
}
/* 
void insereAntes (ListaDupla l, link x, link t);
*/

void destroiLista(ListaDupla l) {
  link t = l->head;
  while (t != l->z) {
    l->head = t->next;
    l->z->next = t->next;
    l->head->prev = l->z;
    free(t); 
    t = l->head;
  } 
  free(t);
  free(l);
}

link buscaMenorItem(ListaDupla l){
  link head = l->head;
  link menor = head;
  while(head != l->z){
    if(menor->item > head->item){
      menor = head;
    }
    head = head->next;
  }
  return head;
}

ListaDupla sortList(ListaDupla l){
  link head = l->head;
  ListaDupla nova = inicializa();
  /*
  procuro o menor item (buscaMenorItem(l)) da lista original,
  removo (removeNo(link menor)) e insiro na nova lista na primeira posição (l->z->prev)
  */
  while(head != l->z){
    insereDepois(nova, nova->z->prev, removeNo(buscaMenorItem(l)));
    head = head->next;
  }
  destroiLista(l);
  return nova;
}
