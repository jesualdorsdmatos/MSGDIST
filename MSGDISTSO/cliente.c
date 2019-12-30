#include "geraldefinc.h"
#include "cliente_default.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
cli_dados cliente;
/*
void * recebedadoslogin() {

while(1){
 
 }
 }


}

}

*/
void main(){
int fd_servidor,fd_cliente;
int n=-1;
fd_servidor=open(SERV_PIPE,O_RDWR);
printf("introduz o username:");
scanf(" %s",cliente.username);
cliente.pid= getpid();
cliente.estado=0;
sprintf(cliente.nome_pipe,PIPE_CLI,cliente.pid);
write(fd_servidor,&cliente,sizeof(cli_dados));
do{
int fd_cliente=open(cliente.nome_pipe,O_RDONLY);
n= read(fd_cliente,&cliente,sizeof(cli_dados));

if(n!=-1){
printf("CONSEGUIR ler o username:%s, no pipe %s, estado:%d",cliente.username,cliente.nome_pipe,cliente.estado);
}//}
}while(n==-1);
if(cliente.estado==1){

/*
scanf("")
scanf(" %[^\n]",dados.titulo);
printf("\nTopic:");
scanf(" %[^\n]",dados.topico);
printf("\nMensagem:");
scanf(" %[^\n]",dados.corpo);
dados.ident=getpid();

*/


}
}


