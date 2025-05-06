#ifndef ATTIVITA_H //per evitare di includere più volte lo stesso file
#define ATTIVITA_H

typedef struct attivita* attivita;  //typedef "opaco" per rispettare l'information hiding, attivita è ora un puntatore alla struttura definita in attivita.c
attivita crea_attivita(char*, char*, char*, char*, int, int);
void stampa_attivita(attivita);
void modifica_scadenza(attivita);
void stampa_stato_completamento(attivita);
int accedi_priorita(attivita);
float calcola_progresso(attivita);
void stampa_progresso(attivita);
void modifica_completata(attivita);
char* accedi_nome(attivita);
void modifica_tempo_effettivo(attivita); 
#endif