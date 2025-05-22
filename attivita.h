#ifndef ATTIVITA_H //per evitare di includere più volte lo stesso file
#define ATTIVITA_H

typedef struct attivita* attivita;  //typedef "opaco" per rispettare l'information hiding, attivita è ora un puntatore alla struttura definita in attivita.c

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

attivita crea_attivita(char*, char*, char*, char*, char*, int, int);

/*

• Funzione: data_valida
- verifica se la stringa "data" è una data scritta nel formato: gg/mm/aaaa

* parametri:
data

*precondizioni: la funzione deve ricevere una stringa

*postcondizioni: la funzione restituisce 0 se la data è in un formato non valido, oppure se la data indicata è irregolare, 1 altrimenti.


*/

int data_valida(char*);

/*

• Funzione: stringa_valida
- verifica che la stringa "str" non sia vuota, o composta da soli spazi, e che sia < 100 caratteri

* parametri:
str

* precondizioni: la funzione deve ricevere una stringa

* postcondizioni: la funzione restituisce 0 se la stringa è vuota, troppo lunga, oppure composta da soli spazi, 1 altrimenti.

*/

int stringa_valida(char*);

/*

• Funzione: modifica_scadenza
- modifica il membro: "data_scadenza" dell'attività passata alla funzione

* parametri:
att : ossia l'attività di cui si vuole modificare la scadenza

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: la scadenza dell’attività passata come argomento viene modificata dall’utente (che aggiungerà una nuova data).

*/

void modifica_scadenza(attivita);

/*

• Funzione: stampa_stato_completamento

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: viene stampato un messaggio in cui è scritto se l’attività è completata o meno (a seconda del valore del membro “completata”)

*/

void stampa_stato_completamento(attivita);

/*

• Funzione: calcola_progresso
- la funzione calcola il progresso dell'attività basandosi sul rapporto tra ore di studio effettive, e le ore di studio stimate

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: la funzione calcola il progresso dell’attività passata come argomento, e restituisce un valore in % del lavoro completato 

*/

float calcola_progresso(attivita);

/*

• Funzione: stampa_progresso

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: la funzione calcola (tramite calcola_progresso) e stampa il valore del progresso

*/

void stampa_progresso(attivita);

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

void stampa_attivita(attivita);

/*

• Funzione: stampa_priorita

- la funzione stampa "priorità alta", "priorità media" oppure "priorità bassa" a seconda del valore del membro priorita di att

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: viene stampata una stringa che indica la priorità dell’attività passata come argomento, a seconda del valore del membro “priorita” di essa.

*/

void stampa_priorita(attivita att);

/*

• Funzione: modifica_completata

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: : il membro “completata” dell’attività passata come argomento, viene modificato (se è 0 diventa 1, se è 1 diventa 0)

*/

void modifica_completata(attivita);

/*

• Funzione: modifica_tempo_effettivo

- la funzione aggiorna il valore di tempo_effettivo, sommando le ore inserite dall'utente con le ore già presenti, ed aggiorna data_ultima_modifica
alla data di oggi

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: nessuna

* side effect: il tempo effettivo dell’attività passata come argomento viene modificato dall’utente (che inserirà la quantità di ore di studio effettuate, 
che si andranno a sommare con quelle già presenti). Inoltre, il membro data_ultima_modifica viene aggiornato con il valore di data_oggi

*/

void modifica_tempo_effettivo(attivita, char*); 

/*

•confronta_date(data1, data2) -> -1 || 0 || 1

-la funzione confronta due date, e restitusice uno degli interi indicati a seconda del risultato del confronto

*parametri: att

*precondizioni: devono essere inserite due date valide

*postcondizioni: la funzione restituisce:
-1 se data1 < data2
0 se data1 = data2
1 se data1 > data2

*/

int confronta_date(char*, char*);

/*

• accedi_nome(att) -> att->nome

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: la funzione restituisce il membro nome dell’attività passata come argomento,
  oppure se l’attività è vuota (NULL), stampa un messaggio di errore, e restituisce la stringa “ERRORE”

* note: questa funzione è importante per rispettare l’information hiding

*/

char* accedi_nome(attivita);

/*

•	accedi_priorita(att) -> att->priorita

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: la funzione restituisce il membro priorita dell’attività passata come argomento, 
oppure se l’attività è vuota (NULL), stampa un messaggio di errore, e restituisce il valore “ – 1”

* note: questa funzione è importante per rispettare l’information hiding.

*/


int accedi_priorita(attivita);

/*

• accedi_completata(att) -> att->completata

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni la funzione restituisce il membro completata dell’attività passata come argomento, 
oppure se l’attività è vuota (NULL), stampa un messaggio di errore, e restituisce il valore “ – 1 “.

* note: questa funzione è importante per rispettare l’information hiding.

*/

int accedi_completata(attivita);

/*

• accedi_data_scadenza(att) -> att->data_scadenza

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: la funzione restituisce il membro data_scadenza dell’attività passata come argomento, oppure se l’attività è vuota (NULL), 
stampa un messaggio di errore, e restituisce la stringa “ERRORE”

note: questa funzione è importante per rispettare l’information hiding

*/

char* accedi_data_scadenza(attivita);

/*

• accedi_data_ultima_modifica(att) -> att->data_ultima_modifica

* parametri:
att

* precondizioni: deve essere inserita un’attività esistente

* postcondizioni: la funzione restituisce il membro data_ultima_modifica dell’attività passata come argomento, oppure se l’attività è vuota (NULL),
stampa un messaggio di errore, e restituisce la stringa “ERRORE”

* note: questa funzione è importante per rispettare l’information hiding

*/

char* accedi_data_ultima_modifica(attivita);

/*

•	sottrai_7_giorni(data_oggi, data_risultato) -> void

- la funzione, data una stringa contenente una data nel formato gg/mm/aaaa, calcola il valore della data 7 giorni precedente
ad essa, e salva il risultato nell'area di memoria puntata da data_risultato

* parametri:
data_oggi
data_risultato

* precondizioni: devono essere inserite due date valide

* postcondizioni: nessuna

* side effect: la stringa puntata da data_risultato conterrà la data 7 giorni precedente a data_oggi.

*/

void sottrai_7_giorni(char*, char*);

#endif