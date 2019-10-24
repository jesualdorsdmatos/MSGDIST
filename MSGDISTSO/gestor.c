<<<<<<< HEAD
/*
 
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
=======
#include "geraldefinc.h"
#include "gestor_default.h"


>>>>>>> 96ee919071a864840eeeb9dc27942eabbfb9bb4e



void encerrar(){
    printf("O programa vai encerrar!\n");
    exit(0);
}
int main(int argc, char *argv[]){
    varamb var;
    char *str;
    int estado=0, p[2];
    // Processamento das variáveis de amabientes
    //Máximo de mensagens
    if((getenv("MAXMSG"))==NULL){
         printf("MAXMSG default.\n");
    var.MAXMSG=MAXMSGD;
    }
     else   
         var.MAXMSG=atoi((getenv("MAXMSG")));
         
     //Máximo número de palavras rejeitadas
    if((getenv("MAXNOT"))==NULL){
         printf("MAXNOT default.\n");
    var.MAXNOT=MAXNOTD;}
     else   
         var.MAXNOT=atoi((getenv("MAXNOT")));
       
     //Nome da ficheiro com as palavras proíbidas

     if((getenv("WORDSNOT"))==NULL){
         printf("WORDSNOT default.\n");
        strcpy(var.WORDSNOT,WORSNOTD);
     }
     else   
         strcpy(var.WORDSNOT,"WORDSNOT");
     
    char cmd[50];
    char pal[50];
    int i=0;
    while(1){
    printf("Intoduza um comando: ");
  scanf("%[^\n]" ,cmd); 
   printf("%s\n",cmd);         
    for(int i =0; i<strlen(cmd);i++)
        cmd[i]= toupper(cmd[i]);


    if (strcmp(cmd,"SHUTDOWN")==0){
       encerrar();
    }else if(strcmp(cmd,"FILTER")==0){
              printf("%s",pal);
         pipe(p);
        if(fork()==0){
                scanf("%[^\n]" ,pal); 

         close(0);//Fecha o teclado
         dup(p[0]);
         close(p[0]);
         close(p[1]);
puts(pal);
         execl("verificador","verificador","pal_bad.txt",NULL);
         exit(1);
      }
        close (1);
	dup(p[1]);
	close(p[0]);
	close (p[1]);
	printf("%s\n",pal);
    close(1);
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
