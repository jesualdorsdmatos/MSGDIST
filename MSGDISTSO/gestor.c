#include "gestor_default.h"
#include "geraldefinc.h"

// Retira espa�os a mais entre os comandos
void removerespaco(char str[]) {
    int j = 0;
    for (int i = 0; str[i]; i++) {
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
         
     //M�ximo n�mero de palavras rejeitadas
    if((getenv("MAXNOT"))==NULL){
         printf("MAXNOT default.\n");
    var.MAXNOT=MAXNOTD;}
     else   
         var.MAXNOT=atoi((getenv("MAXNOT")));
       
     //Nome da ficheiro com as palavras pro�bidas
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
    char cmd[50],pal[50];
    cmds b;
    b.argumento=NULL;
    int p[2],res;
    varamb var=lervarambiente();


    
    while(1){
    printf("Intoduza um comando: ");
    scanf(" %[^\n]",cmd);
    fflush(stdin);
    removerespaco(cmd);

    for(int i =0; i<strlen(cmd);i++)
        cmd[i]= toupper(cmd[i]);

        b.comando=strtok(cmd," ");
        b.argumento=strtok(NULL, " ");


    if (strcmp(b.comando,"SHUTDOWN")==0){
       encerrar();
    }else if(strcmp(b.comando,"FILTER")==0 && b.argumento!=NULL){
        if(strcmp(b.argumento,"ON")==0){
            //scanf("%s",pal);
            pipe(p);//O pipe tem de ser criado antes do fork
                 //para quando este for feito herdar a tabela de fd's
            getchar();
                fgets(pal,50,stdin);
         if(fork()==0){
            /* p[0]-lado de escrita do pipe;//0-stdin;
             1-stdout;
             2-stderr;
             //p[0]-lado de escrita do pipe;
             //p[1]- lado de leitura do pipe;
*/
              close(0);    //fechamos o teclado
              dup(p[0]);  // trocas o teclado pela extremidade p[0] do pipe.
              close(p[0]);//fechamos a extremidade do pipe para que n�o seja ecrito mais nada.
              close(p[1]);// fechamos a extremidade de leitura do pipe.
             execl("verificador","verificador",var.WORDSNOT,NULL);
             exit(1);
         }
         close(1);//fechamos ecr�
         dup(p[1]);
         close(p[1]);
         close (p[0]);
         //FILE* fd=fdopen(p[1],"w");
         //char *c;
         //fgets(c,1,fd);
         printf("%s",pal);
         close(1);
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