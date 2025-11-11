#include "projeto.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define TAMANHO_MAXIMO_MORADA 40
#define TAMANHO_MAXIMO_NOME 30

int main() {
    int op = 0;
    int *ptr, num_clientes = 0;
    ptr = &num_clientes;
    char nome_completo[TAMANHO_MAXIMO_NOME];
    char morada[TAMANHO_MAXIMO_MORADA];
    long int telemovel, nif;
    int resposta = 1;
    cliente *clientes = NULL;  // Initialize clientes pointer to NULL

    FILE *file = fopen("data_1000.csv", "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir ficheiro.\n");
        return 1;
    }

    // Read client data from the file
    while (!feof(file)) {
        // Allocate memory for one more cliente struct
        clientes = realloc(clientes, (num_clientes + 1) * sizeof(cliente));
        if (!clientes) {
            fprintf(stderr, "Erro ao alocar memoria.\n");
            fclose(file);
            return 1;
        }

        // Read client data into the newly allocated struct
        fscanf(file, "%ld,%29[^,],%ld,%39[^\n]%*c",
                   &clientes[num_clientes].nif,
                   clientes[num_clientes].nome_completo,
                   &clientes[num_clientes].telemovel,
                   clientes[num_clientes].morada);
        num_clientes++;  // Increment the number of clients read
    }  
    fclose(file);
    
    do{

        menu();
        printf("Resposta: ");

        if (scanf(" %d", &op) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        switch (op) {
            case 1:
                do {
                clientes_visualizar(clientes, ptr);
                printf("Deseja visualizar mais algum cliente?\n1 - Sim\n2 - Nao\nR: ");
                scanf(" %d", &resposta);

                } while (resposta == 1);
                break;
            case 2:
                do {
                printf("Vamos adicionar um novo cliente !!\n");
                printf("Nome completo: ");
                if (scanf("%s", nome_completo) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                strToLower(nome_completo);
                printf("Morada: ");
                if (scanf(" %s", morada) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                printf("Telemovel: ");
                if (scanf(" %ld", &telemovel) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                printf("NIF: ");
                if (scanf(" %ld", &nif) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                
                adicionar_clientes(clientes, ptr, nif, telemovel, nome_completo, morada);
                printf("\nDeseja adicionar mais algum cliente?\n1 - Sim\n2 - Nao\nR: ");
                scanf(" %d", &resposta);

                } while (resposta == 1);
                break;
            case 3:
                do {
                printf("Digite o nome completo do cliente desejado: ");
                if (scanf(" %s", nome_completo) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                
                editar_clientes(clientes, ptr, nome_completo);

                printf("Deseja editar mais algum cliente?\n1 - Sim\n2 - Nao\nR: ");
                scanf(" %d", &resposta);

                } while (resposta == 1);
                break;
            case 4:
                do {
                printf("Digite o nome completo do cliente desejado: ");
                if (scanf(" %s", nome_completo) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                anular_clientes(clientes, ptr, nome_completo);
                printf("Deseja anular mais algum cliente?\n1 - Sim\n2 - Nao\nR: ");
                scanf(" %d", &resposta);

                } while (resposta == 1);
                break;
            case 5:
                printf("Hasta la vista !!\n");
                free(clientes);
                return 0;
            default:
                printf("Opcao invalida. Por favor insira um numero correto...\n");
                break;
        }
    } while(op != 5);

    free(clientes);
    return 0;
}