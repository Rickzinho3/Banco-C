#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Declarações antecipadas
int inicio();
int Verify(const char *nome, const char *email);

//? Função menu
void menu(void){
    printf("\n[1] Depositar\n[2] Sacar\n[3] Saldo\n[4] Adicionar na carteira\n[5] Sair\n"); 
}

//? Verificr saldo atual
float SaldoAtual(float saldo, float deposito){

    printf("\nSeu saldo atual: R$%.2f\n", saldo);
    printf("\nValor depositado: R$%.2f\n", deposito);

    return saldo;
}

//? Adicionar à  carteira
float Adicionar(float saldo){

    float add;

    printf("\ndigite quanto deseja adicionar R$ ");
    scanf("%f", &add);

    saldo += add;

    return saldo;
}

//? Depósito
float Depositar(float *saldo, float *deposito){

    float valor;

    printf("\nDigite quanto deseja depositar R$ ");
    scanf("%f", &valor);

    if(valor > *saldo){
        printf("\nSaldo insuficiente.\n");
    } else{
        *saldo -= valor;
        *deposito += valor;
        printf("\nDepositado com sucesso!\n");
    }

    return *saldo;
}

//? Saque
float Sacar(float *saldo, float *deposito){
    float valor;

    printf("\nDigite quanto deseja sacar R$ ");
    scanf("%f", &valor);

    if(valor > *deposito){
        printf("\nSaldo insuficiente.\n");
    } else{
        *saldo += valor;
        *deposito -= valor;
        printf("\nSaque realizado com sucesso!\n");
    }

    return *saldo;
}

//! usuario
struct usuario{
    char nome[50];
    char email[50];
};

typedef struct usuario usuario;

//? menu inicio
void menuInicio(void){
    printf("[1] Login\n[2] Cadastro\n[3] Sair\n");
}

// Função para verificar se o usuário existe no arquivo
int Verify(const char *nome, const char *email){
    FILE *file = fopen("Dados.txt", "r");
    char linha[256];
    char nomeArquivo[100];
    char emailArquivo[100];
    
    if(file == NULL){
        printf("Erro ao abrir o arquivo ou arquivo não existe.\n");
        printf("Por favor, cadastre-se primeiro.\n");
        return 0;
    }

    // Remover o \n do final do nome e email
    char nomeTemp[50], emailTemp[50];
    strcpy(nomeTemp, nome);
    strcpy(emailTemp, email);
    
    nomeTemp[strcspn(nomeTemp, "\n")] = '\0';
    emailTemp[strcspn(emailTemp, "\n")] = '\0';

    // Formato esperado no arquivo: "Nome: nome\nE-mail: email\n\n"
    while(fgets(linha, sizeof(linha), file) != NULL) {
        // Verificar se a linha começa com "Nome: "
        if(strncmp(linha, "Nome: ", 6) == 0) {
            // Extrair o nome do arquivo (remover "Nome: ")
            strcpy(nomeArquivo, linha + 6);
            nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
            
            // Ler a próxima linha que deve conter o email
            if(fgets(linha, sizeof(linha), file) != NULL && strncmp(linha, "E-mail: ", 8) == 0) {
                // Extrair o email do arquivo (remover "E-mail: ")
                strcpy(emailArquivo, linha + 8);
                emailArquivo[strcspn(emailArquivo, "\n")] = '\0';
                
                // Comparar nome e email
                if(strcmp(nomeArquivo, nomeTemp) == 0 && strcmp(emailArquivo, emailTemp) == 0) {
                    fclose(file);
                    return 1; // Usuário encontrado
                }
            }
        }
    }
    
    fclose(file);
    return 0; // Usuário não encontrado
}

//? Login
void login(void){
    usuario user;
    
    // Limpar o buffer de entrada
    getchar();

    printf("-------- Login ----------\n");
    printf("Nome: ");
    fgets(user.nome, sizeof(user.nome), stdin);

    printf("Digite seu E-mail: ");
    fgets(user.email, sizeof(user.email), stdin);

    if(Verify(user.nome, user.email)){
        printf("\nLogin bem-sucedido!\n");
        Sleep(1000);
        system("cls");
        inicio();
    } else{
        printf("\nUsuário não encontrado! Verifique seu nome e email ou cadastre-se.\n");
        Sleep(1500);
        system("cls");
    }
}

//? cadastro
void cadastro(void){

    usuario user;
    FILE *file;

    //* Limpar o buffer de entrada
    getchar();

    printf("---------- Cadastro ----------\n");
    printf("Nome: ");
    fgets(user.nome, sizeof(user.nome), stdin);
    user.nome[strcspn(user.nome, "\n")] = '\0';

    printf("Email: ");
    fgets(user.email, sizeof(user.email), stdin);
    user.email[strcspn(user.email, "\n")] = '\0';
    
    printf("\n---------- Concluido ----------\n");
    printf("Nome: %s\nE-mail: %s\n", user.nome, user.email);
    printf("-------------------------------\n");
    
    //* Cria o arquivo de texto
    file = fopen("Dados.txt", "a");
    
    if(file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "Nome: %s\nE-mail: %s\n\n", user.nome, user.email);
    fclose(file);

    printf("\nCadastro realizado com sucesso!\n");
    Sleep(1500);
    system("cls");
}

int inicio(){

    int c;
    float saldo = 0;
    float deposito = 0;

    do{
        menu();

        printf("\n>>> ");
        scanf("%d", &c);

        switch(c){
            case 1:
                Depositar(&saldo, &deposito);
                break;

            case 2:
                Sacar(&saldo, &deposito);
                break;

            case 3:
                SaldoAtual(saldo, deposito);
                break;

            case 4:
                saldo = Adicionar(saldo);
                break;
                
            case 5:
                printf("\nVoltando ao menu principal...\n");
                system("cls");
                return 0;
                break;

            default:
                printf("\nOpção inválida\n");
        }
    } while(1);

    return 0;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    
    int s;

    do{
        menuInicio();

        printf(">>> ");
        scanf("%d", &s);

        switch (s)
        {
        case 1:
            system("cls");
            login();
            break;

        case 2:
            system("cls");
            cadastro();
            break;
        
        case 3:
            printf("\nSaindo...\n");
            Sleep(500);
            printf("Fazendo limpeza...");
            Sleep(500);
            system("cls");
            return 0;
            break;

        default:
            printf("\nOpção inválida\n");
            Sleep(1000);
            system("cls");
            break;
        }

    }while(1);

    return 0;
}