
#include "geraldefinc.h"
#ifndef CLIENTE_DEFAULT_H
#define CLIENTE_DEFAULT_H
//Estrutura por armazenaros dados associados a uma mensagem enviada por um cliente
typedef struct msg_cli{
    char user[40];
    int pid;
    char topico[MAX_TOPIC];
    char titulo[MAX_TITULO];
    char corpo[MAX_CORPO];
    int duracao;
} msg_cli;



//Estrutura responsável por armazenar os dados do tabuleiro da mensagem.
typedef struct Config_Tab{
int n_linhas,n_colunas;

}Config_Tab;


#endif /* CLIENTE_DEFAULT_H */

