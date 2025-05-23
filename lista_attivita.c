#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_attivita.h"
#include "attivita.h"

/*
lista concatenata
*/
struct nodo {
    attivita dato;
    struct nodo* next;
};

/*

• Funzione: crea_lista

* parametri:
nessuno

* precondizioni: nessuna

* postcondizioni: la funzione crea e restituisce una lista vuota

*/

lista_attivita crea_lista(void) {
    return NULL; //una lista vuota è esattamente un puntatore NULL, questa funzione serve solamente per rispettare l'information hiding
}

/*

• Funzione: stampa_lista

* parametri:
lst

* precondizioni: deve essere inserita una lista esistente

* postcondizioni: nessuna

* side effect: viene stampata la lista delle attività ordinate secondo la priorità (prima quelle con priorità maggiore)

*/

void stampa_lista(lista_attivita lst) {
    if(lst == NULL) {  //controllo per lista vuota
        printf("la lista è vuota\n");
        return;
    }    
     for (int priorita = 1; priorita <= 3; priorita++) {
        lista_attivita attuale = lst;
        while (attuale != NULL) {
            if (accedi_priorita(attuale->dato) == priorita) {
                stampa_attivita(attuale->dato);
                stampa_progresso(attuale->dato);
                stampa_stato_completamento(attuale->dato);
                stampa_priorita(attuale->dato);
                printf("----------------------------------\n");
            }
            attuale = attuale->next;
        }
    }
}

/*

• Funzione: inserisci_attivita

* parametri:
lst, att

* precondizioni: devono essere inserite una lista ed un’attività esistenti

* postcondizioni: viene restituita una lista con l’aggiunta (in testa alla lista) dell’attività passata come argomento 

*/

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

/*

• Funzione: rimuovi_attivita

* parametri:
lst, nome

* precondizioni: deve essere inserita una lista esistente ed il nome di un'attività

* postcondizioni: viene restituita una lista con l’eliminazione della prima attività trovata con il nome passato alla funzione, oppure, 
se il nome inserito non corrisponde ad alcuna attività, restituisce NULL, e stampa un messaggio di errore.

*/

lista_attivita rimuovi_attivita(lista_attivita lst, char* nome) {
    lista_attivita attuale = lst;
    lista_attivita precedente = lst;
    if (attuale != NULL) {
        if (strcmp(accedi_nome(attuale->dato), nome) == 0) { //controlla se il primo nodo contiene l'attività da rimuovere
            lista_attivita nuovo_inizio = attuale->next;   //salva il nuovo inizio della lista
            free(attuale->dato);   //libera la memoria allocata per i dati dell'attività
            free(attuale);   //libera la memoria allocata per il nodo stesso
            return nuovo_inizio;   //restituisce il nuovo inizio della lista
        }
        attuale = attuale->next; //avanza al nodo successivo
    }
    while(attuale != NULL) {   //ciclo per scorrere l'intera lista
        if (strcmp(accedi_nome(attuale->dato), nome) == 0) {  //controlla se il nome dell'attività corrente, corrisponde con quello da rimuovere
            precedente->next = attuale->next;  //per rimuovere il nodo attuale, colleghiamo il nodo precedente ad attuale, a quello successivo
            free(attuale->dato);  //libera i dati dell'attività
            free(attuale);  //libera il nodo stesso
            return lst;  //restituisce la testa della lista (che è sempre la stessa)
        } 
        attuale = attuale->next;  //passa al nodo successivo
        precedente = precedente->next;  //anche "precedente" avanza
    }
    printf("nessuna attività con questo nome trovata\n");
    return lst;
}

/*

• Funzione: cerca_attivita

* parametri:
lst, nome

* precondizioni: devono essere inserite una lista esistente ed il nome di un’attività

* postcondizioni: la funzione restituisce l’attività con il nome indicato, oppure, 
se il nome inserito non corrisponde ad alcuna attività, restituisce NULL

*/

attivita cerca_attivita(lista_attivita lst, char* nome) {
    lista_attivita attuale = lst;
    while(attuale != NULL) {  //ciclo per scorrere l'intera lista
        if (strcmp(accedi_nome(attuale->dato), nome) == 0)  //compariamo la stringa passata alla funzione, con il nome dell'attività
            return attuale->dato;
        attuale = attuale->next; //passiamo alla prossima attività
    }
        return NULL;
}

