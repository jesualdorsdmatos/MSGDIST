/* 
 * File:   structs.h
 * Author: franciscosilva
 */
#include "defines.h"
#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct msg_cli{
    char topico[MAX_TOPIC];
    char titulo[MAX_TITULO];
    char corpo[MAX_CORPO];
    int duracaO;
} msg_cli;


typedef struct variaveisamb{
    
    int MAXMSG;
    int MAXNOT;
    int WORDSNOT;
    
}varamb;

#endif /* STRUCTS_H */

