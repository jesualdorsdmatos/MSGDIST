#include "geraldefinc.h"
#include "gestor_default.h"





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
    
    while(1){
<<<<<<< HEAD
    printf("Intoduza um comando: ");
    scanf("%s",cmd);
            
=======
    printf("Intoduza um comando:");
    scanf(" %[^\n]",cmd);
    removerespaco(cmd);

   
>>>>>>> ramo_jesualdo
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
<<<<<<< HEAD
=======
        }else if(strcmp(b.argumento,"OFF")==0){

        }elsegit add *
        git commit -m "comentário"
        git push
        git checkout master
        git pull
        git marge ramo_name
        git commit -m "comentario"
        git push
        volto ao meu ramo
        git marge master
        git push
            printf("[ERRO] Argumento:%s invalido.\nArgumento:ON/OFF\n",b.argumento);
    }else if(strcmp(b.comando,"USERS")==0){
>>>>>>> ramo_jesualdo
    
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
