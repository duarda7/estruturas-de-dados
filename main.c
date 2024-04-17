#include <stdio.h>
#include "cliente.h"

int main (void){
    int n;
    char Cliente[5];
    printf ("Informe a quantidade de clientes:\n");
    scanf ("%d", &n);
    Cliente *v = criaLista(n);
    lerClientes(n, v);
    imprimeClientes(n, v);
    
    return 0;
}