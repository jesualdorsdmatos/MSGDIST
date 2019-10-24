/*
 
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



#include "structs.h"




void encerrar(){
    printf("O programa vai encerrar!\n");
    exit(0);
}
int main(int argc, char *argv[]){
    varamb var;
    char *str;
    int estado=0;
    // Processamento das variáveis de amabientes
    //Máximo de mensagens
    if((getenv("MAXMSG"))==NULL)
         printf("A variavel MAXMSG nao existe.\n");
     else   
         var.MAXMSG=atoi((getenv("MAXMSG")));
         
     //Máximo número de palavras rejeitadas
    if((getenv("MAXNOT"))==NULL)
         printf("A variavel MAXNOT nao existe.\n");
     else   
         var.MAXNOT=atoi((getenv("MAXNOT")));
       
     //Nome da ficheiro com as palavras proíbidas
     if((getenv("WORDSNOT"))==NULL)
         printf("A variavel WORDSNOT nao existe.\n");
     else   
         var.WORDSNOT=atoi((getenv("WORDSNOT")));
     
    char cmd[50];
    char pal[50];
    
    while(1){
    printf("Intoduza um comando: ");
    scanf("%s",cmd);
            
    for(int i =0; i<strlen(cmd);i++)
        cmd[i]= toupper(cmd[i]);
    

    if (strcmp(cmd,"SHUTDOWN")==0){
       encerrar();
    }else if(strcmp(cmd,"FILTER")==0){
         scanf("%s",pal);
        
         if(fork()==0){
             execl("verificador","verificador",pal,NULL);
             exit(1);
         }
         wait(NULL);
    
    }else if(strcmp(cmd,"USERS")==0){
    
    } else if(strcmp(cmd,"TOPICS")==0){
    
    } else if(strcmp(cmd,"MSG")==0){
    
    } else if(strcmp(cmd,"DEL")==0){
    
    } else if(strcmp(cmd,"KICK")==0){
    
    } else if(strcmp(cmd,"PRUNE")==0){
    
    } else{
        printf("o comando %s nao e valido\n",cmd);
    }
    //pause();
  }

}
