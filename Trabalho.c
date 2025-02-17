#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MESAGEM 100
#define MAX_CONTAS 100
#define MAX_USUARIO 20
#define MAX_SENHA 20

typedef struct 
{
    char Mensagem[MAX_MESAGEM];
    char usuario[MAX_USUARIO];
    char senha[MAX_SENHA];
    
} Conta;

void criptografar(char *texto) 
{
    while (*texto) 
    {
        *texto = *texto + 4;
        texto++;
    }
}

void descriptografar(char *texto) 
{
    while (*texto) 
    {
        *texto = *texto - 4;
        texto++;
    }
}

void registrar() 
{
    FILE *arquivo;
    Conta contas[MAX_CONTAS];
    int num_contas = 0;
    char usuario[MAX_USUARIO];
    char senha[MAX_SENHA];

    arquivo = fopen("contas.txt", "a+");
    if (arquivo == NULL) 
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%s %s\n", contas[num_contas].usuario, contas[num_contas].senha) == 2) 
    {
        descriptografar(contas[num_contas].usuario);
        descriptografar(contas[num_contas].senha);
        num_contas++;
    }

    system("cls"); 
    printf("Digite o nome do usuario:\n");
    scanf("%s", usuario);
    system("cls");
    printf("Digite a senha:\n");
    scanf("%s", senha);
    system("cls");

    strcpy(contas[num_contas].usuario, usuario);
    strcpy(contas[num_contas].senha, senha);

    criptografar(usuario);
    criptografar(senha);

    fprintf(arquivo, "%s %s\n", usuario, senha);

    printf("Conta registra com sucesso!\n\n\n");
    system("pause");

    fclose(arquivo);
}

int login(char *usuario_logado) 
{
    FILE *arquivo;
    Conta contas[MAX_CONTAS];
    int num_contas = 0;
    char usuario[MAX_USUARIO];
    char senha[MAX_SENHA];

    arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) 
    {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fscanf(arquivo, "%s %s\n", contas[num_contas].usuario, contas[num_contas].senha) == 2) 
    {
        descriptografar(contas[num_contas].usuario);
        descriptografar(contas[num_contas].senha);
        num_contas++;
    }

    fclose(arquivo);

    system("cls");
    printf("Digite o nome do usuario:\n");
    scanf("%s", usuario);
    system("cls");
    printf("Digite a senha:\n");
    scanf("%s", senha);
    system("cls");

    for (int i = 0; i < num_contas; i++) 
    {
        if (strcmp(contas[i].usuario, usuario) == 0 && strcmp(contas[i].senha, senha) == 0) 
        {
            printf("Login realizado com sucesso!\n\n\n");
            system("pause");
            strcpy(usuario_logado, usuario);
            return 1;
        }
    }

    printf("Usuario ou senha incorretos!\n");
    system("pause");
    return 0;
}

void Escrever_Mensagem(char *usuario_logado)
{
    FILE *arquivo;
    char nome_arquivo[40];
    criptografar(usuario_logado);
    sprintf(nome_arquivo, "%s_mensagem.txt", usuario_logado);
    descriptografar(usuario_logado);
    arquivo = fopen(nome_arquivo, "a+");
    if (arquivo == NULL) 
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char mensagem[MAX_MESAGEM];
    system("cls");
    printf("Digite a mensagem:\n");
    scanf(" %[^\n]s", mensagem);
    system("cls");

    criptografar(mensagem);

    fprintf(arquivo, "%s\n", mensagem);
    printf("Mensagem armazenado com sucesso!\n\n\n");
    system("pause");
    fclose(arquivo);
}

void Procurar_Mensagem(char *usuario_logado)
{
    FILE *arquivo;
    char nome_arquivo[40];
    char mensagem[MAX_MESAGEM];
    char linha[MAX_MESAGEM];
    int mensagem_encontrada = 0; 
    criptografar(usuario_logado);
    sprintf(nome_arquivo, "%s_mensagem.txt", usuario_logado);
    descriptografar(usuario_logado);
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    system("cls");
    printf("Digite a mensagem que deseja encontrar:\n");
    scanf(" %[^\n]", mensagem);
    system("cls");

    printf("Procurando mensagem '%s':\n", mensagem);
    while (fgets(linha, MAX_MESAGEM, arquivo) != NULL)
    {
        
        char linha_decriptada[MAX_MESAGEM];
        strcpy(linha_decriptada, linha);
        descriptografar(linha_decriptada);
        if (strstr(linha_decriptada, mensagem) != NULL)
        {
            printf("Mensagem encontrada!\n\n\n");
            mensagem_encontrada = 1; 
            break; 
        }
    }

    if (!mensagem_encontrada) 
    {
        printf("Mensagem nao encontrada!\n\n\n");
    }

    system("pause");
    fclose(arquivo);
}

int main() 
{
    int escolha, escolha_2;
    char usuario_logado[MAX_USUARIO];

    do {
        system("cls");
        printf("+-----------------------------------+\n");
        printf("| 1 Registrar conta                 |\n");
        printf("| 2 Fazer login                     |\n");
        printf("| 3 Sair                            |\n");
        printf("+-----------------------------------+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) 
        {
            case 1:
                registrar();
                break;
            case 2:
                if (login(usuario_logado)) 
                {
                    do {
                        system("cls");
                        printf(" Usuario: %s\n",usuario_logado);
                        printf("+-----------------------------------+\n");
                        printf("| 1 Escrever Mensagem               |\n");
                        printf("| 2 Procurar Mensagem               |\n");
                        printf("| 3 Sair                            |\n");
                        printf("+-----------------------------------+\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &escolha_2);
                        switch (escolha_2) 
                        {
                            case 1:
                            Escrever_Mensagem(usuario_logado);
                            break;
                            case 2:
                            Procurar_Mensagem(usuario_logado);
                            break;
                            default:
                            break;
                        }
                    } while (escolha_2 != 3);
                }
                break;
            default:
            break;
        }
    } while (escolha != 3);

    return 0;
}