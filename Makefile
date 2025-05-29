#  Compatibile con Windows e Unix/Linux
#
#  Comandi utili:
#    make         → compila il programma principale (main)
#    make test    → esegue la suite di test (test_suite)
#    make clean   → rimuove gli eseguibili compilati
#
#  Per eseguire manualmente:
#   ./main.exe     (su Windows)
#   ./main         (su Linux/macOS)
#

ifeq ($(OS),Windows_NT)
	EXE_EXT = .exe
else
	EXE_EXT =
endif

MAIN = main$(EXE_EXT)
TEST = test_suite$(EXE_EXT)

$(MAIN): main.c attivita.c lista_attivita.c
	gcc main.c attivita.c lista_attivita.c -o $(MAIN)

$(TEST): test_suite.c
	gcc test_suite.c -o $(TEST)

test: $(TEST)
	./$(TEST)

clean:
	rm -f main.exe test_suite.exe main test_suite
