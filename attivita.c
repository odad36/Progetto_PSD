#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
definizione dettagliata della struttura attivita
*/
struct attivita {
char nome[100];
char descrizione[100];
char corso_appartenenza[100]; 
char data_scadenza [11];  //11 caratteri, perchè una stringa "data_scadenza" sarà composta da 10 caratteri + \0
char data_ultima_modifica[11];  //questo valore aggiornato con "data_oggi" (nel main), ogni volta che "tempo_effettivo" viene incrementato.
int priorita;  // valori: 1 = alta, 2 = media, 3 = bassa
int tempo_stimato;  //rappresenta il tempo stimato (in ore) per il completamento dell'attività, è un valore scelto dall'utente
int tempo_effettivo;  //rappresenta il tempo effettivo (in ore) di studio fatto dall'utente, è un valore che viene manualmente aggiornato dall'utente
int completata; //valori: 1 = sì, 0 = no
};

/*

• Funzione: crea_attivita

* parametri:
nome, descrizione, corso_appartenenza, data_scadenza, data_ultima_modifica, priorita, tempo_stimato

* precondizioni:
devono essere inseriti dei valori validi per ogni membro della struttura attivita.

* postcondizioni: 
la funzione restituisce una struttura attivita con all’interno i dati inseriti dall’utente, 
inoltre i valori: “tempo effettivo” e “completata” sono inizializzati a 0, e la stringa “data_ultima_modifica” sarà la copia di “data_oggi”.

*/

attivita crea_attivita(char* nome, char* descrizione, char* corso_appartenenza, char* data_scadenza, char* data_oggi, int priorita, int tempo_stimato) {
    attivita att = malloc(sizeof(struct attivita));
    strcpy(att->nome, nome);
    strcpy(att->descrizione, descrizione);
    strcpy(att->corso_appartenenza, corso_appartenenza);
    strcpy(att->data_scadenza, data_scadenza);
    strcpy(att->data_ultima_modifica, data_oggi);
    att->priorita = priorita;
    att->tempo_stimato = tempo_stimato;
    att->tempo_effettivo = 0;
    att->completata = 0;
    return att;
}

/*

• Funzione: data_valida
- verifica se la stringa "data" è una data scritta nel formato: gg/mm/aaaa

* parametri:
data

*precondizioni: la funzione deve ricevere una stringa

*postcondizioni: la funzione restituisce 0 se la data è in un formato non valido, oppure se la data indicata è irregolare, 1 altrimenti.


*/


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

/*

• Funzione: stringa_valida
- verifica che la stringa "str" non sia vuota, o composta da soli spazi, e che sia < 100 caratteri

* parametri:
str

* precondizioni: la funzione deve ricevere una stringa

* postcondizioni: la funzione restituisce 0 se la stringa è vuota, troppo lunga, oppure composta da soli spazi, 1 altrimenti.

*/

int stringa_valida(char* str) {
    if (str == NULL) {
        return 0;
    }

    int lunghezza = strlen(str);
    if (lunghezza == 0 || lunghezza >= 100) {
        return 0;
    }

    int solo_spazi = 1;
    for (int i = 0; i < lunghezza; i++) {
        if (str[i] != ' ') {
            solo_spazi = 0;
            break;
        }
    }
    if (solo_spazi) {
        return 0;
    }

    return 1;
}

/*

• Funzione: modifica_scadenza
- modifica il membro: "data_scadenza" dell'attività passata alla funzione

* parametri:
att : ossia l'attività di cui si vuole modificare la scadenza

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: la scadenza dell’attività passata come argomento viene modificata dall’utente (che aggiungerà una nuova data).

*/

void modifica_scadenza(attivita att) {
    char nuova_scadenza[11];
    while(1) {
        printf("inserire la nuova data di scadenza, rispettando il formato: giorno/mese/anno\n");
        scanf("%10s", nuova_scadenza);
        while (getchar() != '\n'); 
        if (data_valida(nuova_scadenza) == 1) {
            strcpy(att->data_scadenza, nuova_scadenza);
            return;
        }
        else {
            printf("Errore! Assicurarsi di aver scritto la data con il formato: giorno/mese/anno (01/01/2001), e di non aver inserito una data passata o inesistente.\n");
        }
    }
}

/*

• Funzione: stampa_stato_completamento

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: viene stampato un messaggio in cui è scritto se l’attività è completata o meno (a seconda del valore del membro “completata”)

*/

void stampa_stato_completamento(attivita att) {
    if(att->completata == 0)
        printf("l'attività non è stata ancora completata\n");
    else
        printf("l'attività è stata completata\n");
return;
}

/*

• Funzione: calcola_progresso
- la funzione calcola il progresso dell'attività basandosi sul rapporto tra ore di studio effettive, e le ore di studio stimate

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: la funzione calcola il progresso dell’attività passata come argomento, e restituisce un valore in % del lavoro completato 

*/

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

/*

• Funzione: stampa_progresso

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: la funzione calcola (tramite calcola_progresso) e stampa il valore del progresso

*/

