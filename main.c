#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_USUARIOS 1000

typedef struct {
    int id;
    char nome[100];
    char email[100];
    char sexo[10];
    char endereco[100];
    double altura;
    int vacina;
} Usuario;

int numUsuarios = 0;
Usuario usuarios[MAX_USUARIOS];
Usuario backupUsuarios[MAX_USUARIOS];

// Function prototypes
void AbrirMenu();
int AdicionarUsuario();
int EditarUsuario();
int ExcluirUsuario();
int BuscarPorEmail();
int ImprimirUsuarios();
int BackUp();
int RestaurarDados();
int gerarID();

int main() {
    char opcao = ' ';

    while (opcao != '0') {
        AbrirMenu();
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                AdicionarUsuario();
                break;
            case '2':
                EditarUsuario();
                break;
            case '3':
                ExcluirUsuario();
                break;
            case '4':
                BuscarPorEmail();
                break;
            case '5':
                ImprimirUsuarios();
                break;
            case '6':
                BackUp();
                break;
            case '7':
                RestaurarDados();
                break;
            case '0':
                printf("--------Fechando programa--------\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
}

void AbrirMenu() {
    printf("1 - Adicionar um novo usuario\n");
    printf("2 - Editar um Usuario\n");
    printf("3 - Excluir usuario\n");
    printf("4 - Buscar por usuario por Email\n");
    printf("5 - Imprimir todos os usuarios cadastrados\n");
    printf("6 - Fazer Backup dos usuarios\n");
    printf("7 - Restaurar os dados\n");
    printf("0 - Fechar programa\n");
    printf("Digite a opcao escolhida: ");
}

int gerarID() {
    int id;
    int validacao;
    srand(time(NULL));

    do {
        id = rand() % 100000;

        for (int i = 0; i < numUsuarios; i++) {
            if (usuarios[i].id == id) {
                printf("Usuario cadastrado ja existe\n");
                id = 0;
                validacao = 1;
                break;
            } else {
                validacao = 0;
            }
        }
    } while (validacao == 1);

    return id;
}

int AdicionarUsuario() {
    int id, vacina, validacao;
    char nome[100], email[100], sexo[10], endereco[100];
    double altura;

    if (numUsuarios >= MAX_USUARIOS) {
        printf("Numero de usuarios alcançou o limite D:\n");
        return -1;
    }

    printf("Digite seu nome completo: ");
    scanf(" %[^\n]", nome);

    printf("Digite seu email: ");
    scanf(" %[^\n]", email);

    do {
        validacao = 1;
        for (int i = 0; i < strlen(email); i++) {
            if (email[i] == '@') {
                validacao = 0;
                break;
            }
        }

        if (validacao == 1) {
            printf("Email invalido, tente novamente: ");
            scanf(" %[^\n]", email);
        }

    } while (validacao == 1);

    printf("Digite seu sexo (Feminino/Masculino): ");
    scanf(" %[^\n]", sexo);

    printf("Digite seu endereco: ");
    scanf(" %[^\n]", endereco);

    printf("Digite sua altura (em metros): ");
    scanf("%lf", &altura);

    printf("Ja tomou a vacina? (1-Sim / 0-Nao): ");
    scanf("%d", &vacina);

    id = gerarID();

    usuarios[numUsuarios].id = id;
    strcpy(usuarios[numUsuarios].nome, nome);
    strcpy(usuarios[numUsuarios].email, email);
    strcpy(usuarios[numUsuarios].sexo, sexo);
    strcpy(usuarios[numUsuarios].endereco, endereco);
    usuarios[numUsuarios].altura = altura;
    usuarios[numUsuarios].vacina = vacina;

    printf("Usuario adicionado com sucesso!\n");
    printf("ID do usuario: %d\n", id);

    numUsuarios++;

    return 0;
}
int EditarUsuario() {
    int id, opcao;
    int encontrado = 0;
    char novoNome[100], novoEmail[100], novoSexo[10], novoEndereco[100];
    double novaAltura;
    int novaVacina;

    printf("Digite o ID do usuario que deseja editar: ");
    scanf("%d", &id);

    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            encontrado = 1;
            printf("Usuario encontrado!\n");
            printf("O que deseja editar?\n");
            printf("1 - Nome\n");
            printf("2 - Email\n");
            printf("3 - Sexo\n");
            printf("4 - Endereco\n");
            printf("5 - Altura\n");
            printf("6 - Vacina\n");
            printf("Digite a opcao escolhida: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf(" %[^\n]", novoNome);
                    strcpy(usuarios[i].nome, novoNome);
                    break;
                case 2:
                    printf("Digite o novo email: ");
                    scanf(" %[^\n]", novoEmail);
                    strcpy(usuarios[i].email, novoEmail);
                    break;
                case 3:
                    printf("Digite o novo sexo: ");
                    scanf(" %[^\n]", novoSexo);
                    strcpy(usuarios[i].sexo, novoSexo);
                    break;
                case 4:
                    printf("Digite o novo endereco: ");
                    scanf(" %[^\n]", novoEndereco);
                    strcpy(usuarios[i].endereco, novoEndereco);
                    break;
                case 5:
                    printf("Digite a nova altura: ");
                    scanf("%lf", &novaAltura);
                    usuarios[i].altura = novaAltura;
                    break;
                case 6:
                    printf("Digite a nova vacina (1-Sim / 0-Nao): ");
                    scanf("%d", &novaVacina);
                    usuarios[i].vacina = novaVacina;
                    break;
                default:
                    printf("Opcao invalida\n");
                    break;
            }

            printf("Usuario atualizado com sucesso!\n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("Usuario nao encontrado\n");
    }

    return 0;
}

