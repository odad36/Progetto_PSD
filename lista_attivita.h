#ifndef LISTA_ATTIVITA_H
#define LISTA_ATTIVITA_H
#include "attivita.h"

typedef struct nodo* lista_attivita;  //typedef "opaco" per rispettare l'information hiding

/*

• Funzione: crea_lista

* parametri:
nessuno

* precondizioni: nessuna

* postcondizioni: la funzione crea e restituisce una lista vuota

*/

lista_attivita crea_lista(void);

/*

• Funzione: stampa_lista

* parametri:
lst

* precondizioni: deve essere inserita una lista esistente

* postcondizioni: nessuna

* side effect: viene stampata la lista

*/

void stampa_lista(lista_attivita);

/*

• Funzione: inserisci_attivita

* parametri:
lst, att

* precondizioni: devono essere inserite una lista ed un’attività esistenti

* postcondizioni: viene restituita una lista con l’aggiunta (in testa alla lista) dell’attività passata come argomento 

*/

lista_attivita inserisci_attivita(lista_attivita, attivita);

/*

• Funzione: rimuovi_attivita

* parametri:
lst, nome

* precondizioni: deve essere inserita una lista esistente ed il nome di un'attività

* postcondizioni: viene restituita una lista con l’eliminazione della prima attività trovata con il nome passato alla funzione, oppure, 
se il nome inserito non corrisponde ad alcuna attività, restituisce NULL, e stampa un messaggio di errore.

*/

lista_attivita rimuovi_attivita(lista_attivita, char*);

/*

• Funzione: cerca_attivita

* parametri:
lst, nome

* precondizioni: devono essere inserite una lista esistente ed il nome di un’attività

* postcondizioni: la funzione restituisce l’attività con il nome indicato, oppure, 
se il nome inserito non corrisponde ad alcuna attività, restituisce NULL

*/

attivita cerca_attivita(lista_attivita, char*);

/*

• Funzione: conta_attivita

* parametri:
lst

* precondizioni: deve essere inserita una lista esistente

* postcondizioni: la funzione restituisce n, ossia il numero di attività presenti nella lista

*/

int conta_attivita(lista_attivita);

/*

• Funzione: genera_report_settimanale

* parametri:
lst, data_oggi

* precondizioni: devono essere inserite una lista esistente, ed una data valida 

* postcondizioni: nessuna 

* side effect: la funzione stampa un report, che analizza tutte le attività che negli
ultimi 7 giorni sono scadute, quelle su cui l'utente ha fatto dei progressi, e quelle completate,
le divide quindi in 3 categorie e le stampa:

attività scadute
attività aggiornate
attività completate

*/

void genera_report_settimanale(lista_attivita, char*);

/*

• Funzione: distruggi_lista

* parametri:
lst

precondizioni: deve essere inserita una lista esistente

postcondizioni: nessuna

side effect: la funzione (chiamata solo alla terminazione del programma) dealloca tutta la memoria precedentemente allocata per la lista. 

*/

void distruggi_lista(lista_attivita);

#endif