#include "geraldefinc.h"
#include "cliente_default.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
cli_dados dados;
msg_cli msg;

int linha=1,coluna=0;
void iniciarncurses(){
    initscr();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_GREEN,COLOR_BLUE);
    init_pair(3,COLOR_BLACK,COLOR_WHITE);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    curs_set(1);        //TORdNAR CURSOR INVISIVEL
    noecho();           // aparece dados de teclado
    keypad(stdscr,TRUE);//ativar teclado
}
void sair()
{
    endwin(); /*Sempre que finalizarmos um programa com a biblioteca curses,
                     devemos executar este comando.*/
    exit(0);  
}
void clean( WINDOW *limpar){
wbkgd(limpar,COLOR_PAIR(4));
refresh();
}



void iniciar( WINDOW *intiwin){
  int x,y;
  getmaxyx(intiwin,x,y);
wbkgd(intiwin,COLOR_PAIR(1));
 box(intiwin, '|', '-');
 char welcome[40]="*********BEM-VINDO*********";
 char welcome1[40]="MSGDIST";
 char welcome2[80]="Trabalho realizado por: Jesualdo Matos e Francisco Silva";
 char welcome3[40]="Prime qualquer tecla para continuar";
 int valor=strlen(welcome);
 int valor1=strlen(welcome1);
 int valor2=strlen(welcome2);
 int valor3=strlen(welcome3);
mvwprintw(intiwin,5,(y/2)-(valor/2),"%s",welcome);
mvwprintw(intiwin,6,(y/2)-(valor1/2),"%s",welcome1);
mvwprintw(intiwin,7,(y/2)-(valor2/2),"%s",welcome2);
mvwprintw(intiwin,8,(y/2)-(valor3/2),"%s",welcome3);

refresh();
}

