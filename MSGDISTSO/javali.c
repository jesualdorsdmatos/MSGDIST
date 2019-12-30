#include "geraldefinc.h"
#include "cliente_default.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
cli_dados cliente;
msg_cli   mensagem;

void main(){
int fd_servidor,fd_cliente;
int n=-1;
//verificar se o gestor está a correr
fd_servidor=open(SERV_PIPE,O_RDWR);
printf("introduz o username:");
scanf(" %s",cliente.username);
cliente.pid= getpid();
cliente.estado=0;
sprintf(cliente.nome_pipe_escrita,PIPE_CLI_ESCRITA,cliente.pid);
sprintf(cliente.nome_pipe_leitura,PIPE_CLI_LEITURA,cliente.pid);

write(fd_servidor,&cliente,sizeof(cli_dados));
do{
int fd_cliente=open(cliente.nome_pipe_leitura,O_RDONLY);
n= read(fd_cliente,&cliente,sizeof(cli_dados));

if(n!=-1){
printf("CONSEGUIR ler o username:%s, no pipe %s, estado:%d",cliente.username,cliente.nome_pipe_leitura,cliente.estado);
}//}
}while(n==-1);
close(fd_cliente);
if(cliente.estado==1){
int valor;
printf("Nome do topic:");
scanf(" %[^\n]",mensagem.topico);
printf("TITULO:");
scanf(" %[^\n]",mensagem.titulo);
printf("\nMensagem:");
scanf(" %[^\n]",mensagem.corpo);
  strcpy(mensagem.user,cliente.username);
  printf("deseja enviar gravar a mensagem sim -1, nao -2\n");
  scanf("%d",&valor);
if(valor==1){
int fd_cliente=open(cliente.nome_pipe_leitura,O_WRONLY);
write(fd_cliente,&mensagem,sizeof(msg_cli));
printf("foi enviado a sua mensagem\n");
}
sleep(20);
}
}


