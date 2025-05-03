#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_attivita.h"

struct nodo {
    attivita dato;
    struct nodo* next;
};