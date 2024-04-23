#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <windows.h>



void printRaffleBoard(int board[10][10]) {
    printf("===================================================\n");
    printf("|*                Rifa da Sorte                  *|\n");
    printf("===================================================\n");

    for (int i = 0; i < 10; i++) {
        printf("|");
        for (int j = 0; j < 10; j++) {
            printf(" %2d |", board[i][j]);
        }
        printf("\n---------------------------------------------------\n");
    }
}

void generateBoleto(float valorTotal);


typedef struct Node {
    char email[100];
    struct Node* next;
} Node;


Node* createNode(char* email) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->email, email);
    newNode->next = NULL;
    return newNode;
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

void editarEmail(Node* head, char* emailAntigo, char* novoEmail);


int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    char nome[100];
    char plano;
    float dados_utilizados, valor_total, dados;
    int opcao_menu, opcao2, opcao3;
    int found_index = -1;
    char login_adm[] = "admin";
    char senha_adm[] = "admin123";
    char login_digitado[100], senha_digitada[100];
    char email[80];
    char emails_cadastrados[10][80]; 
    int num_emails = 0; 
    int prizeNumber; 
    int emailValid = 0; 
Node* head = NULL;
    

    printf(" Olá, querido cliente! Você está acessando a Ufersa.NET \n");
    printf(" Vamos iniciar realizando o seu login!\n");
    printf("--------------------------------------------------------\n");
    printf(" Digite o nome de usuário:\n");
    scanf("%s", login_digitado);

    printf("Digite a senha:\n");
    scanf("%s", senha_digitada);
    printf("-----------------------------------------------------\n");

    #ifdef _WIN32
        Sleep(2000);
#else
        sleep(2); 
#endif
        system("cls || clear");
    while (1) {
        emailValid = 0; 
        printf("\nSelecione uma opção:\n");
        printf("-------------------------------------------------------\n");
        printf("|1. Cadastrar Email                                   |\n");
        printf("|                                                     |\n");
        printf("|2. Listar Emails Cadastrados                         |\n");
        printf("|                                                     |\n");
        printf("|3. Continuar para o Menu Principal                   |\n");
        printf("|                                                     |\n");
        printf("|4. Buscar Email                                      |\n");
        printf("|                                                     |\n");
        printf("|5. Editar Email Cadastrado                           |\n");
        printf("|                                                     |\n");
        printf("|6. Excluir Email Cadastrado                          |\n");
        printf("-------------------------------------------------------\n"); 
        printf("Opção: ");
        scanf("%d", &opcao_menu);

#ifdef _WIN32
        Sleep(2000);
#else
        sleep(2); 
#endif
        system("cls || clear");
        switch (opcao_menu) {
            case 1:
                printf("Digite o email a ser cadastrado: ");
                scanf("%s", email);
                cadastrar(&head, email);
                break;

#ifdef _WIN32
                Sleep(2000);
#else
                sleep(2); 
#endif
                system("cls || clear");
                if (emailValid == 0) {
                    printf("Opss... Email inválido! Certifique-se de que o email inserido contenha '@' e tenha no máximo 79 caracteres.\n");
                } else {
                    int emailExiste = 0;
                    for (int i = 0; i < num_emails; i++) {
                        if (strcmp(emails_cadastrados[i], email) == 0) {
                            emailExiste = 1;
                            break;
                        }
                    }

                    if (emailExiste) {
                        printf("Email já cadastrado no sistema.\n");
                    } else {
                        if (num_emails < 10) {
                            strcpy(emails_cadastrados[num_emails], email);
                            num_emails++;
                            printf("Email cadastrado com sucesso!\n");
                        } else {
                            printf("Limite de emails cadastrados atingido.\n");
                        }
                    }
                }
                break;

#ifdef _WIN32
                Sleep(2000);
#else
                sleep(2); 
#endif
                system("cls || clear");
            case 2:
                
               listar(head);
                break;

#ifdef _WIN32
                Sleep(2000);
#else
                sleep(2); 
#endif
                system("cls || clear");
            case 3:
               
                printf("\nRedirecionando para o Menu Principal...\n");
                break;

#ifdef _WIN32
                Sleep(2000);
#else
                sleep(2); 
#endif
                system("cls || clear");
                case 4:
                
                printf("Digite o email a ser buscado: ");
                scanf("%s", email);
                buscar(head, email);
                break;
                case 5:
     char novoEmail[100]; // Declaração da variável novoEmail
    printf("Digite o email a ser editado: ");
    scanf("%s", email);
    printf("Digite o novo email: ");
    scanf("%s", novoEmail); // Utilizando a variável novoEmail
    editarEmail(head, email, novoEmail);
    break;
    
                case 6:
    printf("Digite o email a ser excluído: ");
                scanf("%s", email);
                excluir(&head, email);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao_menu == 3) {
            break; 
        }
    }




    if (strcmp(login_digitado, login_adm) == 0 && strcmp(senha_digitada, senha_adm) == 0) {
        printf("Oba! Login realizado com sucesso.\n");
        printf("Entrando no sistema...\n");
        printf("                                       \n");
        #ifdef _WIN32
        Sleep(2000); 
#else
        sleep(2); 
#endif
        int raffleBoard[10][10];
        int nextRaffleNumber = 1;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                raffleBoard[i][j] = nextRaffleNumber++;
            }
        }

        prizeNumber = rand() % 100 + 1;
        #ifdef _WIN32
        Sleep(2000); 
