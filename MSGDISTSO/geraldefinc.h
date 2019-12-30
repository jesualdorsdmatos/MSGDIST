
#ifndef GERALDEFINC_H
#define GERALDEFINC_H

//***********INCLUDES***********//

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>




//***********DEFINES***********//
#define MAX_TOPIC 30
#define MAX_TITULO 30
#define MAX_USER 30
#define MAX_CORPO 1000
#define ENTER 10
#define ESCAPE 27
#define INITX 14
#define INITY 6
#define MAXMSGD 10
#define MAXNOTD 10
#define WORSNOTD  "pal_bad.txt"
#define SERV_PIPE "pipe_servidor"
#define PIPE_CLI_LEITURA "cli_leitura_%d"
#define PIPE_CLI_ESCRITA "cli_escrita_%d"
// Estrutura responsável por armazenar os dados de um cliente.
typedef struct cli_dados{
char username[MAX_USER];
char nome_pipe_leitura[MAX_USER];
char nome_pipe_escrita[MAX_USER];
int pid;
int estado;// 0- se não tiver sido aprovada e 1 em caso de aprovação
}cli_dados;

//Estrutura por armazenaros dados associados a uma mensagem enviada por um cliente
typedef struct msg_cli{
    char user[MAX_USER];
    char topico[MAX_TOPIC];
    char titulo[MAX_TITULO];
    char corpo[MAX_CORPO];
    int ident;
    int duracao;
} msg_cli;

#endif /* GERALDEFINC_H */