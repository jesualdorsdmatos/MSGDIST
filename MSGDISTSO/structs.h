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



#endif /* STRUCTS_H */