void login( WINDOW *janelalogin,WINDOW *limpar){
  int n=-1;
  int fd_cliente,fd_servidor;
wbkgd(janelalogin,COLOR_PAIR(3));
int x,y;
getmaxyx(limpar,x,y);
mvprintw(x/2-1,y/2-(strlen("Indique o seu username")/2),"Indique o seu username:");
refresh();
echo();
wrefresh(janelalogin);
wscanw(janelalogin,"%s",dados.username);
dados.pid= getpid();
dados.estado=0;
sprintf(dados.nome_pipe_escrita,PIPE_CLI_ESCRITA,dados.pid);
sprintf(dados.nome_pipe_leitura,PIPE_CLI_LEITURA,dados.pid);
msg.ident=getpid();
strcpy(msg.user,dados.username);
fd_servidor=open(SERV_PIPE,O_RDWR);
write(fd_servidor,&dados,sizeof(cli_dados));
do{
int fd_cliente=open(dados.nome_pipe_leitura,O_RDONLY);

n= read(fd_cliente,&dados,sizeof(cli_dados));
if(n!=-1){
mvprintw(x/2+2,y/2-((strlen("O seu username:")+strlen(dados.username))/2),"O seu username:%s",dados.username);
}


}while(n==-1);
close(fd_cliente);
refresh();
}
//Variáveis globais
int main(int argc, char** argv) {
    
int valor;
int tecla;
  WINDOW *janelalogin,*intiwin,*limpar,*menu,*titulo,*topic,*mensagem,*listopic;
  iniciarncurses();
  limpar=newwin(0,0,0,0);
int x,y;
getmaxyx(limpar,x,y);

  janelalogin=newwin(1,50,x/2,(y/2)-(50/2));
  intiwin=newwin(0,0,0,0);
  mensagem=subwin(limpar,x-8,y/2,5,0);
  menu=subwin(limpar,x-1,y/2,1,y/2);
  topic=subwin(limpar,1,y/2,1,0);
  titulo=subwin(limpar,1,y/2,3,0);
  iniciar(intiwin);
  wrefresh(intiwin);
  getch();  
  delwin(intiwin);  
  refresh();
  clean(limpar);
  wrefresh(limpar);
  refresh();
  login(janelalogin,limpar);
  if(dados.estado==1){
  wrefresh(janelalogin);
  getch();
  wclear(janelalogin);
  delwin(janelalogin);
  refresh();
  mvwprintw(limpar,0,0,"INDIQUE O TOPICO:");
  mvwprintw(limpar,2,0,"INDIQUE O TITULO:");
  mvwprintw(limpar,4,0,"INDIQUE A MENSAGEM:");
  mvwprintw(limpar,0,y/2,"MENU:");
  mvwprintw(limpar,x-2,0,"Deseja gravar? Sim=1|Nao=0:");
  mvwprintw(menu,5,y/4-(strlen("Consultar lista de Topics-> OPCAO:1"))/2,"Consultar lista de Topics-> OPCAO:1");
  mvwprintw(menu,6,y/4-(strlen("Consultar lista de Titulos-> OPCAO:2"))/2,"Consultar lista de Titulos-> OPCAO:2");
  mvwprintw(menu,7,y/4-(strlen("Consultar lista de Mensagens-> OPCAO:3"))/2,"Consultar lista de Mensagens-> OPCAO:3");
  mvwprintw(menu,8,y/4-(strlen("Subscrever/Cancelar subscricao de um topic-> OPCAO:4"))/2,"Subscrever/Cancelar subscricao de um topic-> OPCAO:4");
    mvwprintw(menu,20,y/4-(strlen("Indique a sua opcao:"))/2,"Indique a sua opcao:");

  wrefresh(menu);
  wrefresh(limpar);
  wbkgd(titulo,COLOR_PAIR(2));
  wbkgd(topic,COLOR_PAIR(2));
  wbkgd(mensagem,COLOR_PAIR(2));
  wbkgd(menu,COLOR_PAIR(3));
  wrefresh(titulo);
  wrefresh(menu); 
  wrefresh(topic); 
  wrefresh(mensagem);
  refresh(); 
  getch();
  getmaxyx(limpar,x,y);
while(1){

mvwprintw(menu,25,y/4,"linha:%d, Coluna:%d",linha,coluna);
wrefresh(menu);
refresh();
tecla=getch();
switch(tecla){
case KEY_LEFT:
if(coluna>0 && linha!=x-2)
  coluna--;
    
  move(linha,coluna);
  refresh();
 break;
case KEY_RIGHT:
  if(coluna<y/2-1){
  coluna++;
  move(linha,coluna);
  }else{
    if(coluna==((y/2)+strlen("Indique a sua opcao:")/2+y/4)-1){
  coluna++;}
  move(21,(y/2)+strlen("Indique a sua opcao:")/2+y/4);
  }refresh();
 break;
case KEY_UP:
    if(linha>1)
    linha--;
    if(linha==2)
    linha=1;
    if(linha==4)
    linha=3;
    if(linha==x-3){
    linha=x-4;
    coluna=strlen("Deseja gravar? Sim=1|Nao=0:");
}
  move(linha,coluna);

  
  refresh();
break;
case KEY_DOWN:
if(linha<x-2)
  linha++;
  if(linha==2)
  linha=3;
  if(linha==0)
  linha=1;
  if(linha==4)
  linha=5;
  if(linha==x-3){
    linha=x-2;
    coluna=strlen("Deseja gravar? Sim=1|Nao=0:");
  }
  move(linha,coluna);
  refresh();
  break;
case ENTER:
if(linha==1)
wscanw(topic," %[^\n]",msg.topico);
if(linha==3)
wscanw(titulo," %[^\n]",msg.titulo);
if(linha>=5&& linha <x-2)
wscanw(mensagem," %[^\n]",msg.corpo);
if(linha==x-2)
mvwscanw(limpar,x-2,strlen("Deseja gravar? Sim=1|Nao=0:"),"%d",&valor);
mvwprintw(menu,26,y/4,"valor tem:%d",valor);
wrefresh(menu);

wrefresh(limpar);
if(valor==1){
  int fd_cliente=open(dados.nome_pipe_leitura,O_WRONLY);
write(fd_cliente,&msg,sizeof(msg_cli));
}
break;
}}
sair(); 
 }   
}

