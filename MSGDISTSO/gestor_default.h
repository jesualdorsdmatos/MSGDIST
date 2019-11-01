#include "geraldefinc.h"
#ifndef GESTOR_DEFAULT_h
#define GESTOR_DEFAULT_h
#define READ 0
#define WRITE 1

typedef struct variaveisamb{
    
    int MAXMSG;
    int MAXNOT;
    char WORDSNOT[30];
    
}varamb;

typedef struct cmdguardar{

    char *comando;
    char *argumento;

}cmds;

#endif /* GESTOR_DEFAULT_h */
