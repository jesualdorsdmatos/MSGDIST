#include "geraldefinc.h"
#include "cliente_default.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>


void main(){
int fd_servidor,fd_cliente;
cli_dados dados_login,new;
// criar pipe login
//verificar se o servidor está a correr //acess para o pipe dele

//se não estiver mensagem de erro
 fd_servidor=open(SERV_PIPE,O_RDWR);
printf("introduz o username:");
scanf(" %s",dados_login.username);
dados_login.pid= getpid();
dados_login.estado=0;
sprintf(dados_login.nome_pipe,PIPE_CLI,dados_login.pid);

write(fd_servidor,&dados_login,sizeof(cli_dados));

fd_cliente=open(dados_login.nome_pipe,O_RDONLY);
if(fd_cliente==-1){
  printf("ERRO NO PIPE!");
}
read(fd_cliente,&new,sizeof(cli_dados));
printf("%d",dados_login.estado);
if(new.estado!=1){
  printf("ERRO nao pode logar!\n");
  exit(1);
}
//->Confirmação se este se poder logar ou não e qual o seu username//read
printf("\nTitulo:");

/*
scanf(" %[^\n]",dados.titulo);
printf("\nTopic:");
scanf(" %[^\n]",dados.topico);
printf("\nMensagem:");
scanf(" %[^\n]",dados.corpo);
dados.ident=getpid();



printf("%s\n%s\n%s\n%s\n%d",dados.user,dados.titulo,dados.topico,dados.corpo,dados.ident);
*/
}
