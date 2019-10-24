
#include "geraldefinc.h"
#ifndef CLIENTE_DEFAULT_H
#define CLIENTE_DEFAULT_H
typedef struct msg_cli{
    char topico[MAX_TOPIC];
    char titulo[MAX_TITULO];
    char corpo[MAX_CORPO];
    int duracao;
} msg_cli;

#endif /* CLIENTE_DEFAULT_H */

