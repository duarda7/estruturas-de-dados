#include "cliente.h"

void printRaffleBoard(int board[10][10]) {
    printf("===================================================\n");
    printf("|*                Rifa da Sorte                  *|\n");
    printf("===================================================\n");

   int i, j;
for (i = 0; i < 10; i++) {
    printf("|");
    for (j = 0; j < 10; j++) {
        printf(" %2d |", board[i][j]);
    }
    printf("\n---------------------------------------------------\n");
}

}

Node* createNode(char* email) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->email, email);
    newNode->next = NULL;
    return newNode;
}

void cadastrar(Node** head, char* email) {
    if (strchr(email, '@') == NULL) {
        printf("Email inválido! O email deve conter o caractere '@'.\n");
        return;
    }
    
    Node* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            printf("Email já cadastrado no sistema.\n");
            return;
        }
        temp = temp->next;
    }
    
    Node* newNode = createNode(email);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Email %s cadastrado com sucesso!\n", email);
}

void listar(Node* head) {
    if (head == NULL) {
        printf("A lista está vazia.\n");
    } else {
        Node* temp = head;
        printf("Emails da lista:\n");
        while (temp != NULL) {
            printf("%s\n", temp->email);
            temp = temp->next;
        }
    }
}

void buscar(Node* head, char* email) {
    Node* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            printf("Email %s encontrado na lista.\n", email);
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Email %s não encontrado na lista.\n", email);
    }
}

void excluir(Node** head, char* email) {
    Node* temp = *head;
    Node* prev = NULL;

    while (temp != NULL && strcmp(temp->email, email) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Email %s não encontrado na lista. Nada foi excluído.\n", email);
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Email %s excluído da lista.\n", email);
}

void editarEmail(Node* head, char* emailAntigo, char* novoEmail) {
    Node* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->email, emailAntigo) == 0) {
            strcpy(temp->email, novoEmail);
            printf("Email editado com sucesso!\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Email %s não encontrado na lista. Não foi possível editar.\n", emailAntigo);
    }
}

void ordenarLista(Node** head) {
    Node* current = *head;
    Node* index = NULL;
    char temp[100];

    if (*head == NULL) {
        return;
    } else {
        while (current != NULL) {
            index = current->next;

            while (index != NULL) {
                if (strcmp(current->email, index->email) > 0) {
                    strcpy(temp, current->email);
                    strcpy(current->email, index->email);
                    strcpy(index->email, temp);
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void generateBoleto(float valorTotal) {
    printf("\n-----------------------------------------------------\n");
    printf("*                 BOLETO BANCÁRIO                  *\n");
    printf("-----------------------------------------------------\n");
    printf("| Beneficiário: UFERSA.NET                         |\n");
    printf("| Valor a ser pago: R$ %.2f                        |\n", valorTotal);
    printf("| Vencimento: 26/07/2024                           |\n");
    printf("| Código de Barras: 1234 5678 9012 3456 7890       |\n");
    printf("-----------------------------------------------------\n");
}
