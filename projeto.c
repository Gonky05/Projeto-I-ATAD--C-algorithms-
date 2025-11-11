#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int comparar_clientes_nif_telemovel(const void *a, const void *b) {
    const cliente *cliente_a = (const cliente *)a;
    const cliente *cliente_b = (const cliente *)b;

    // Compara os NIFs dos clientes
    if (cliente_a->nif < cliente_b->nif) {
        return -1; // Indica que o cliente_a vem antes de cliente_b
    } else if (cliente_a->nif > cliente_b->nif) {
        return 1; // Indica que o cliente_a vem depois de cliente_b
    } else {
        return 0; // Indica que os NIFs são iguais
    }
}
int comparar_clientes(const void *a, const void *b)
{
    const char *cliente_a = *(const char **)a;
    const char *cliente_b = *(const char **)b;
    return strcmp(cliente_a, cliente_b);
}

int procura_cliente_nome_completo_binario(cliente clientes[], int *tamanho, char nome_completo[])
{
    int indice;
    char **clientes_temporarios = malloc(*tamanho * sizeof(char *));
    if (!clientes_temporarios)
    {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os nomes completos para clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        // Alocar memória suficiente para armazenar a string nome_completo
        clientes_temporarios[i] = malloc((strlen(clientes[i].nome_completo) + 1) * sizeof(char));
        if (!clientes_temporarios[i])
        {
            fprintf(stderr, "Erro ao alocar memória para clientes_temporarios[%d].\n", i);
            // Tratar erro, se necessário
            // Libere a memória alocada até este ponto
            for (int j = 0; j < i; j++)
            {
                free(clientes_temporarios[j]);
            }
            free(clientes_temporarios);
            return -1; // Retorne um valor indicativo de erro
        }
        strcpy(clientes_temporarios[i], clientes[i].nome_completo);
    }

    clock_t comeca = clock();
    // Ordenar o array de strings clientes_temporarios
    qsort(clientes_temporarios, *tamanho, sizeof(char *), comparar_clientes);

    // Realizar busca binária no array ordenado clientes_temporarios
    int esquerda = 0;
    int direita = *tamanho - 1;
    int encontrado = 0;
    indice = -1; // Inicialize o índice com um valor inválido

    while (esquerda <= direita)
    {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(clientes_temporarios[meio], nome_completo);

        if (cmp == 0)
        {
            encontrado = 1;
            indice = meio;
            break;
        }
        else if (cmp < 0)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }
    clock_t acaba = clock();
    double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
    printf("Tempo: %f segundos\n", search_time);

    if (!encontrado)
    {
        printf("Nome não encontrado.\n\n");
    }
    else
    {

        return indice;
    }

    // Liberar a memória alocada dinamicamente para cada string em clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        free(clientes_temporarios[i]);
    }
    // Liberar o array de ponteiros para strings clientes_temporarios

    free(clientes_temporarios);

    return -1;
}
int procura_cliente_nome_completo_sequencial(cliente clientes[], int *tamanho, char nome_completo[])
{
    clock_t comeca = clock();
    for (int i = 0; i < *tamanho; i++)
    {
        if (strcmp(clientes[i].nome_completo, nome_completo) == 0)
        {
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome_completo);
            printf("NIF: %ld\n", clientes[i].nif);
            printf("Telemovel: %ld\n", clientes[i].telemovel);
            printf("Morada: %s\n", clientes[i].morada);
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);

            return i;
        }
    }
    return -1;
}
int procura_cliente_nome_completo_ternario(cliente clientes[], int *tamanho, char nome_completo[]){
    char **clientes_temporarios = malloc(*tamanho * sizeof(char *));
    if (!clientes_temporarios)
    {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os nomes completos para clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        clientes_temporarios[i] = malloc((strlen(clientes[i].nome_completo) + 1) * sizeof(char));
        if (!clientes_temporarios[i])
        {
            fprintf(stderr, "Erro ao alocar memória para clientes_temporarios[%d].\n", i);
            // Libere a memória alocada até este ponto
            for (int j = 0; j < i; j++)
            {
                free(clientes_temporarios[j]);
            }
            free(clientes_temporarios);
            return -1; // Retorne um valor indicativo de erro
        }
        strcpy(clientes_temporarios[i], clientes[i].nome_completo);
    }

    clock_t comeca = clock();
    // Ordenar o array de strings clientes_temporarios
    qsort(clientes_temporarios, *tamanho, sizeof(char *), comparar_clientes);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita)
    {
        int terco = (direita - esquerda) / 3;
        int meio1 = esquerda + terco;
        int meio2 = direita - terco;

        int cmp1 = strcmp(clientes_temporarios[meio1], nome_completo);
        int cmp2 = strcmp(clientes_temporarios[meio2], nome_completo);

        if (cmp1 == 0)
        {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes_temporarios[meio1]);
            return meio1; // Encontrou o nome na posição meio1
        }
        else if (cmp2 == 0)
        {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes_temporarios[meio2]);
            return meio2; // Encontrou o nome na posição meio2
        }
        else if (cmp1 < 0)
        {
            esquerda = meio1 + 1; // O nome está à direita de meio1
        }
        else if (cmp2 > 0)
        {
            direita = meio2 - 1; // O nome está à esquerda de meio2
        }
        else
        {
            esquerda = meio1 + 1;
            direita = meio2 - 1;
        }
    }

    // Liberar a memória alocada dinamicamente para cada string em clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        free(clientes_temporarios[i]);
    }
    free(clientes_temporarios);

    return -1; // Nome não encontrado
}
int procura_cliente_nome_completo_por_interpolacao(cliente clientes[], int *tamanho, char nome_completo[])
{
    char **clientes_temporarios = malloc(*tamanho * sizeof(char *));
    if (!clientes_temporarios)
    {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os nomes completos para clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        clientes_temporarios[i] = malloc((strlen(clientes[i].nome_completo) + 1) * sizeof(char));
        if (!clientes_temporarios[i])
        {
            fprintf(stderr, "Erro ao alocar memória para clientes_temporarios[%d].\n", i);
            // Libere a memória alocada até este ponto
            for (int j = 0; j < i; j++)
            {
                free(clientes_temporarios[j]);
            }
            free(clientes_temporarios);
            return -1; // Retorne um valor indicativo de erro
        }
        strcpy(clientes_temporarios[i], clientes[i].nome_completo);
    }

    clock_t comeca = clock();
    // Ordenar o array de strings clientes_temporarios
    qsort(clientes_temporarios, *tamanho, sizeof(char *), comparar_clientes);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita)
    {
        int probe = esquerda + ((double)(direita - esquerda) / (strcmp(clientes_temporarios[direita], clientes_temporarios[esquerda]) + 1)) * (strcmp(nome_completo, clientes_temporarios[esquerda]) - strcmp(clientes_temporarios[esquerda], clientes_temporarios[direita]));

        if (probe < 0 || probe >= *tamanho)
        {
            break;
        }

        int cmp = strcmp(clientes_temporarios[probe], nome_completo);
        if (cmp == 0)
        {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes_temporarios[probe]);
            return probe; // Encontrou o nome na posição probe
        }
        else if (cmp < 0)
        {
            esquerda = probe + 1; // O nome está à direita de probe
        }
        else
        {
            direita = probe - 1; // O nome está à esquerda de probe
        }
    }

    return -1; // Nome não encontrado
}
int procura_cliente_nome_completo(cliente clientes[], int *tamanho, char nome_completo[])
{
    int procura;
    do
    {
        printf("Que procura deseja utilizar?\n1 - Sequencial\n2 - Binaria\n3 - Ternaria\n4 - Por interpolacao\nR: ");
        scanf(" %d", &procura);
    } while (procura > 5 && procura < 0);

    switch (procura)
    {
    case 1:
        int indice = procura_cliente_nome_completo_sequencial(clientes, tamanho, nome_completo);
        if (indice != 1)
        {
            return indice;
        }
        break;

    case 2:
        indice = procura_cliente_nome_completo_binario(clientes, tamanho, nome_completo);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 3:
        indice = procura_cliente_nome_completo_ternario(clientes, tamanho, nome_completo);
        if (indice != 1)
        {
            return indice;
        }
        break;

    case 4:
        indice = procura_cliente_nome_completo_por_interpolacao(clientes, tamanho, nome_completo);
        if (indice != 1)
        {
            return indice;
        }
        break;
    }
    return -1;
}

