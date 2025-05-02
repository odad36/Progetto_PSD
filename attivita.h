typedef struct attivita* attivita;
attivita crea_attivita(char*, char*, char*, char*, int, int);
void stampa_attivita(attivita);
void modifica_scadenza(attivita);
void stampa_stato_completamento(attivita);
float calcola_progresso(attivita);
int accedi_priorità(attivita);
