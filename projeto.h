#ifndef PROJETO_H
#define PROJETO_H

#define TAMANHO_MAXIMO_MORADA 40
#define TAMANHO_MAXIMO_NOME 30

/*titulo de funcoes*/

typedef struct cliente_ {
    long int nif;
    long int telemovel;
    char nome_completo[TAMANHO_MAXIMO_NOME + 1]; 
    char morada[TAMANHO_MAXIMO_MORADA + 1];      
} cliente;

int comparar_clientes_nif_telemovel(const void *a, const void *b);
int comparar_clientes(const void *a, const void *b);

int procura_cliente_nome_completo_binario(cliente clientes[], int *tamanho, char nome_completo[]);
int procura_cliente_nome_completo_sequencial(cliente clientes[], int *tamanho, char nome_completo[]);
int procura_cliente_nome_completo_ternario(cliente clientes[], int *tamanho, char nome_completo[]);
int procura_cliente_nome_completo_por_interpolacao(cliente clientes[], int *tamanho, char nome_completo[]);
int procura_cliente_nome_completo(cliente clientes[], int *tamanho, char nome_completo[]);

int procura_cliente_morada(cliente clientes[], int *tamanho, char morada[]);


void linha(int x);
void strToLower(char str[]);
cliente *adicionar_clientes(cliente clientes[], int *tamanho, long int nif, long int telemovel, const char nome_completo[], const char morada[]);
void clientes_visualizar(cliente clientes[], int *tamanho);
cliente *editar_clientes(cliente clientes[], int *tamanho, char nome_completo[]);
cliente *anular_clientes(cliente clientes[], int *tamanho, char nome_completo[]);
void menu();

#endif