void stampa_progresso(attivita att) {
    printf("il progresso dell'attività è pari al %.2f percento\n", calcola_progresso(att));
    return;
}

/*

• Funzione: stampa_attivita
- la funzione stampa tutti i membri dell'attivita tranne: priorita e completamento
(questo perchè questi due sono valori numerici, che vanno stampati con delle apposite funzioni)

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: i membri dell’attività passata come argomento (tranne priorita e completamento) vengono stampati

*/

void stampa_attivita(attivita att) { 
    printf("ecco le specifiche della tua attività\n"
    "nome:%s;\n" 
    "descrizione:%s;\n" 
    "corso di appartenenza:%s;\n" 
    "data di scadenza:%s;\n" 
    "data ultima modifica:%s;\n"
    "tempo stimato:%d;\n" 
    "tempo effettivo:%d;\n", 
    att->nome,
    att->descrizione,
    att->corso_appartenenza,
    att->data_scadenza,
    att->data_ultima_modifica,
    att->tempo_stimato,
    att->tempo_effettivo);
return;
}

/*

• Funzione: stampa_priorita
- la funzione stampa tutti i membri 

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: i membri dell’attività passata come argomento vengono stampati

*/

void stampa_priorita(attivita att) {
    if (att == NULL) {
        printf("Errore: attività non valida\n");
        return;
    }

    printf("priorità: ");

    if (att->priorita == 1) {
        printf("alta\n");
    } else if (att->priorita == 2) {
        printf("media\n");
    } else if (att->priorita == 3) {
        printf("bassa\n");
    }
}

void modifica_completata(attivita att) {
    if(att->completata == 0)
        att->completata = 1;
    else
        att->completata = 0;
    return;
}

void modifica_tempo_effettivo(attivita att, char* data_oggi) {
    if(att == NULL) {
        printf("Errore, l'attività è vuota\n");
        return;
    }
    int tempo_aggiuntivo;
    int input_valido = 0;
    do {
        printf("Quante ore hai studiato? Inserisci un numero intero positivo:\n");
        input_valido = scanf("%d", &tempo_aggiuntivo);
        while (getchar() != '\n');
        if (input_valido != 1 || tempo_aggiuntivo < 0) {
            printf("Input non valido. Riprova.\n");
            input_valido = 0; // forza a ripetere
    }
} while (input_valido == 0);

    att->tempo_effettivo += tempo_aggiuntivo;
    strcpy(att->data_ultima_modifica, data_oggi);
    return;
}

int confronta_date(char* data1, char* data2) {
    int giorno1, mese1, anno1, giorno2, mese2, anno2;
    sscanf(data1, "%2d/%2d/%4d", &giorno1, &mese1, &anno1);
    sscanf(data2,  "%2d/%2d/%4d", &giorno2, &mese2, &anno2);
    if (anno1 != anno2) {
        if (anno1 < anno2)
            return -1;
        if (anno1 > anno2)
            return 1;
    }
    if (mese1 != mese2) {
        if (mese1 < mese2)
            return -1;
        if (mese1 > mese2)
            return 1;
    }
    if (giorno1 != giorno2) {
        if (giorno1 < giorno2)
            return -1;
        if (giorno1 > giorno2)
            return 1;
    }
    return 0;
}

char* accedi_nome(attivita att) {
    if (att == NULL){
        printf("Errore, l'attività è vuota\n");
        return "ERRORE";
    }
    return att->nome;
}

int accedi_priorita(attivita att) {
    if (att == NULL){
        printf("Errore, l'attività è vuota\n");
        return -1;
    }
    return att->priorita;
}

int accedi_completata(attivita att) {
    if (att == NULL) {
        printf("Errore, l'attività è vuota\n");
        return -1;
    }
    return att->completata;
}

char* accedi_data_scadenza(attivita att) {
    if (att == NULL) {
        printf("Errore, l'attività è vuota\n");
        return "ERRORE";
    }
    return att->data_scadenza;
}

char* accedi_data_ultima_modifica(attivita att) {
    if (att == NULL) {
        printf("Errore, l'attività è vuota\n");
        return "ERRORE";
    }
    return att->data_ultima_modifica;
}

void sottrai_7_giorni(char* data_oggi, char* data_risultato) {
    int giorno, mese, anno;
    sscanf(data_oggi, "%2d/%2d/%4d", &giorno, &mese, &anno);
    giorno -= 7;
    while (giorno < 1) {
        mese--;
        if (mese < 1) {
            mese = 12;
            anno--;
        }
        if (mese == 2) {
            int bisestile = 0;
            if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0)) {
                bisestile = 1;
                }
            if (bisestile == 1) {
                giorno += 29;
                } 
            else {
                giorno += 28;
                }
            } 
            else if (mese == 4 || mese == 6 || mese == 9 || mese == 11) {
                giorno += 30;
            } 
            else {
                giorno += 31;
            }
        }
    sprintf(data_risultato, "%02d/%02d/%04d", giorno, mese, anno);
}