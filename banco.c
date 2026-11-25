#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "banco.h"

/* Estrutura que guarda os dados de cada cliente */
struct Cliente {
    char nome[50];
    int conta;
    int tipo;
    float saldo;
    int titulo;
    int emprestimo;
};

/* Variaveis internas do banco */
static struct Cliente c[100];
static int qtd = 0;
static int numero = 1000;
static int aberto = 0;

void inicializar_banco(void) {
    srand((unsigned) time(NULL));
}

void abrir_banco(void) {
    aberto = 1;
}

int banco_esta_aberto(void) {
    return aberto;
}

void verificar_alertas(void) {
    for (int i = 0; i < qtd; i++) {
        if (c[i].tipo == 1 && c[i].saldo < 0) {
            printf("ALERTA: %s esta negativo!\n", c[i].nome);
        }
    }
}

void cadastrar(void) {
    int tipo;

    if (qtd >= 100) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %49[^\n]", c[qtd].nome);

    printf("Tipo da conta:\n");
    printf("1 - Corrente\n");
    printf("2 - Salario\n");
    printf("3 - Poupanca\n");
    scanf("%d", &tipo);

    c[qtd].tipo = tipo;
    c[qtd].conta = numero++;
    c[qtd].saldo = 0;
    c[qtd].titulo = 0;
    c[qtd].emprestimo = 0;

    qtd++;

    printf("Cliente cadastrado!\n");
}

void depositar(void) {
    int i;
    float valor;

    printf("Numero do cliente: ");
    scanf("%d", &i);

    if (i < 1 || i > qtd) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Valor: ");
    scanf("%f", &valor);

    if (valor > 0) {
        c[i-1].saldo += valor;
        printf("Deposito realizado!\n");
    }
}

void sacar(void) {
    int i;
    float valor;

    printf("Numero do cliente: ");
    scanf("%d", &i);

    if (i < 1 || i > qtd) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Valor: ");
    scanf("%f", &valor);

    if (valor > 0 && (c[i-1].tipo == 1 ||
        valor <= c[i-1].saldo)) {
        c[i-1].saldo -= valor;
        printf("Saque realizado!\n");
    } else {
        printf("Saldo insuficiente!\n");
    }
}

void emprestimo(void) {
    int i;
    float limite;

    printf("Numero do cliente: ");
    scanf("%d", &i);

    if (i < 1 || i > qtd) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    if (c[i-1].tipo == 1 && c[i-1].emprestimo == 0) {
        limite = c[i-1].saldo * 2.5;

        if (limite > 0) {
            c[i-1].saldo += limite;
            c[i-1].emprestimo = 1;
            printf("Emprestimo aprovado: %.2f\n", limite);
        } else {
            printf("Saldo insuficiente!\n");
        }
    } else {
        printf("Nao pode receber emprestimo!\n");
    }
}

void titulo(void) {
    int i;

    printf("Numero do cliente: ");
    scanf("%d", &i);

    if (i < 1 || i > qtd) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    if (c[i-1].tipo == 2 &&
        c[i-1].saldo >= 1000 &&
        c[i-1].saldo <= 1500) {

        c[i-1].titulo = 1;
        printf("Titulo comprado!\n");

    } else {
        printf("Cliente nao pode comprar titulo!\n");
    }
}

void historico(void) {
    float total = 0;

    printf("\nHISTORICO DO BANCO\n");

    for (int i = 0; i < qtd; i++) {
        total += c[i].saldo;

        if (c[i].saldo < 0) {
            printf("ALERTA: %s esta com saldo negativo!\n",
                   c[i].nome);
        }
    }

    printf("Clientes: %d\n", qtd);
    printf("Saldo total: %.2f\n", total);

    printf("\nCLIENTES CADASTRADOS\n");

    for (int i = 0; i < qtd; i++) {
        printf("%s | %d-%02d | %.2f\n",
               c[i].nome, c[i].conta,
               c[i].tipo, c[i].saldo);
    }
}

void sorteio(void) {
    int ordem[100];
    int aux;
    int vencedor;
    int n;
    int a = 0, b = 1, fib;

    if (qtd < 5) {
        printf("Precisa ter 5 clientes!\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        ordem[i] = i;
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (c[ordem[j]].saldo > c[ordem[i]].saldo) {
                aux = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = aux;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        if (c[ordem[i]].titulo == 0) {
            printf("Os cinco maiores saldos precisam ter titulo!\n");
            return;
        }
    }

    n = rand() % 10 + 1;

    for (int i = 1; i < n; i++) {
        fib = (a + b) % 5;
        a = b;
        b = fib;
    }

    vencedor = ordem[b % 5];

    printf("Vencedor: %s\n", c[vencedor].nome);
    printf("Premio: %.2f\n", c[vencedor].saldo * 10);

    c[vencedor].saldo = c[vencedor].saldo * 11;
}
