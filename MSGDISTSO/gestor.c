/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    // Processamento das variáveis de amabientes
    //Máximo de mensagens
     char* str;
     str=getenv("MAXMSG");
     if(str!=NULL)
         printf("A 1 variavel tem o valor %s .\n",str);
     else    
       printf("A variavel MAXMSG nao existe.\n");
        
     //Máximo número de palavras rejeitadas
     str= getenv("MAXNOT");
     if(str != NULL)
         printf("A variavel 2 tem o valor. %s \n",str);
     else    
       printf("A variavel MAXNOT nao existe.\n");
       
     //Nome da ficheiro com as palavras proíbidas
     str= getenv("WORDSNOT");
     if(str != NULL)
         printf("A variavel 3 tem o valor. %s \n",str);
     else    
       printf("A variavel WORDSNOT nao existe.\n");
     
    char cmd[50];
    
    while(1){
    printf("Intoduza um comando: ");
    scanf("%s",cmd);
            
    
    
    
    for(int i =0; i<strlen(cmd);i++)
        cmd[i]= toupper(cmd[i]);
    
    
 if (strcmp(cmd,"SHUTDOWN")==0){
        printf("O Programa vai encerrar.\n");
        exit(0);
    }else if(strcmp(cmd,"FILTER")==0){
        char *pal;
        scanf("%s",pal);
        if(fork()==0){
            execlp("./verificador","./verificador",pal,NULL);
            exit(0);
        }
        
        
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
