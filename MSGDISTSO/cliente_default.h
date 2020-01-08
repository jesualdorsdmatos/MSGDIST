
#include "geraldefinc.h"
#ifndef CLIENTE_DEFAULT_H
#define CLIENTE_DEFAULT_H

//Estrutura responsável por armazenar os dados do tabuleiro da mensagem.
typedef struct Config_Tab{
int n_linhas,n_colunas;

}Config_Tab;


void lertopics();
void lertitulos();
void lermensagem();
void subscrever();
void sair();
#endif /* CLIENTE_DEFAULT_H */

