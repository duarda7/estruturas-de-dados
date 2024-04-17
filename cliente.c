#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

struct Clientes {
    char nome[30];
    float valorconta;
};

Clientes* criaLista(int n){
    Clientes * v= (Clientes*)malloc(n*sizeof)(Clientes));
    return v;
}

void lerClientes (int n, Clientes *v){
    printf ("informe os dados do cliente:\n");
    int i;
    for (i = 0; i<n; i++){
        printf ("informe os dados do cliente %d;\n", i + 1);
        scanf ("%d %s %f", &v[i].nome, v[i].valorconta);
    }
}

void imprimeClientes (int n, Clientes *v){
    printf ("imprimindo os clientes:\n");
int i;
for (i=0; i<n; i++) {
    printf ("%d %s %f", v[i].nome, v[i].valorconta);
}
}