int procura_cliente_morada_por_interpolacao(cliente clientes[], int *tamanho, char morada[])
{
    char **clientes_temporarios = malloc(*tamanho * sizeof(char *));
    if (!clientes_temporarios)
    {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os nomes completos para clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        clientes_temporarios[i] = malloc((strlen(clientes[i].morada) + 1) * sizeof(char));
        if (!clientes_temporarios[i])
        {
            fprintf(stderr, "Erro ao alocar memória para clientes_temporarios[%d].\n", i);
            // Libere a memória alocada até este ponto
            for (int j = 0; j < i; j++)
            {
                free(clientes_temporarios[j]);
            }
            free(clientes_temporarios);
            return -1; // Retorne um valor indicativo de erro
        }
        strcpy(clientes_temporarios[i], clientes[i].morada);
    }

    clock_t comeca = clock();
    // Ordenar o array de strings clientes_temporarios
    qsort(clientes_temporarios, *tamanho, sizeof(char *), comparar_clientes);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita)
    {
        int probe = esquerda + ((double)(direita - esquerda) / (strcmp(clientes_temporarios[direita], clientes_temporarios[esquerda]) + 1)) * (strcmp(morada, clientes_temporarios[esquerda]) - strcmp(clientes_temporarios[esquerda], clientes_temporarios[direita]));

        if (probe < 0 || probe >= *tamanho)
        {
            break;
        }

        int cmp = strcmp(clientes_temporarios[probe], morada);
        if (cmp == 0)
        {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Morada: %s\n", clientes_temporarios[probe]);
            return probe; // Encontrou o nome na posição probe
        }
        else if (cmp < 0)
        {
            esquerda = probe + 1; // O nome está à direita de probe
        }
        else
        {
            direita = probe - 1; // O nome está à esquerda de probe
        }
    }

    return -1; // Nome não encontrado
}
int procura_cliente_morada_binario(cliente clientes[], int *tamanho, char morada[])
{
    int indice;
    char **clientes_temporarios = malloc(*tamanho * sizeof(char *));
    if (!clientes_temporarios)
    {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        // Tratar erro, se necessário
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os nomes completos para clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        // Alocar memória suficiente para armazenar a string nome_completo
        clientes_temporarios[i] = malloc((strlen(clientes[i].morada) + 1) * sizeof(char));
        if (!clientes_temporarios[i])
        {
            fprintf(stderr, "Erro ao alocar memória para clientes_temporarios[%d].\n", i);
            // Tratar erro, se necessário
            // Libere a memória alocada até este ponto
            for (int j = 0; j < i; j++)
            {
                free(clientes_temporarios[j]);
            }
            free(clientes_temporarios);
            return -1; // Retorne um valor indicativo de erro
        }
        strcpy(clientes_temporarios[i], clientes[i].morada);
    }

    clock_t comeca = clock();
    // Ordenar o array de strings clientes_temporarios
    qsort(clientes_temporarios, *tamanho, sizeof(char *), comparar_clientes);

    // Realizar busca binária no array ordenado clientes_temporarios
    int esquerda = 0;
    int direita = *tamanho - 1;
    int encontrado = 0;
    indice = -1; // Inicialize o índice com um valor inválido

    while (esquerda <= direita)
    {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(clientes_temporarios[meio], morada);

        if (cmp == 0)
        {
            encontrado = 1;
            indice = meio;
            break;
        }
        else if (cmp < 0)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }
    clock_t acaba = clock();
    double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
    printf("Tempo: %f segundos\n", search_time);

    if (!encontrado)
    {
        printf("Nome não encontrado.\n\n");
    }
    else
    {
        printf("Cliente encontrado:\n");
        printf("Nome: %s\n", clientes_temporarios[indice]);
        return indice;
    }

    // Liberar a memória alocada dinamicamente para cada string em clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        free(clientes_temporarios[i]);
    }
    // Liberar o array de ponteiros para strings clientes_temporarios
    free(clientes_temporarios);
    return -1;
}
int procura_cliente_morada_ternario(cliente clientes[], int *tamanho, char morada[]){
    char **clientes_temporarios = malloc(*tamanho * sizeof(char *));
    if (!clientes_temporarios)
    {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os nomes completos para clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        clientes_temporarios[i] = malloc((strlen(clientes[i].morada) + 1) * sizeof(char));
        if (!clientes_temporarios[i])
        {
            fprintf(stderr, "Erro ao alocar memória para clientes_temporarios[%d].\n", i);
            // Libere a memória alocada até este ponto
            for (int j = 0; j < i; j++)
            {
                free(clientes_temporarios[j]);
            }
            free(clientes_temporarios);
            return -1; // Retorne um valor indicativo de erro
        }
        strcpy(clientes_temporarios[i], clientes[i].morada);
    }

    clock_t comeca = clock();
    // Ordenar o array de strings clientes_temporarios
    qsort(clientes_temporarios, *tamanho, sizeof(char *), comparar_clientes);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita)
    {
        int terco = (direita - esquerda) / 3;
        int meio1 = esquerda + terco;
        int meio2 = direita - terco;

        int cmp1 = strcmp(clientes_temporarios[meio1], morada);
        int cmp2 = strcmp(clientes_temporarios[meio2], morada);

        if (cmp1 == 0)
        {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Morada: %s\n", clientes_temporarios[meio1]);
            return meio1; // Encontrou o nome na posição meio1
        }
        else if (cmp2 == 0)
        {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Morada: %s\n", clientes_temporarios[meio2]);
            return meio2; // Encontrou o nome na posição meio2
        }
        else if (cmp1 < 0)
        {
            esquerda = meio1 + 1; // O nome está à direita de meio1
        }
        else if (cmp2 > 0)
        {
            direita = meio2 - 1; // O nome está à esquerda de meio2
        }
        else
        {
            esquerda = meio1 + 1;
            direita = meio2 - 1;
        }
    }

    // Liberar a memória alocada dinamicamente para cada string em clientes_temporarios
    for (int i = 0; i < *tamanho; i++)
    {
        free(clientes_temporarios[i]);
    }
    free(clientes_temporarios);

    return -1; // Nome não encontrado
}
int procura_cliente_morada_sequencial(cliente clientes[], int *tamanho, char morada[])
{
    clock_t comeca = clock();
    for (int i = 0; i < *tamanho; i++)
    {
        if (strcmp(clientes[i].morada, morada) == 0)
        {
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome_completo);
            printf("NIF: %ld\n", clientes[i].nif);
            printf("Telemovel: %ld\n", clientes[i].telemovel);
            printf("Morada: %s\n", clientes[i].morada);
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);

            return i;
        }
    }
    return -1;
}
int procura_cliente_morada(cliente clientes[], int *tamanho, char morada[])
{
    int procura;
    do
    {
        printf("Que procura deseja utilizar?\n1 - Sequencial\n2 - Binaria\n3 - Ternaria\n4 - Por interpolacao\nR: ");
        scanf(" %d", &procura);
    } while (procura > 5 && procura < 0);

    switch (procura)
    {
    case 1:
        int indice = procura_cliente_morada_sequencial(clientes, tamanho, morada);
        if (indice != 1)
        {
            return indice;
        }
        break;

    case 2:
        indice = procura_cliente_morada_binario(clientes, tamanho, morada);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 3:
        indice = procura_cliente_morada_ternario(clientes, tamanho, morada);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 4:
        indice = procura_cliente_morada_por_interpolacao(clientes, tamanho, morada);
        if (indice != 1)
        {
            return indice;
        }
        break;
    }
        
    return -1;
}

