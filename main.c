#include "attivita.h"
#include <stdio.h>

/* main usato per testing
int main() {
    // Test creazione
    attivita a = crea_attivita("Progetto PSD", "Modello dati + funzioni", "PSD", "10/05/2025", 1, 10);

    // Test stampa
    stampa_attivita(a);

    // Test stato
    stampa_stato_completamento(a);
    modifica_completata(a);
    stampa_stato_completamento(a);

    // Test progresso (senza tempo effettivo)
    stampa_progresso(a);

    // Modifica scadenza (con input utente)
    modifica_scadenza(a);
    stampa_attivita(a);  // per vedere la nuova data

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"
#include "lista_attivita.h"

int main() {
    lista_attivita lista = crea_lista();

    // Creo alcune attivita
    attivita a1 = crea_attivita("Analisi", "Studiare derivate", "Matematica", "10/05/2025", 2, 5);
    attivita a2 = crea_attivita("PSD", "Finire ADT", "PSD", "12/05/2025", 1, 8);
    attivita a3 = crea_attivita("Inglese", "Essay finale", "Lingue", "15/05/2025", 3, 3);

    // Inserisco in lista
    lista = inserisci_attivita(lista, a1);
    lista = inserisci_attivita(lista, a2);
    lista = inserisci_attivita(lista, a3);

    printf("--- Lista iniziale ---\n");
    stampa_lista(lista);

    // Test conta
    printf("\nNumero di attivita: %d\n", conta_attivita(lista));

    // Test cerca
    printf("\nCerco 'PSD'...\n");
    attivita trovata = cerca_attivita(lista, "PSD");
    if (trovata != NULL) {
        stampa_attivita(trovata);
    }

    // Test rimozione testa
    printf("\nRimuovo 'Inglese' (testa della lista)\n");
    lista = rimuovi_attivita(lista, "Inglese");
    stampa_lista(lista);

    // Test rimozione in mezzo
    printf("\nRimuovo 'PSD' (nodo centrale)\n");
    lista = rimuovi_attivita(lista, "PSD");
    stampa_lista(lista);

    // Test rimozione in fondo
    printf("\nRimuovo 'Analisi' (ultimo nodo)\n");
    lista = rimuovi_attivita(lista, "Analisi");
    stampa_lista(lista);

    // Test rimozione non esistente
    printf("\nProvo a rimuovere 'Fisica' (non esiste)\n");
    lista = rimuovi_attivita(lista, "Fisica");
    stampa_lista(lista);

    return 0;
}