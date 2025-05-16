#include <stdio.h>
#include <string.h>
#include "attivita.h"
#include "lista_attivita.h"

int main() {
    char data_oggi[11];
    printf("Inserisci la data di oggi (gg/mm/aaaa):\n");
    scanf("%s", data_oggi);
    while (!data_valida(data_oggi)) {
        printf("Data non valida, riprova:\n");
        scanf("%s", data_oggi);
    }

    while (getchar() != '\n');  //Svuota il buffer dopo scanf

    lista_attivita lst = crea_lista();
    int scelta;

    do {
        printf("\n----- MENU PRINCIPALE -----\n");
        printf("1. Aggiungi un'attività di studio\n");
        printf("2. Rimuovi un'attività di studio\n");
        printf("3. Visualizza attività di studio\n");
        printf("4. Modifica il tempo di studio effettivo di un'attività\n");
        printf("5. Modifica la data di scadenza di un'attività\n");
        printf("6. Segna un'attività come completata\n");
        printf("7. Genera un report settimanale\n");
        printf("0. Esci\n");
        printf("Digita un numero da 0 a 7 per scegliere un opzione del menu: ");
        scanf("%d", &scelta);
        while(scelta < 0 || scelta > 7) {
            printf("opzione non esistente, riprova\n");
            scanf("%d", &scelta);
        }
    }  while (scelta != 0);

        switch(scelta) {


            case 1: {
                char nome[100], descrizione[100], corso_appartenenza[100], data_scadenza[11];
                int priorita, tempo_stimato;

                printf("Inserisci il nome (max 100 caratteri):\n");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                while (!stringa_valida(nome) || cerca_attivita(lst, nome) != NULL) {
                    printf("Nome non valido o già utilizzato, riprova");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                }

                printf("Inserisci la descrizione:\n");
                fgets(descrizione, 100, stdin);
                descrizione[strcspn(descrizione, "\n")] = '\0';
                while (!stringa_valida(descrizione)) {
                    printf("Descrizione non valida, riprova:\n");
                    fgets(descrizione, 100, stdin);
                    descrizione[strcspn(descrizione, "\n")] = '\0';
                }

                printf("Inserisci il corso di appartenenza:\n");
                fgets(corso_appartenenza, 100, stdin);
                corso_appartenenza[strcspn(corso_appartenenza, "\n")] = '\0';
                while (!stringa_valida(corso_appartenenza)) {
                    printf("Corso non valido, riprova:\n");
                    fgets(corso_appartenenza, 100, stdin);
                    corso_appartenenza[strcspn(corso_appartenenza, "\n")] = '\0';
                }

                printf("Inserisci la data di scadenza (gg/mm/aaaa):\n");
                scanf("%s", data_scadenza);
                while (!data_valida(data_scadenza)) {
                    printf("Data non valida, riprova:\n");
                    scanf("%s", data_scadenza);
                }
                while (getchar() != '\n');

                printf("Inserisci la priorità (1 = alta, 2 = media, 3 = bassa):\n");
                while (scanf("%d", &priorita) != 1 || (priorita != 1 && priorita != 2 && priorita != 3)) {
                    printf("Valore non valido, inserisci 1, 2 o 3:\n");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                printf("Inserisci il tempo stimato in ore:\n");
                while (scanf("%d", &tempo_stimato) != 1 || tempo_stimato <= 0) {
                    printf("Valore non valido, riprova:\n");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                attivita att = crea_attivita(nome, descrizione, corso_appartenenza, data_scadenza, data_oggi, priorita, tempo_stimato);
                lst = inserisci_attivita(lst, att);
                printf("Attività di studio aggiunta con successo!\n");
                break;
            }


            case 2: {
                char nome [100];
                printf("inserisci il nome dell'attività da rimuovere\n");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                lista_attivita nuova_lst = rimuovi_attivita(lst, nome);
                if (nuova_lst == lst) {
                // nessuna attività rimossa (rimuovi_attivita stampa il messaggio di errore)
                break;
                }
                lst = nuova_lst;
                printf("Attività di studio rimossa con successo.\n");
                break;
                }
            
            
            case 3: {
            int scelta_3;
            do {
                printf("\n----- OPZIONI DI VISUALIZZAZIONE -----\n");
                printf("1. Visualizza un'attività di studio\n");
                printf("2. Visualizza tutte le attività di studio\n");
                printf("0. Esci\n");
                scanf("%d", &scelta_3);
                while(scelta_3 < 0 || scelta_3 > 2) {
                    printf("opzione non esistente, riprova\n");
                    scanf("%d", &scelta);
                }
            } while (scelta_3 != 0);
            
            switch (scelta_3) {
                
            case 1: {
                char nome [100];
                printf("inserisci il nome dell'attività da visualizzare\n");
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
                break;
            }

            case 2: {
            if (lst == NULL) {
               printf("Nessuna attività presente.\n");
               break;
            }
            stampa_lista(lst);
            break;
            }

            case 0: {
                break;
            }
            default: {
                printf("Scelta non valida. Riprova.\n");
            }

            }
                
                break;

            case 4:
                char nome[100];
                attivita att;
                printf("inserisci il nome dell'attività di cui vuoi modificare il tempo effettivo di studio\n");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                att = cerca_attivita(lst, nome);
                if (att == NULL) {
                    printf("nessuna attivita con questo nome trovata\n");
                    break;
                }
                modifica_tempo_effettivo(att, data_oggi);
                break;

            case 5:
                char nome[100];
                attivita att;
                printf("inserisci il nome dell'attività di cui vuoi modificare la scadenza\n");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                att = cerca_attivita(lst, nome);
                if (att == NULL) {
                    printf("nessuna attivita con questo nome trovata\n");
                    break;
                }
                modifica_scadenza(att);
                break;
            case 6:
                char nome[100];
                attivita att;
                printf("inserisci il nome dell'attività di cui vuoi aggiornare il completamento\n");
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
            case 7:
                genera_report_settimanale(lst, data_oggi);
                break;
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
        }

    } while (scelta != 0);

    return 0;
}
