all:
	gcc -o main main.c attivita.c lista_attivita.c

clean:
	rm -f main