int procura_cliente_nif_por_interpolacao(cliente clientes[], int *tamanho, long int nif) {
    // Alocar memória para um array de ponteiros de long int
    long int **clientes_temporarios = malloc(*tamanho * sizeof(long int *));
    if (!clientes_temporarios) {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Copiar os endereços dos NIFs para o array de ponteiros
    for (int i = 0; i < *tamanho; i++) {
        clientes_temporarios[i] = &(clientes[i].nif);
    }

    clock_t comeca = clock();

    // Ordenar o array de ponteiros de long int (NIFs)
    qsort(clientes_temporarios, *tamanho, sizeof(long int *), comparar_clientes_nif_telemovel);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita) {
        // Calcular a posição probe usando interpolação
        int probe = esquerda + (((double)(direita - esquerda) / (*clientes_temporarios[direita] - *clientes_temporarios[esquerda])) * (nif - *clientes_temporarios[esquerda]));

        if (probe < 0 || probe >= *tamanho) {
            break;
        }

        if (*clientes_temporarios[probe] == nif) {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes[probe].nome_completo);
            printf("Morada: %s\n", clientes[probe].morada);
            free(clientes_temporarios); // Liberar a memória alocada
            return probe; // Encontrou o NIF na posição probe
        } else if (*clientes_temporarios[probe] < nif) {
            esquerda = probe + 1; // O NIF está à direita de probe
        } else {
            direita = probe - 1; // O NIF está à esquerda de probe
        }
    }

    free(clientes_temporarios); // Liberar a memória alocada
    return -1; // NIF não encontrado
}
int procura_cliente_nif_ternario(cliente clientes[], int *tamanho, long int nif) {
    long int **clientes_temporarios = malloc(*tamanho * sizeof(long int *));
    if (!clientes_temporarios) {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os endereços dos NIFs para clientes_temporarios
    for (int i = 0; i < *tamanho; i++) {
        clientes_temporarios[i] = &(clientes[i].nif);
    }

    clock_t comeca = clock();

    // Ordenar o array de ponteiros de NIFs (long int)
    qsort(clientes_temporarios, *tamanho, sizeof(long int *), comparar_clientes_nif_telemovel);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita) {
        int terco = (direita - esquerda) / 3;
        int meio1 = esquerda + terco;
        int meio2 = direita - terco;

        // Comparar os NIFs nos índices meio1 e meio2 com o NIF procurado
        if (*clientes_temporarios[meio1] == nif) {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("NIF: %ld\n", *clientes_temporarios[meio1]);
            return meio1; // Encontrou o NIF na posição meio1
        } else if (*clientes_temporarios[meio2] == nif) {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("NIF: %ld\n", *clientes_temporarios[meio2]);
            return meio2; // Encontrou o NIF na posição meio2
        } else if (*clientes_temporarios[meio1] > nif) {
            direita = meio1 - 1; // O NIF está à esquerda de meio1
        } else if (*clientes_temporarios[meio2] < nif) {
            esquerda = meio2 + 1; // O NIF está à direita de meio2
        } else {
            esquerda = meio1 + 1;
            direita = meio2 - 1;
        }
    }

    // Liberar a memória alocada dinamicamente para o array de ponteiros de NIFs
    free(clientes_temporarios);

    return -1; // NIF não encontrado
}
int procura_cliente_nif_sequencial(cliente clientes[], int *tamanho, long int nif)
{
    printf("\nProcura sequencial:\n");

    clock_t comeca = clock();
    for (int i = 0; i < *tamanho; i++)
    {
        if ( clientes[i].nif == nif)
        {
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome_completo);
            printf("NIF: %ld\n", clientes[i].nif);
            printf("Telemovel: %ld\n", clientes[i].telemovel);
            printf("Morada: %s\n", clientes[i].morada);
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);

            return i;
        }
    }
    return -1;
}
int procura_cliente_nif_binario(cliente clientes[], int *tamanho, long int nif)
{
    int i;
    int clientes_temporarios[*tamanho];
    for (i = 0; i < *tamanho; i++)
        clientes_temporarios[i] = clientes[i].nif;

    printf("\nPesquisa binaria:\n");

    clock_t comeca = clock();

    qsort(clientes_temporarios, *tamanho, sizeof(int), comparar_clientes_nif_telemovel);

    int esquerdo = 0;
    int direito = *tamanho - 1;
    int meio;
    int encontrado = 0;

    while (esquerdo <= direito)
    {
        meio = (esquerdo + direito) / 2;
        if (clientes_temporarios[meio] == nif)
        {
            encontrado = 1;
            break;
        }
        else if (clientes_temporarios[meio] < nif)
            esquerdo = meio + 1;
        else
            direito = meio - 1;
    }

    clock_t acaba = clock();
    double tempo = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
    printf("Tempo: %f segundos\n", tempo);

    if (!encontrado){
        printf("NIF nao encontrado.\n\n");
    }
    else {
        printf("Acao completa com sucesso\n\n");
        printf("Nif: %d", clientes_temporarios[meio]);
        return meio;
    }
    return -1;
} 
int procura_cliente_nif(cliente clientes[], int *tamanho, long int nif)
{
    int procura;
    do
    {
        printf("Que procura deseja utilizar?\n1 - Sequencial\n2 - Binaria\n3 - Ternaria\n4 - Por interpolacao\nR: ");
        scanf(" %d", &procura);
    } while (procura > 5 && procura < 0);

    switch (procura)
    {
    case 1:
        int indice = procura_cliente_nif_sequencial(clientes, tamanho, nif);
        if (indice != 1)
        {
            return indice;
        }
        break;

    case 2:
        indice = procura_cliente_nif_binario(clientes, tamanho, nif);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 3:
        indice = procura_cliente_nif_ternario(clientes, tamanho, nif);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 4:
        indice = procura_cliente_nif_por_interpolacao(clientes, tamanho, nif);
        if (indice != 1)
        {
            return indice;
        }
        break;
    }
        
    return -1;
}

