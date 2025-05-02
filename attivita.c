#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
struct attivita {
char nome[50];
char descrizione[100];
char corso_appartenenza[50]; 
char data_scadenza [11]; //11 caratteri, perchè una stringa "data_scadenza" sarà composta da 10 caratteri + \0
int priorita;
int tempo_stimato; //rappresenta il tempo stimato (dall'utente) per il completamento dell'attività
int tempo_effettivo; //rappresenta il tempo effettivo di studio fatto dall'utente, è un valore che viene manualmente aggiornato dall'utente
int completata; //1 = sì, 0 = no
};