#else
        sleep(2); 
#endif
        system("cls || clear");
        
        
            printf("=====================================================\n");
            printf("*           Bem-vindo ao UFERSA.NET                 *\n");
            printf("=====================================================\n");
            printf("                                                    \n");
            printf("                                                     \n");
            
            do {
            printf("-----------------------------------------------------\n");
            printf("|              O que deseja fazer?                  |\n");
            printf("|                                                   |\n");
            printf("| 1 - Escolha seu Plano                             |\n");
            printf("|                                                   |\n");
            printf("| 2 - Tipos de pagamento                            |\n");
            printf("|                                                   |\n");
            printf("| 3 - Sobre a Internet                              |\n");
            printf("|                                                   |\n");
            printf("| 4 - Formas de Contato                             |\n");
            printf("|                                                   |\n");
            printf("| 5 - Participar do Sorteio *Viagem para Gramado*   |\n");
            printf("|                                                   |\n");
            printf("| 6 - Sair                                          |\n");
            printf("|                                                   |\n");
            printf("-----------------------------------------------------\n");
            printf("                                                    \n");
            printf("Informe a opção desejada: \n");
            scanf("%d", &opcao2);
            printf("                                                    \n");
        #ifdef _WIN32
        Sleep(2000); 
#else
        sleep(2); 
#endif
        system("cls || clear");
            switch (opcao2) {
                case 1:
                    printf("======================================================\n");
                    printf("|              Escolha seu plano:                    |\n");
                    printf("-----------------------------------------------------\n");
                    printf("|                                                    |\n");
                    printf("|   B - Básico (10%% de desconto)                     |\n");
                    printf("|                                                    |\n");
                    printf("|   I - Intermediário (20%% de desconto)              |\n");
                    printf("|                                                    |\n");
                    printf("|   P - Premium (30%% de desconto)                    |\n");
                    printf("|                                                    |\n");
                    printf("======================================================\n");
                    printf("                                                    \n");
                    printf("Digite a sua escolha: \n");
                    scanf(" %c", &plano);

                    printf("-----------------------------------------------------\n");
                    printf("Informe a quantidade de dados utilizados (em MB): \n");
                    scanf("%f", &dados);

                    switch (plano) {
                        case 'B':
                            valor_total = dados * 0.30;
                            break;
                        case 'I':
                            valor_total = dados * 0.60;
                            break;
                        case 'P':
                            valor_total = dados * 0.90;
                            break;
                        default:
                            valor_total = -1;
                    }

                    if (valor_total >= 0) {
                        printf("-----------------------------------------------------\n");
                        printf("*       O valor total da sua conta é R$ %.2f       *\n", valor_total);
                        printf("-----------------------------------------------------\n");
                        printf("                                                   \n");
                        #ifdef _WIN32
        Sleep(2000); 
#else
        sleep(2); 
#endif
        system("cls || clear");
                        printf("                                                    \n");
                
                    } else {
                        printf("Plano inválido. Por favor, escolha um plano válido. (B, I ou P).\n");
                         printf("                                                   \n");
                    }
                    break;
                case 2:
                    printf("-----------------------------------------------------\n");
                    printf("|           Tabela de Tipos de Pagamento            |\n");
                    printf("-----------------------------------------------------\n");
                    printf("| 1 - Cartão de Crédito                             |\n");
                    printf("|                                                   |\n");
                    printf("| 2 - Boleto Bancário                               |\n");
                    printf("|                                                   |\n");
                    printf("| 3 - PIX                                           |\n");
                    printf("|                                                   |\n");
                    printf("-----------------------------------------------------\n");
                    printf("                                                   \n");
                    printf("Digite o número do tipo de pagamento desejado:\n ");
                    scanf("%d", &opcao3);
                    #ifdef _WIN32
        Sleep(2000);
#else
        sleep(2); 
#endif
        system("cls || clear");

                    switch (opcao3) {
                        case 1:
                        	printf("================================================================================\n");
                            printf("Tipo de pagamento selecionado: Cartão de Crédito\n");
                            printf("Prezado cliente, como o sr.(a) escolheu a opção de pagamento cartão de crédito\n");
                            printf("pedimos que dirija-se até a unidade de atendimento mais próxima.   \n");
                            printf("Essa medida é tomada por razões de segurança.             \n");
                            printf("================================================================================\n");
                            printf("                                                 \n");
                            #ifdef _WIN32
        Sleep(4000);
#else
        sleep(4); 
#endif
        system("cls || clear");
                            break;
                        case 2:
                            printf("Tipo de pagamento selecionado: Boleto Bancário\n");
                            printf("                                                 \n");
                            printf("Valor total da conta: R$ %.2f\n", valor_total);
                            generateBoleto(valor_total);
                            printf("                                                 \n");
                            #ifdef _WIN32
        Sleep(5000);
#else
        sleep(5); 
#endif
        system("cls || clear");
                            break;
                        case 3:
                            printf("Tipo de pagamento selecionado: PIX\n");
                            printf("                                  \n");
                            printf("====================================\n");
                            printf("*           CHAVE PIX              *\n");
                            printf("|         (88)9 0101 0202          |\n");
                            printf("|        PROVEDOR UFERSA NET       |\n");
                            printf("|        BANCO DE BRASIL           | \n");
                            printf("====================================\n");
                            printf("                                                 \n");
                            #ifdef _WIN32
        Sleep(4000);
#else
        sleep(4); 
#endif
        system("cls || clear");
                            break;
                        default:
                            printf("Opção inválida. Digite um número válido (1, 2 ou 3).\n");
                            printf("                                                 \n");
                            printf("                                                 \n");
                    }
                    break;
                    printf("                                                 \n");
                    #ifdef _WIN32
        Sleep(2000); 
#else
        sleep(2);
#endif
        system("cls || clear");
                case 3:
                    printf(" +-------------------------------------------+ \n");
                    printf(" |   Tabela de Informações - Internet Rápida | \n");
                    printf(" |                                           |\n");
                    printf(" +-------------------------------------------+ \n");
                    printf(" | Velocidade    |   Download   |   Upload   | \n");
                    printf(" |  (em Mbps)    |   (em Mbps)  |  (em Mbps) | \n");
                    printf(" +-------------------------------------------+ \n");
                    printf(" |   50          |     50       |     25     | \n");
                    printf(" |               |              |            | \n");
                    printf(" |   100         |    100       |     50     | \n");
                    printf(" |               |              |            | \n");
                    printf(" |   200         |    200       |    100     | \n");
                    printf(" |               |              |            | \n");
                    printf(" |   300         |    300       |    150     | \n");
                    printf(" |               |              |            | \n");
                    printf(" |   500         |    500       |    250     | \n");
                    printf(" |               |              |            | \n");
                    printf(" |   1000        |   1000       |    500     | \n");
                    printf(" |               |              |            |\n");
                    printf(" +-------------------------------------------+ \n");
                    printf("                                           \n");
                    printf("                                           \n");
                    #ifdef _WIN32
        Sleep(3000);
#else
        sleep(3); 
#endif
        system("cls || clear");
                    break;
                    printf("                                           \n");
                    
                case 4:
                    printf("=========================================================\n");
                    printf("|        Tabela de Formas de Contato - UfersaNet        |\n");
                    printf("---------------------------------------------------------\n");
                    printf("|    Forma de Contato |      Descrição                  |\n");
                    printf("---------------------------------------------------------\n");
                    printf("|   Telefone          |         0800 7447               |\n");
                    printf("|                     |                                 |\n");
                    printf("|   E-mail            |     ufersanet@gmail.com         |\n");
                    printf("|                     |                                 |\n");
                    printf("|   Redes Sociais     |     @ufersanet.oficial          |\n");
                    printf("|                     |                                 |\n");
                    printf("|   Suporte Técnico   |     suporteufnet.com.br         |\n");
                    printf("|                     |                                 |\n");
                    printf("=========================================================\n");   
                     printf("                                                    \n");
                     #ifdef _WIN32
        Sleep(4000);
#else
        sleep(4); 
#endif
        system("cls || clear");
                    break;
            #ifdef _WIN32
        Sleep(3000); 
#else
        sleep(3); 
#endif
        system("cls || clear");
           case 5:
           	 printf("                                                    \n");
                    printRaffleBoard(raffleBoard);

                    int chosenNumber;
                    printf("Escolha um número da rifa (1 a 100): ");
                    scanf("%d", &chosenNumber);

                    if (chosenNumber >= 1 && chosenNumber <= 100) {
                        printf("Ok %s! Você escolheu o número %d.\n", nome, chosenNumber);
                         printf(" Que rufem os tambores...  \n");
                         #ifdef _WIN32
        Sleep(3000); 
#else
        sleep(3); 
#endif
                          printf("                                                    \n");
                        printf("O número vencedor: %d\n", prizeNumber);
                    

                        if (chosenNumber == prizeNumber) {
                            printf("Parabéns! Você ganhou uma viagem para Gramado!\n");
                            printf("                                                    \n");
                        } else {
                            printf("Poxa, sinto muito... Não foi dessa vez!\n");
                            printf("                                                    \n");
                        }
                    } else {
                        printf("Número inválido. Escolha um número de 1 a 100.\n");
                        printf("                                                    \n");
                    } 
					#ifdef _WIN32
        Sleep(6000);
#else
        sleep(6); 
#endif
        system("cls || clear");
                    break;
                    printf("                                                    \n");
                    
                case 6:
                	printf("Até breve, volte sempre!\n");
                	printf("                                                 \n");
                    printf("Desconectando...\n");
                    #ifdef _WIN32
        Sleep(3000); 
#else
        sleep(3); 
#endif
                    printf("                                                    \n");
                    printf("Usuário desconectado! \n");
                    break;
                default:
                    printf("Opção inválida. Digite uma opção válida.\n");
                    printf("                                                    \n");
            }
        } while (opcao2 != 6);
    } else {
        printf("Ops... Login ou senha incorretos.\n");
        printf("Não foi possivel acessar o sistema, tente novamente!\n");
        printf("                                                    \n");
    }

    return 0;
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
