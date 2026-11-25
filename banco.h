#ifndef BANCO_H
#define BANCO_H

void inicializar_banco(void);
void abrir_banco(void);
int banco_esta_aberto(void);
void verificar_alertas(void);

void cadastrar(void);
void depositar(void);
void sacar(void);
void emprestimo(void);
void titulo(void);
void historico(void);
void sorteio(void);

#endif
