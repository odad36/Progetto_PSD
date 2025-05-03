#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct attivita {
char nome[50];
char descrizione[100];
char corso_appartenenza[50]; 
char data_scadenza [11]; //11 caratteri, perchè una stringa "data_scadenza" sarà composta da 10 caratteri + \0
int priorita;
int tempo_stimato; //rappresenta il tempo stimato (in ore) per il completamento dell'attività, è un valore scelto dall'utente
int tempo_effettivo; //rappresenta il tempo effettivo (in ore) di studio fatto dall'utente, è un valore che viene manualmente aggiornato dall'utente
int completata; //1 = sì, 0 = no
};

attivita crea_attivita(char* nome, char* descrizione, char* corso_appartenenza, char* data_scadenza, int priorita, int tempo_stimato) {
    attivita att = malloc(sizeof(struct attivita));
    strcpy(att->nome, nome);
    strcpy(att->descrizione, descrizione);
    strcpy(att->corso_appartenenza, corso_appartenenza);
    strcpy(att->data_scadenza, data_scadenza);
    att->priorita = priorita;
    att->tempo_stimato = tempo_stimato;
    att->tempo_effettivo = 0;
    att->completata = 0;
    return att;
}

int data_valida(char* data) {
    int giorno;
    int mese;
    int anno;
    if (strlen(data) != 10) //verifica che la data sia della lunghezza giusta
        return 0;
    if (data[2] != '/' || data[5] != '/') //verifica che gli slash '/' siano al posto giusto
        return 0;
    if (!isdigit(data[0]) || !isdigit(data[1]) || !isdigit(data[3]) || !isdigit(data[4])  //verifica che oltre agli slash siano presenti solamente numeri
    || !isdigit(data[6]) || !isdigit(data[7]) || !isdigit(data[8]) || !isdigit(data[9]))
        return 0;
    if (sscanf(data, "%2d/%2d/%4d", &giorno, &mese, &anno) != 3) //verifica per assucurarsi che sscanf non abbia letto formati irregolari
        return 0;
    if (giorno < 1 || giorno > 31 || mese < 1 || mese > 12 || anno < 2025) //verifica che giorno, mese ed anno abbiano dei valori validi
        return 0;
    if ((mese == 4 || mese == 6 || mese == 9 || mese == 11) && giorno > 30) //verifica dei giorni per mesi da 30 giorni
        return 0;
    if (mese == 2) { //verifica specifica per febbraio
        int bisestile = (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0); //verifica per anno bisestile
        if ((bisestile && giorno > 29) || (!bisestile && giorno > 28)) //verifica dei giorni per anni bisestili o meno
            return 0;
        }
    return 1;
    }

void modifica_scadenza(attivita att) {
    char nuova_scadenza[11];
    while(1) {
        printf("inserire la nuova data di scadenza, rispettando il formato: giorno/mese/anno\n");
        scanf("%s", nuova_scadenza);
        if (data_valida(nuova_scadenza) == 1) {
            strcpy(att->data_scadenza, nuova_scadenza);
            return;
        }
        else {
            printf("Errore! Assicurarsi di aver scritto la data con il formato: giorno/mese/anno (01/01/2001), e di non aver inserito una data passata o inesistente.\n");
        }
    }
}

void stampa_stato_completamento(attivita att) {
    if(att->completata == 0)
        printf("l'attività non è stata ancora completata\n");
    else
        printf("l'attività è stata completata\n");
return;
}

int accedi_priorita(attivita att) {
    return att->priorita;
}

float calcola_progresso(attivita att) {
    float progresso;
    if (att->tempo_stimato == 0)  //per assicurarsi che il tempo stimato non sia 0, ed evitare errori inaspettati
        return 0; 
    else
        progresso = ((float)att->tempo_effettivo / att->tempo_stimato) * 100;  //calcola il valore in percentuale dei progressi effettuati basandosi sul tempo di studio effettivo, il casting a float serve per far sì che il risultato della divisione sia un float
    if (progresso > 100)
        progresso = 100;
    return progresso;
}

void stampa_progresso(attivita att) {
    printf("il progresso dell'attività è pari al %.2f percento\n", calcola_progresso(att));
    return;
}

void stampa_attivita(attivita att) { 
    printf("ecco le specifiche della tua attività\n"
    "nome:%s;\n" 
    "descrizione:%s;\n" 
    "corso di appartenenza:%s;\n" 
    "data di scadenza:%s;\n" 
    "priorità:%d;\n" 
    "tempo stimato:%d;\n" 
    "tempo effettivo:%d;\n", 
    att->nome,
    att->descrizione,
    att->corso_appartenenza,
    att->data_scadenza,
    att->priorita,
    att->tempo_stimato,
    att->tempo_effettivo); //nota: il campo "completata" non è presente, per sapere se un'attività è completata o meno, si utilizza la funzione stampa_stato_completamento
return;
}

void modifica_completata(attivita att) {
    if(att->completata == 0)
        att->completata = 1;
    else
        att->completata = 0;
    return;
}