/*

• Funzione: conta_attivita

* parametri:
lst

* precondizioni: deve essere inserita una lista esistente

* postcondizioni: la funzione restituisce n, ossia il numero di attività presenti nella lista

*/

int conta_attivita(lista_attivita lst) {
    lista_attivita attuale = lst;
    int contatore = 0;
    while(attuale != NULL) { //ciclo per scorrere l'intera lista
        contatore += 1;  //incremento il contatore
        attuale = attuale->next;  //passiamo alla prossima attività
    }
    return contatore;
}

/*

• Funzione: genera_report_settimanale

* parametri:
lst, data_oggi

* precondizioni: devono essere inserite una lista esistente, ed una data valida 

* postcondizioni: nessuna 

* side effect: la funzione stampa un report, che analizza tutte le attività che negli
ultimi 7 giorni sono scadute, quelle su cui l'utente ha fatto dei progressi (modificate), e quelle completate,
le divide quindi in 3 categorie e le stampa:

attività scadute
attività modificate
attività completate

*/

void genera_report_settimanale(lista_attivita lst, char* data_oggi) {
    if(lst == NULL) {
        printf("la lista è vuota\n");
        return;
    }
    char data_settimana[11];  //stringa che conterrà la data 7 giorni precedente alla data di oggi
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
         confronta_date(accedi_data_scadenza(a), data_oggi) <= 0) {  // controlla se l'attività non è stata completata, ed è scaduta negli ultimi 7 giorni
             printf("- %s (scadenza: %s)\n", accedi_nome(a), accedi_data_scadenza(a));  //stampa il nome dell'attività scaduta, e la data in cui è scaduta
         }
         attuale = attuale->next;
     }
 
     // 2. Attività MODIFICATE negli ultimi 7 giorni
     printf("\n-- ATTIVITÀ MODIFICATE NEGLI ULTIMI 7 GIORNI --\n");
     attuale = lst;
     while(attuale != NULL) {
         attivita a = attuale->dato;
         if (confronta_date(accedi_data_ultima_modifica(a), data_settimana) >= 0 && 
         confronta_date(accedi_data_ultima_modifica(a), data_oggi) <= 0) {  //controlla se l'attività è stata modificata (ossia se sono state aggiunte delle ore di studio) negli ultimi 7 giorni
             printf("- %s (modificata il: %s) - Progresso: %.2f%%\n", accedi_nome(a), accedi_data_ultima_modifica(a), calcola_progresso(a));  //stampa il nome dell'attività aggiornata, la data in cui è avvenuta l'ultima modifica, ed il progresso dell'attività
         }
         attuale = attuale->next;
     }
 
     // 3. Attività COMPLETATE negli ultimi 7 giorni
     printf("\n-- ATTIVITÀ COMPLETATE NEGLI ULTIMI 7 GIORNI --\n");
     attuale = lst;
     while(attuale != NULL) {
         attivita a = attuale->dato;
         if (accedi_completata(a) == 1 && confronta_date(accedi_data_ultima_modifica(a), data_settimana) >= 0 && 
         confronta_date(accedi_data_ultima_modifica(a), data_oggi) <= 0) {  //controlla se l'attività è stata completata negli ultimi 7 giorni
             printf("- %s (completata il: %s)\n", accedi_nome(a), accedi_data_ultima_modifica(a));  //stampa il nome dell'attività completata, e la data in cui è stata completata
         }
         attuale = attuale->next;
     }
 
     printf("------ FINE REPORT ------\n");
 }

/*

• Funzione: distruggi_lista

* parametri:
lst

precondizioni: deve essere inserita una lista esistente

postcondizioni: nessuna

side effect: la funzione (chiamata solo alla terminazione del programma) dealloca tutta la memoria precedentemente allocata per la lista. 

*/

void distruggi_lista(lista_attivita lst) {
    lista_attivita corrente = lst;
    while (corrente != NULL) {
        lista_attivita temp = corrente;  //salva il nodo corrente
        corrente = corrente->next;  //passa al nodo successivo
        free(temp->dato);  // libera l'attività contenuta
        free(temp);        // libera il nodo stesso
    }
}