int procura_cliente_telemovel_por_interpolacao(cliente clientes[], int *tamanho, long int telemovel) {
    // Alocar memória para um array de ponteiros de long int
    long int **clientes_temporarios = malloc(*tamanho * sizeof(long int *));
    if (!clientes_temporarios) {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Copiar os endereços dos NIFs para o array de ponteiros
    for (int i = 0; i < *tamanho; i++) {
        clientes_temporarios[i] = &(clientes[i].telemovel);
    }

    clock_t comeca = clock();

    // Ordenar o array de ponteiros de long int (NIFs)
    qsort(clientes_temporarios, *tamanho, sizeof(long int *), comparar_clientes_nif_telemovel);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita) {
        // Calcular a posição probe usando interpolação
        int probe = esquerda + (((double)(direita - esquerda) / (*clientes_temporarios[direita] - *clientes_temporarios[esquerda])) * (telemovel - *clientes_temporarios[esquerda]));

        if (probe < 0 || probe >= *tamanho) {
            break;
        }

        if (*clientes_temporarios[probe] == telemovel) {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes[probe].nome_completo);
            printf("Morada: %s\n", clientes[probe].morada);
            free(clientes_temporarios); // Liberar a memória alocada
            return probe; // Encontrou o NIF na posição probe
        } else if (*clientes_temporarios[probe] < telemovel) {
            esquerda = probe + 1; // O NIF está à direita de probe
        } else {
            direita = probe - 1; // O NIF está à esquerda de probe
        }
    }

    free(clientes_temporarios); // Liberar a memória alocada
    return -1; // NIF não encontrado
}
int procura_cliente_telemovel_ternario(cliente clientes[], int *tamanho, long int telemovel) {
    long int **clientes_temporarios = malloc(*tamanho * sizeof(long int *));
    if (!clientes_temporarios) {
        fprintf(stderr, "Erro ao alocar memória para clientes_temporarios.\n");
        return -1; // Retorne um valor indicativo de erro
    }

    // Alocar memória e copiar os endereços dos NIFs para clientes_temporarios
    for (int i = 0; i < *tamanho; i++) {
        clientes_temporarios[i] = &(clientes[i].telemovel);
    }

    clock_t comeca = clock();

    // Ordenar o array de ponteiros de NIFs (long int)
    qsort(clientes_temporarios, *tamanho, sizeof(long int *), comparar_clientes_nif_telemovel);

    int esquerda = 0;
    int direita = *tamanho - 1;

    while (esquerda <= direita) {
        int terco = (direita - esquerda) / 3;
        int meio1 = esquerda + terco;
        int meio2 = direita - terco;

        // Comparar os NIFs nos índices meio1 e meio2 com o NIF procurado
        if (*clientes_temporarios[meio1] == telemovel) {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("NIF: %ld\n", *clientes_temporarios[meio1]);
            return meio1; // Encontrou o NIF na posição meio1
        } else if (*clientes_temporarios[meio2] == telemovel) {
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);
            printf("Cliente encontrado:\n");
            printf("NIF: %ld\n", *clientes_temporarios[meio2]);
            return meio2; // Encontrou o NIF na posição meio2
        } else if (*clientes_temporarios[meio1] > telemovel) {
            direita = meio1 - 1; // O NIF está à esquerda de meio1
        } else if (*clientes_temporarios[meio2] < telemovel) {
            esquerda = meio2 + 1; // O NIF está à direita de meio2
        } else {
            esquerda = meio1 + 1;
            direita = meio2 - 1;
        }
    }

    // Liberar a memória alocada dinamicamente para o array de ponteiros de telemoveis
    free(clientes_temporarios);

    return -1; // NIF não encontrado
}
int procura_cliente_telemovel_sequencial(cliente clientes[], int *tamanho, long int telemovel)
{
    printf("\nProcura sequencial:\n");

    clock_t comeca = clock();
    for (int i = 0; i < *tamanho; i++)
    {
        if ( clientes[i].telemovel == telemovel)
        {
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome_completo);
            printf("NIF: %ld\n", clientes[i].nif);
            printf("Telemovel: %ld\n", clientes[i].telemovel);
            printf("Morada: %s\n", clientes[i].morada);
            clock_t acaba = clock();
            double search_time = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
            printf("Tempo: %f segundos\n", search_time);

            return i;
        }
    }
    return -1;
}
int procura_cliente_telemovel_binario(cliente clientes[], int *tamanho, long int telemovel)
{
    int i;
    int clientes_temporarios[*tamanho];
    for (i = 0; i < *tamanho; i++)
        clientes_temporarios[i] = clientes[i].telemovel;

    printf("\nPesquisa binaria:\n");

    clock_t comeca = clock();

    qsort(clientes_temporarios, *tamanho, sizeof(int), comparar_clientes_nif_telemovel);

    int esquerdo = 0;
    int direito = *tamanho - 1;
    int meio;
    int encontrado = 0;

    while (esquerdo <= direito)
    {
        meio = (esquerdo + direito) / 2;
        if (clientes_temporarios[meio] == telemovel)
        {
            encontrado = 1;
            break;
        }
        else if (clientes_temporarios[meio] < telemovel)
            esquerdo = meio + 1;
        else
            direito = meio - 1;
    }

    clock_t acaba = clock();
    double tempo = ((double)(acaba - comeca)) / CLOCKS_PER_SEC;
    printf("Tempo: %f segundos\n", tempo);

    if (!encontrado){
        printf("Telemovel nao encontrado.\n\n");
    }
    else {
        printf("Acao completa com sucesso\n\n");
        printf("Telemovel: %d", clientes_temporarios[meio]);
        return meio;
    }
    return -1;
}
int procura_cliente_telemovel(cliente clientes[], int *tamanho, long int telemovel)
{
    int procura;
    do
    {
        printf("Que procura deseja utilizar?\n1 - Sequencial\n2 - Binaria\n3 - Ternaria\n4 - Por interpolacao\nR: ");
        scanf(" %d", &procura);
    } while (procura > 5 && procura < 0);

    switch (procura)
    {
    case 1:
        int indice = procura_cliente_telemovel_sequencial(clientes, tamanho, telemovel);
        if (indice != 1)
        {
            return indice;
        }
        break;

    case 2:
        indice = procura_cliente_telemovel_binario(clientes, tamanho, telemovel);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 3:
        indice = procura_cliente_telemovel_ternario(clientes, tamanho, telemovel);
        if (indice != 1)
        {
            return indice;
        }
        break;
    case 4:
        indice = procura_cliente_telemovel_por_interpolacao(clientes, tamanho, telemovel);
        if (indice != 1)
        {
            return indice;
        }
        break;
    }
        
    return -1;
}

