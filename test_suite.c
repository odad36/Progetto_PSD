#include <stdio.h>
#include <stdlib.h>

// Funzione che confronta due file riga per riga
int confronta_file(const char* file1, const char* file2) {
    //apro in lettura i file
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");  
    
    if (f1 == NULL || f2 == NULL) {  //controllo se l'apertura è andata a buon fine
        printf("Errore nell'apertura di uno dei file\n");
        return 0;
    }

    int ch1, ch2;

    do {
    //leggo carattere per carattere i file
        ch1 = fgetc(f1);
        ch2 = fgetc(f2);

    //confronto carattere per carattere i file
        if (ch1 != ch2) {
            fclose(f1);
            fclose(f2);
            return 0; // file diversi
        }

    } while (ch1 != EOF && ch2 != EOF);  // il ciclo si interrompe al termine di uno dei file (o entrambi)

    fclose(f1);
    fclose(f2);
    return 1; // file uguali
}

int main() {
    // Eseguo il programma in modalità test con input da file
    int esito;

    //  TEST 1
    //per far funzionare system sia su Windows che su Unix/Linux
    #ifdef _WIN32
        esito = system("main.exe --test < test\\test_case_T1.txt > test\\test_result_T1.txt"); // (Windows)
    #else
        esito = system("./main --test < test/test_case_T1.txt > test/test_result_T1.txt"); // (Unix/Linux)
    #endif

    if (esito != 0) {
        printf("[✗] Errore nell'esecuzione del programma principale\n");
        return 1;
    }

    // Confronta l'output generato con l'oracolo
    if (confronta_file("test/test_result_T1.txt", "test/test_oracle_T1.txt")) {
        printf("Test T1 superato\n");
    } else {
        printf("Test T1 fallito\n");
    }

    //TEST 2
    #ifdef _WIN32
        esito = system("main.exe --test < test\\test_case_T2.txt > test\\test_result_T2.txt");
    #else
        esito = system("./main --test < test/test_case_T2.txt > test/test_result_T2.txt");
    #endif

    if (esito != 0) {
        printf("Errore nell'esecuzione del programma principale (T2)\n");
    } else if (confronta_file("test/test_result_T2.txt", "test/test_oracle_T2.txt")) {
        printf("Test T2 superato\n");
    } else {
        printf("Test T2 fallito\n");
    }

    //TEST T3
    #ifdef _WIN32
        esito = system("main.exe --test < test\\test_case_T3.txt > test\\test_result_T3.txt");
    #else
        esito = system("./main --test < test/test_case_T3.txt > test/test_result_T3.txt");
    #endif

    if (esito != 0) {
        printf("Errore nell'esecuzione del programma principale (T3)\n");
    } else if (confronta_file("test/test_result_T3.txt", "test/test_oracle_T3.txt")) {
        printf("Test T3 superato\n");
    } else {
        printf("Test T3 fallito\n");
    }

    return 0;
}