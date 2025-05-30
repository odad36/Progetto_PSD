#include <stdio.h>
#include <string.h>
#include "attivita.h"
#include "lista_attivita.h"

int main(int argc, char* argv[]) {
    
    /*la test_mode è una modalità che permette di utilizzare il programma senza visualizzare
    il menu interattivo, in maniera tale da rendere l'oracolo ed il result molto più brevi e chiari*/

    int test_mode = 0;
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {  //condizione di attivazione della modalità test
        test_mode = 1;
    }

    char data_oggi[11]; 
    int input_valido;
    do {
        if (!test_mode) {  //controllo per non stampare messaggi in modalità test
            printf("Inserisci la data di oggi (gg/mm/aaaa):\n");
        }
        input_valido = scanf("%10s", data_oggi);  //richiede la data di oggi (necessaria come riferimento per il report settimanale)
        while (getchar() != '\n');  //Svuota il buffer dopo scanf
        if (input_valido != 1 || !data_valida(data_oggi)) {
        if (!test_mode) {
            printf("Data non valida. Riprova.\n");
        }
    }

} while (input_valido != 1 || !data_valida(data_oggi));

    lista_attivita lst = crea_lista();
    int scelta;

 do {
    //stampa del menu interattivo
    if (!test_mode) {
        printf("\n----- MENU PRINCIPALE -----\n");
        printf("1. Aggiungi un'attività di studio\n");
        printf("2. Rimuovi un'attività di studio\n");
        printf("3. Visualizza attività di studio\n");
        printf("4. Modifica il tempo di studio effettivo di un'attività\n");
        printf("5. Modifica la data di scadenza di un'attività\n");
        printf("6. Segna un'attività come completata\n");
        printf("7. Genera un report settimanale\n");
        printf("0. Esci\n");
    }
   int input_valido;
   //opzione scelta dall'utente
   do {
        if (!test_mode) {
            printf("Digita un numero da 0 a 7 per scegliere un'opzione: ");
        }
        input_valido = scanf("%1d", &scelta);
        while (getchar() != '\n');
        if (input_valido != 1 || scelta < 0 || scelta > 7) {
        if (!test_mode) {
            printf("Input non valido. Riprova.\n");
       }
    }
} while (input_valido != 1 || scelta < 0 || scelta > 7);

        //implementazione del menu interattivo
        switch(scelta) {


            //Aggiunta di un'attività di studio
            case 1: {
                char nome[100], descrizione[100], corso_appartenenza[100], data_scadenza[11];
                int priorita, tempo_stimato;

                //nome
                if (!test_mode) {
                    printf("Inserisci il nome (max 99 caratteri):\n");
                }
                fgets(nome, 100, stdin);  //utilizzo di fgets (e non scanf) per evitare problemi con gli spazi
                if (strchr(nome, '\n') == NULL) {  //se manca il '\n', l'utente ha inserito troppi caratteri
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);   //ch raccoglie tutti i caratteri da eliminare, e svuota buffer
                        printf("Nome troppo lungo! Cancellazione dell'attività, ritorno al menu principale.\n");
                        continue;                                       //torna al case 1
                    }
                nome[strcspn(nome, "\n")] = '\0';   //rimuove il carattere '\n' , e lo sostituisce con '\0' (in modo tale da avere una vera e propria stringa)
                while (!stringa_valida(nome) || cerca_attivita(lst, nome) != NULL) {
                    printf("Nome non valido o già utilizzato, riprova\n");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                }

                //descrizione
                if (!test_mode) {
                    printf("Inserisci la descrizione (max 99 caratteri):\n");
                }
                fgets(descrizione, 100, stdin);
                if (strchr(descrizione, '\n') == NULL) {  //se manca il '\n', l'utente ha inserito troppi caratteri
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);   //ch raccoglie tutti i caratteri da eliminare, e svuota buffer
                        printf("Descrizione troppo lunga! Cancellazione dell'attività, ritorno al menu principale.\n");
                        continue;                                       //torna al case 1
                    }
                descrizione[strcspn(descrizione, "\n")] = '\0';
                while (!stringa_valida(descrizione)) {
                    printf("Descrizione non valida, riprova:\n");
                    fgets(descrizione, 100, stdin);
                    descrizione[strcspn(descrizione, "\n")] = '\0';
                }

                //corso di appartenenza
                if (!test_mode) { 
                    printf("Inserisci il corso di appartenenza (max 99 caratteri):\n");
                }
                fgets(corso_appartenenza, 100, stdin);
                if (strchr(corso_appartenenza, '\n') == NULL) {  //se manca il '\n', l'utente ha inserito troppi caratteri
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);   //ch raccoglie tutti i caratteri da eliminare, e svuota buffer
                        printf("Nome del corso troppo lungo! Cancellazione dell'attività, ritorno al menu principale.\n");
                        continue;                                       //torna al case 1
                    }
                corso_appartenenza[strcspn(corso_appartenenza, "\n")] = '\0';
                while (!stringa_valida(corso_appartenenza)) {
                    printf("Corso non valido, riprova:\n");
                    fgets(corso_appartenenza, 100, stdin);
                    corso_appartenenza[strcspn(corso_appartenenza, "\n")] = '\0';
                }

                //data di scadenza
                if (!test_mode) {
                    printf("Inserisci la data di scadenza (gg/mm/aaaa):\n");
                }
                scanf("%10s", data_scadenza);
                while (getchar() != '\n');
                while (!data_valida(data_scadenza)) {
                    printf("Data non valida, riprova:\n");
                    scanf("%10s", data_scadenza);
                    while (getchar() != '\n');  //necessarie più pulizie di buffer per prevenire stampe multiple
                }
                
                //priorità
                if (!test_mode) {
                    printf("Inserisci la priorità (1 = alta, 2 = media, 3 = bassa):\n");
                }
                while (scanf("%1d", &priorita) != 1 || (priorita != 1 && priorita != 2 && priorita != 3)) {
                    printf("Valore non valido, inserisci 1, 2 o 3:\n");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                //tempo stimato
                if (!test_mode) {
                    printf("Inserisci il tempo stimato in ore:\n");
                }
                while (scanf("%d", &tempo_stimato) != 1 || tempo_stimato <= 0) {
                    printf("Valore non valido, riprova:\n");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                //creazione dell'attività in base ai dati inseriti

                attivita att = crea_attivita(nome, descrizione, corso_appartenenza, data_scadenza, data_oggi, priorita, tempo_stimato);
                lst = inserisci_attivita(lst, att);
                printf("Attività di studio aggiunta con successo!\n");
                break;
            }

            //rimozione di un'attività
            case 2: {
                char nome [100];
                printf("inserisci il nome dell'attività da rimuovere\n");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                lista_attivita nuova_lst = rimuovi_attivita(lst, nome);
                if (nuova_lst == lst) {
                // nessuna attività rimossa (la funzione rimuovi_attivita stampa il messaggio di errore)
                break;
                }
                lst = nuova_lst;
                printf("Attività di studio rimossa con successo.\n");
                break;
                }
            
            //visualizzazione delle attività
            case 3: {
                int scelta_3;
                //sottomenu interattivo 
                do {
                    if (!test_mode) {
                        printf("\n----- OPZIONI DI VISUALIZZAZIONE -----\n");
                        printf("1. Visualizza un'attività di studio\n");
                        printf("2. Visualizza tutte le attività di studio in ordine di priorità\n");
                        printf("0. Esci\n");
                        printf("Scelta: ");
                    }
                    input_valido = scanf("%1d", &scelta_3);
                    while (getchar() != '\n');
 
                    if (input_valido != 1 || scelta_3 < 0 || scelta_3 > 2) {
                        printf("Input non valido. Riprova.\n");
                        continue;
                    }
                
                switch (scelta_3) {
                    //visualizzazione di una singola attività
                    case 1: {
                        char nome [100];
                        if (!test_mode) {
                            printf("inserisci il nome dell'attività da visualizzare\n");
                        }
                        fgets(nome, 100, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        attivita att = cerca_attivita(lst, nome);
                        if (att == NULL) {
                        printf("nessuna attivita con questo nome trovata\n");
                        break;
                    }
                    stampa_attivita(att);
                    stampa_progresso(att);
                    stampa_stato_completamento(att);
                    stampa_priorita(att);
                    break;
                }
                    //visualizzazione di tutte le attività in ordine di priorità
                    case 2: {
                        if (lst == NULL) {
                        printf("Nessuna attività presente.\n");
                        break;
                    }
                        printf("Sono presenti %d attività:\n", conta_attivita(lst)); //stampa il numero di attività presenti
                        stampa_lista(lst);
                        break;
                }
                    //uscita dal sottomenu
                    case 0: {
                        break;
                }
                    default: {
                        printf("Scelta non valida. Riprova.\n");
                        break;
                }
                    }
                } while (scelta_3!= 0);
            break;
        }
            //modifica del tempo effettivo di studio
            case 4: {
                char nome[100];
                attivita att;
                if (!test_mode) {
                    printf("inserisci il nome dell'attività di cui vuoi modificare il tempo effettivo di studio\n");
                }
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                att = cerca_attivita(lst, nome);
                if (att == NULL) {
                    printf("nessuna attivita con questo nome trovata\n");
                    break;
                }
                modifica_tempo_effettivo(att, data_oggi);
                break;
            }

            //modifica della scadenza di un'attività
            case 5: {
                char nome[100];
                attivita att;
                if (!test_mode) {
                    printf("inserisci il nome dell'attività di cui vuoi modificare la scadenza\n");
                }
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                att = cerca_attivita(lst, nome);
                if (att == NULL) {
                    printf("nessuna attivita con questo nome trovata\n");
                    break;
                }
                modifica_scadenza(att);
                break;
            }

            //aggiornamento del completamento di un'attività
            case 6: {
                char nome[100];
                attivita att;
                if (!test_mode) {
                    printf("inserisci il nome dell'attività di cui vuoi aggiornare il completamento\n");
                }
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                att = cerca_attivita(lst, nome);
                if (att == NULL) {
                    printf("nessuna attivita con questo nome trovata\n");
                    break;
                }
                modifica_completata(att);
                stampa_stato_completamento(att);
                break;
            }

            //generazione del report settimanale
            case 7: {
                genera_report_settimanale(lst, data_oggi);
                break;
            }    

            //uscita dal programma
            case 0: {
                if (!test_mode) {
                    printf("Uscita dal programma.\n");
                }
                break;
            }
            default: {
                printf("Scelta non valida. Riprova.\n");
                break;
            }
        }
    } while (scelta != 0); 
        
    distruggi_lista(lst); //dealloca la memoria

    return 0;
}
