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

void genera_report_settimanale(lista_attivita lst, char* data_oggi) {
    if(lst == NULL) {
        printf("la lista è vuota\n");
        return;
    }
    char data_settimana[11];
    sottrai_7_giorni(data_oggi, data_settimana);
    printf("------ Ecco il report dell'ultima settimana ------\n");
    printf("Periodo di riferimento: %s - %s\n", data_settimana, data_oggi);

    lista_attivita attuale;

     // 1. Attività SCADUTE negli ultimi 7 giorni
     printf("\n-- ATTIVITÀ SCADUTE NEGLI ULTIMI 7 GIORNI --\n");
     attuale = lst;
     while(attuale != NULL) {
         attivita a = attuale->dato;
         if (accedi_completata(a) == 0 && confronta_date(accedi_data_scadenza(a), data_settimana) >= 0 && 
         confronta_date(accedi_data_scadenza(a), data_oggi) <= 0) {
             printf("- %s (scadenza: %s)\n", accedi_nome(a), accedi_data_scadenza(a));
         }
         attuale = attuale->next;
     }
 
     // 2. Attività MODIFICATE negli ultimi 7 giorni
     printf("\n-- ATTIVITÀ MODIFICATE NEGLI ULTIMI 7 GIORNI --\n");
     attuale = lst;
     while(attuale != NULL) {
         attivita a = attuale->dato;
         if (confronta_date(accedi_data_ultima_modifica(a), data_settimana) >= 0 && 
         confronta_date(accedi_data_ultima_modifica(a), data_oggi) <= 0) {
             printf("- %s (modificata il: %s) - Progresso: %.2f%%\n", accedi_nome(a), accedi_data_ultima_modifica(a), calcola_progresso(a));
         }
         attuale = attuale->next;
     }
 
     // 3. Attività COMPLETATE negli ultimi 7 giorni
     printf("\n-- ATTIVITÀ COMPLETATE NEGLI ULTIMI 7 GIORNI --\n");
     attuale = lst;
     while(attuale != NULL) {
         attivita a = attuale->dato;
         if (accedi_completata(a) == 1 && confronta_date(accedi_data_ultima_modifica(a), data_settimana) >= 0 && 
         confronta_date(accedi_data_ultima_modifica(a), data_oggi) <= 0) {
             printf("- %s (completata il: %s)\n", accedi_nome(a), accedi_data_ultima_modifica(a));
         }
         attuale = attuale->next;
     }
 
     printf("------ FINE REPORT ------\n");
 }