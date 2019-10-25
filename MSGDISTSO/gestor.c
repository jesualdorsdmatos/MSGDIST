#include "gestor_default.h"
#include "geraldefinc.h"


void removerespaco(char str[]) {
    int j = 1;
    for (int i = 1; str[i]; i++) {
        if (str[i] != ' ' || (str[i - 1] != ' ')) {
           str[j] = str[i];
           j++;
        }
    }
    str[j] = '\0';
}



varamb lervarambiente(){
    varamb var;
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
    
    return var;
}

void encerrar(){
    printf("O programa vai encerrar!\n");
    exit(0);
}
int main(int argc, char *argv){
      char *str;
    int estado=0;
    char cmd[50];
    char pal[50];
    cmds b;
    b.argumento=NULL;
    
    varamb var=lervarambiente();
  
   

    
    while(1){
    printf("Intoduza um comando: ");
    scanf(" %[^\n]",cmd);
    removerespaco(cmd);

   
    for(int i =0; i<strlen(cmd);i++)
        cmd[i]= toupper(cmd[i]);

        b.comando=strtok(cmd," ");
        b.argumento=strtok(NULL, " ");


    if (strcmp(b.comando,"SHUTDOWN")==0){
       encerrar();
    }else if(strcmp(b.comando,"FILTER")==0 && b.argumento!=NULL){
        if(strcmp(b.argumento,"ON")==0){
         scanf("%s",pal);
        
         if(fork()==0){
             execl("verificador","verificador",pal,NULL);
             exit(1);
         }
         wait(NULL);
        }else if(strcmp(b.argumento,"OFF")==0){

        }else
            printf("[ERRO] Argumento:%s invalido.\nArgumento:ON/OFF\n",b.argumento);
    }else if(strcmp(b.comando,"USERS")==0){
    
    } else if(strcmp(b.comando,"TOPICS")==0){
    
    } else if(strcmp(b.comando,"MSG")==0){
    
    } else if(strcmp(b.comando,"DEL")==0 && b.argumento!=NULL){
    
    } else if(strcmp(b.comando,"KICK")==0 && b.argumento!=NULL){
        printf("DEBG!!\n");
    
    } else if(strcmp(b.comando,"PRUNE")==0){
    
    } else{
        printf("[ERRO] Comando %s invalido ou falta de argumentos!\n",cmd);
    }
    //pause();
  }


}
