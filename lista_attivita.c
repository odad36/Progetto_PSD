#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_attivita.h"

struct nodo {
    attivita dato;
    struct nodo* next;
};

lista_attivita crea_lista(void) {
    return NULL; //una lista vuota è esattamente un puntatore NULL, questa funzione serve solamente per rispettare l'information hiding
}
void stampa_lista(lista_attivita lst);

lista_attivita inserisci_attivita(lista_attivita lst, attivita att) { // non c'è bisogno di "pos", l'inserimento può essere semplicemente effettuato in testa
    struct nodo* nuovo = malloc(sizeof(struct nodo));
    if (nuovo == NULL) {
        printf("Errore: memoria insufficiente\n");
        return lst;
    }
    nuovo->dato = att;
    nuovo->next = lst;
    return nuovo;
}
void rimuovi_attivita(lista_attivita, char*);
attivita cerca_attivita(lista_attivita, char*);
int conta_attivita(lista_attivita);