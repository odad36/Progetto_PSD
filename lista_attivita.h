#ifndef LISTA_ATTIVITA_H
#define LISTA_ATTIVITA_H
#include "attivita.h"

typedef struct nodo* lista_attivita;  //typedef "opaco" per rispettare l'information hiding
lista_attivita crea_lista(void);
void stampa_lista(lista_attivita);
lista_attivita inserisci_attivita(lista_attivita, attivita);
lista_attivita rimuovi_attivita(lista_attivita, char*);
attivita cerca_attivita(lista_attivita, char*);
int conta_attivita(lista_attivita);
void genera_report_settimanale(lista_attivita, char*);
#endif