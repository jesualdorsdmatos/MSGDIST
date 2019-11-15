
#ifndef GERALDEFINC_H
#define GERALDEFINC_H

//***********INCLUDES***********//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>




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
// Estrutura responsável por armazenar os dados de um cliente.
typedef struct cli_dados{
char username[MAX_USER];
char nome_pipe[MAX_USER];
int pid;
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