void strToLower(char str[]){
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void linha(int x){
    for (int i = 0; i <= x; i++)
    {
        printf("-");
    }
    printf("\n");
};

cliente *adicionar_clientes(cliente clientes[], int *tamanho, long int nif, long int telemovel, const char nome_completo[], const char morada[]){
    (tamanho++);

    clientes = realloc(clientes, (*tamanho) * sizeof(cliente));
    if (!clientes)
    {
        printf("Erro ao realocar memoria...");
        return NULL;
    }

    clientes[*tamanho - 1].nif = nif;
    clientes[*tamanho - 1].telemovel = telemovel;
    strncpy(clientes[*tamanho - 1].nome_completo, nome_completo, sizeof(clientes[*tamanho - 1].nome_completo) - 1);
    clientes[*tamanho - 1].nome_completo[sizeof(clientes[*tamanho - 1].nome_completo) - 1] = '\0';
    strncpy(clientes[*tamanho - 1].morada, morada, sizeof(clientes[*tamanho - 1].morada) - 1);
    clientes[*tamanho - 1].morada[sizeof(clientes[*tamanho - 1].morada) - 1] = '\0';

    printf("Cliente adicionado com sucesso.");
    return clientes;
}

void clientes_visualizar(cliente clientes[], int *tamanho){
    if (*tamanho == 0 || clientes == NULL)
    {
        printf("Sem clientes para mostrar\n");
        return;
    }

    int procura;
    do
    {
        printf("Indique que atributo deseja procurar:\n");
        printf("1 - nome_completo\n");
        printf("2 - nif\n");
        printf("3 - telemovel\n");
        printf("4 - morada\n");
        printf("R: ");

        if (scanf("%d", &procura) != 1 || procura < 1 || procura > 4)
        {
            printf("Opção invalida... tente novamente.\n");
            // Clear input buffer in case of invalid input
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (procura)
        {
        case 1:
        {
            char nome[TAMANHO_MAXIMO_NOME];
            printf("Indique um nome que procura: ");
            if (scanf("%49s", nome) != 1)
            {
                printf("Entrada invalida.\n");
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                break;
            }

            printf("Lista de nomes encontrados:\n");

            int indice = procura_cliente_nome_completo(clientes, tamanho, nome);
            if (indice == -1)
            {
                printf("Nenhum cliente encontrado com o nome '%s'\n", nome);
            }

            break;
        }
        case 2:
        {
            int indice;
            long int nif;
            printf("Indique um NIF que procura: ");
            if (scanf("%ld", &nif) != 1)
            {
                printf("Entrada invalida.\n");
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                break;
            }

            indice = procura_cliente_nif(clientes, tamanho, nif);
            if (indice == -1)
            {
                printf("Nenhum cliente encontrado com o nif '%ld'\n", nif);
            }

            break;
        }
        case 3:
        {
            long int telemovel;
            printf("Indique um numero de telemovel que procura: ");
            if (scanf("%ld", &telemovel) != 1)
            {
                printf("Entrada inválida.\n");
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                break;
            }

            int indice = procura_cliente_telemovel(clientes, tamanho, telemovel);
            if (indice == -1)
            {
                printf("Nenhum cliente encontrado com o telemovel '%ld'\n", telemovel);
            }

            break;
        }
        case 4:
        {
            char morada[TAMANHO_MAXIMO_MORADA];
            printf("Indique uma morada que procura: ");
            if (scanf(" %99[^\n]", morada) != 1)
            {
                printf("Entrada invalida.\n");
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                break;
            }

            
            int indice = procura_cliente_morada(clientes, tamanho, morada);

            if (indice == -1)
            {
                printf("Nenhum cliente encontrado com a morada '%s'\n", morada);
            }
            break;
        }
        default:
            printf("Opção invalida... tente novamente.\n");
            break;
        }

    } while (procura < 1 || procura > 5);
}

cliente *editar_clientes(cliente clientes[], int *tamanho, char nome_completo[]){

    int indice = procura_cliente_nome_completo(clientes, tamanho, nome_completo);
    if (indice == -1)
    {
        printf("Cliente nao encontrado...\n");
        return clientes;
    }
    int confirmacao = 0;
    do
    {
        printf("Indique o que deseja editar (nome completo, nif, telemovel, morada): ");
        scanf(" %[^\n]", nome_completo);

        strToLower(nome_completo);

        if (strcmp(nome_completo, "nome completo") == 0)
        {
            printf("Insira um novo nome completo: ");
            scanf(" %[^\n]", clientes[indice].nome_completo);
            confirmacao = 1;
        }
        else if (strcmp(nome_completo, "nif") == 0)
        {
            printf("Insira um novo NIF: ");
            scanf(" %ld", &clientes[indice].nif);
            confirmacao = 1;
        }
        else if (strcmp(nome_completo, "telemovel") == 0)
        {
            printf("Insira um novo numero de telemovel: ");
            scanf(" %ld", &clientes[indice].telemovel);
            confirmacao = 1;
        }
        else if (strcmp(nome_completo, "morada") == 0)
        {
            printf("Insira uma nova morada: ");
            scanf(" %[^\n]", clientes[indice].morada);
            confirmacao = 1;
        }
        else
        {
            printf("Opção invalida. Escolha entre nome completo, nif, telemovel ou morada.\n");
            continue;
        }
    } while (confirmacao == 0);

    return clientes;
}

cliente *anular_clientes(cliente clientes[], int *tamanho, char nome_completo[]){
    int indice = procura_cliente_nome_completo(clientes, tamanho, nome_completo);

    if (indice == -1)
    {

        printf("Nao foi encontrado cliente pretendido...\n");
        return clientes;
    }

    int resposta;
    printf("Deseja anular este cliente?\n1 - Sim\n2 - Nao\nR: ");
    if (scanf(" %d", &resposta) != 1)
    {
        printf("Entrada invalida. Operacao cancelada.\n");
        return clientes;
    }

    while (indice < *tamanho)
    {
        strcpy(clientes[indice].nome_completo, clientes[indice + 1].nome_completo);
        clientes[indice].nif = clientes[indice + 1].nif;
        clientes[indice].telemovel = clientes[indice + 1].telemovel;
        strcpy(clientes[indice].morada, clientes[indice + 1].morada);
        indice++;
    }

    (*tamanho)--;

    // Realocar a memória para o novo tamanho
    cliente *temp = realloc(clientes, (*tamanho) * sizeof(cliente));
    if (temp == NULL && *tamanho > 0)
    {
        printf("Erro ao realocar memória para clientes.\n");
        return NULL;
    }

    return temp;
}

void menu()
{
    printf("\n");
    printf("------------------MENU-------------------\n");
    printf("\n");
    printf("|\t 1- Visualizar clientes\t\t|\n");
    printf("|\t 2- Adicionar clientes \t\t|\n");
    printf("|\t 3- Editar clientes\t\t|\n");
    printf("|\t 4- Apagar clientes\t\t|\n");
    printf("|\t 5- Sair\t\t\t|\n");
    printf("\n");
    printf("------------ESCOLHA UMA OPCAO------------\n");
}