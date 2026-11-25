#include <stdio.h>
#include "banco.h"

int main(void) {
    int op;

    inicializar_banco();

    do {
        verificar_alertas();

        printf("\nBANCO DIGITAL\n");
        printf("1 - Abrir banco\n");
        printf("2 - Historico\n");
        printf("3 - Sorteio\n");
        printf("4 - Sair\n");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                int opcao;
                abrir_banco();

                do {
                    printf("\n1 - Cadastrar\n");
                    printf("2 - Depositar\n");
                    printf("3 - Sacar\n");
                    printf("4 - Emprestimo\n");
                    printf("5 - Comprar titulo\n");
                    printf("6 - Voltar\n");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            cadastrar();
                            break;
                        case 2:
                            depositar();
                            break;
                        case 3:
                            sacar();
                            break;
                        case 4:
                            emprestimo();
                            break;
                        case 5:
                            titulo();
                            break;
                    }

                } while (opcao != 6);
                break;
            }

            case 2:
                if (banco_esta_aberto())
                    historico();
                else
                    printf("Abra o banco primeiro!\n");
                break;

            case 3:
                if (banco_esta_aberto())
                    sorteio();
                else
                    printf("Abra o banco primeiro!\n");
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 4);

    return 0;
}
