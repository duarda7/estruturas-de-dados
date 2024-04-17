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

void deleteEmail(char emails_cadastrados[][80], int *num_emails);

int searchEmail(char emails_cadastrados[][80], int num_emails, const char* email) {
    for (int i = 0; i < num_emails; i++) {
        if (strcmp(emails_cadastrados[i], email) == 0) {
            return i; 
        }
    }
    return -1;
}

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
void salvarEmailsTexto(char emails_cadastrados[][80], int num_emails) {
    FILE *arquivo_texto = fopen("emails.txt", "w");
    if (arquivo_texto != NULL) {
        for (int i = 0; i < num_emails; i++) {
            fprintf(arquivo_texto, "%s\n", emails_cadastrados[i]);
        }
        fclose(arquivo_texto);
    } else {
        printf("Erro ao abrir o arquivo de texto para escrita.\n");
    }
}

int carregarEmailsTexto(char emails_cadastrados[][80]) {
    FILE *arquivo_texto = fopen("emails.txt", "r");
    int num_emails = 0;
    if (arquivo_texto != NULL) {
        while (fscanf(arquivo_texto, "%79s", emails_cadastrados[num_emails]) == 1) {
            num_emails++;
        }
        fclose(arquivo_texto);
    } else {
        printf("Erro ao abrir o arquivo de texto para leitura.\n");
    }
    return num_emails;
}

void salvarEmailsBinario(char emails_cadastrados[][80], int num_emails) {
    FILE *arquivo_binario = fopen("emails.bin", "wb");
    if (arquivo_binario != NULL) {
        fwrite(emails_cadastrados, sizeof(emails_cadastrados[0]), num_emails, arquivo_binario);
        fclose(arquivo_binario);
    } else {
        printf("Erro ao abrir o arquivo binário para escrita.\n");
    }
}

int carregarEmailsBinario(char emails_cadastrados[][80]) {
    FILE *arquivo_binario = fopen("emails.bin", "rb");
    int num_emails = 0;
    if (arquivo_binario != NULL) {
        while (fread(emails_cadastrados[num_emails], sizeof(emails_cadastrados[0]), 1, arquivo_binario) == 1) {
            num_emails++;
        }
        fclose(arquivo_binario);
    } else {
        printf("Erro ao abrir o arquivo binário para leitura.\n");
    }
    return num_emails;
}
int buscaEmail(char emails_cadastrados[][80], int num_emails, const char *emailBuscado) {
    for (int i = 0; i < num_emails; i++) {
        if (strcmp(emails_cadastrados[i], emailBuscado) == 0) {
            return i; 
        }
    }
    return -1; 
}
void editEmail(char emails_cadastrados[][80], int num_emails) {
    char email_antigo[80], novo_email[80];
    int indice_email;

    printf("Digite o email que deseja editar:\n");
    scanf("%s", email_antigo);

    indice_email = searchEmail(emails_cadastrados, num_emails, email_antigo);

    if (indice_email != -1) {
        printf("Digite o novo email:\n");
        scanf("%s", novo_email);

        strcpy(emails_cadastrados[indice_email], novo_email);
        printf("Email editado com sucesso!\n");
    } else {
        printf("O email informado não foi encontrado no sistema!\n");
    }
}

void deleteEmail(char emails_cadastrados[][80], int *num_emails) {
    char email_excluir[80];
    int indice_email_excluir;

    printf("Digite o email que deseja excluir:\n");
    scanf("%s", email_excluir);

    indice_email_excluir = searchEmail(emails_cadastrados, *num_emails, email_excluir);

    if (indice_email_excluir != -1) {
        for (int i = indice_email_excluir; i < *num_emails - 1; i++) {
            strcpy(emails_cadastrados[i], emails_cadastrados[i + 1]);
        }
        (*num_emails)--;
        printf("Email excluído com sucesso!\n");
    } else {
        printf("Email não encontrado no sistema.\n");
    }
}

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
                printf("Digite o seu email:\n");
                scanf("%s", email);

                for (int i = 0; email[i] != '\0'; i++) {
                    if (email[i] == '@' && strlen(email) < 80) {
                        emailValid = 1;
                        break;
                    }
                }

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
                
                printf("\nEmails cadastrados:\n");
                for (int i = 0; i < num_emails; i++) {
                    printf("%d. %s\n", i + 1, emails_cadastrados[i]);
                }
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
                
                printf("Digite o email que deseja buscar:\n");
                scanf("%s", email);
                found_index = searchEmail(emails_cadastrados, num_emails, email);
                if (found_index >= 0) {
                    printf("Email encontrado na posição %d.\n", found_index + 1);
                } else {
                    printf("Email não encontrado no sistema.\n");
                }
                break;
                case 5:
    editEmail(emails_cadastrados, num_emails);
    break;
    
                case 6:
    deleteEmail(emails_cadastrados, &num_emails);
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