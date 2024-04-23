#ifndef cliente.h
#define cliente.h

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    char email[100];
    struct Node* next;
} Node;

void printRaffleBoard(int board[10][10]);
Node* createNode(char* email);
void cadastrar(Node** head, char* email);
void listar(Node* head);
void buscar(Node* head, char* email);
void excluir(Node** head, char* email);
void editarEmail(Node* head, char* emailAntigo, char* novoEmail);
void ordenarLista(Node** head);
void generateBoleto(float valorTotal);

#endif 
