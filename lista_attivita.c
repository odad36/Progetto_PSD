#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_attivita.h"
#include "attivita.h"

struct nodo {
    attivita dato;
    struct nodo* next;
};

lista_attivita crea_lista(void) {
    return NULL; //una lista vuota è esattamente un puntatore NULL, questa funzione serve solamente per rispettare l'information hiding
}
void stampa_lista(lista_attivita lst) {
    if(lst == NULL) {  //controllo per lista vuota
        printf("la lista è vuota\n");
        return;
    }    
    lista_attivita attuale = lst;
    while(attuale != NULL) {  //ciclo per scorrere l'intera lista
        stampa_attivita(attuale->dato);  
        stampa_progresso(attuale->dato);
        stampa_stato_completamento(attuale->dato);
        printf("----------------------------------\n");  //printf per spaziare le varie attività
        attuale = attuale->next;  //passiamo alla prossima attività
    }
}

lista_attivita inserisci_attivita(lista_attivita lst, attivita att) { // non c'è bisogno di "pos", l'inserimento può essere semplicemente effettuato in testa
    lista_attivita nuovo = malloc(sizeof(struct nodo));  //alloco memoria per il nuovo nodo
    if (nuovo == NULL) {
        printf("Errore: memoria insufficiente\n");
        return lst;
    }
    nuovo->dato = att;  //inserisco l'attività nel nuovo nodo
    nuovo->next = lst;  //collego il nuovo nodo alla testa della lista
    return nuovo;
}

lista_attivita rimuovi_attivita(lista_attivita lst, char* nome) {
    lista_attivita attuale = lst;
    lista_attivita precedente = lst;
    if (attuale != NULL) {
        if (strcmp(accedi_nome(attuale->dato), nome) == 0) {  
            lista_attivita nuovo_inizio = attuale->next;
            free(attuale->dato);
            free(attuale);
            return nuovo_inizio;
        }
        attuale = attuale->next;
    }
    while(attuale != NULL) {
        if (strcmp(accedi_nome(attuale->dato), nome) == 0) {
            precedente->next = attuale->next;
            free(attuale->dato);
            free(attuale);
            return lst;
        }
        attuale = attuale->next;
        precedente = precedente->next;
    }
    printf("nessuna attività con questo nome trovata\n");
    return lst;
}

attivita cerca_attivita(lista_attivita lst, char* nome) {
    lista_attivita attuale = lst;
    while(attuale != NULL) {  //ciclo per scorrere l'intera lista
        if (strcmp(accedi_nome(attuale->dato), nome) == 0)  //compariamo la stringa passata alla funzione, con il nome dell'attività
            return attuale->dato;
        attuale = attuale->next; //passiamo alla prossima attività
    }
    printf("nessuna attività con questo nome trovata");
        return NULL;
}

int conta_attivita(lista_attivita lst) {
    lista_attivita attuale = lst;
    int contatore = 0;
    while(attuale != NULL) { //ciclo per scorrere l'intera lista
        contatore += 1;  //incremento il contatore
        attuale = attuale->next;  //passiamo alla prossima attività
    }
    return contatore;
}