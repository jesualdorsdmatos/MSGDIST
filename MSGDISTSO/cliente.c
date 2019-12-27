#include "geraldefinc.h"
#include "cliente_default.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

void iniciarncurses(){
    initscr();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_GREEN,COLOR_BLUE);
    init_pair(3,COLOR_BLACK,COLOR_WHITE);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    curs_set(0);        //TORdNAR CURSOR INVISIVEL
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

char login( WINDOW *janelalogin,WINDOW *limpar){
wbkgd(janelalogin,COLOR_PAIR(3));
int x,y;
  getmaxyx(limpar,x,y);
 mvprintw(x/2-1,y/2-(strlen("Indique o seu username")/2),"Indique o seu username:");
 refresh();
char username[80];
echo();
wrefresh(janelalogin);
wscanw(janelalogin,"%s",username);
mvprintw(x/2+2,y/2-((strlen("O seu username:")+strlen(username))/2),"O seu username:%s",username);
refresh();
return username;
}
//Variáveis globais
char username[MAX_USER];
int main(int argc, char** argv) {


  WINDOW *janelalogin,*intiwin,*limpar,*quadro1,*quadro2,*titulo,*topic,*mensagem,*listopic;
  iniciarncurses();
  limpar=newwin(0,0,0,0);
  int x,y;
getmaxyx(limpar,x,y);
  janelalogin=newwin(1,50,x/2,(y/2)-(50/2));
  intiwin=newwin(0,0,0,0);
  quadro1=subwin(limpar,x-5,y/2,5,0);
  quadro2=subwin(limpar,x-1,y/2,1,y/2);
  topic=subwin(limpar,1,y/2,1,0);
  mensagem=subwin(limpar,1,y/2,3,0);
  iniciar(intiwin);
  wrefresh(intiwin);
  getch();  
  delwin(intiwin);  
  refresh();
  clean(limpar);
  wrefresh(limpar);
  refresh();
  login(janelalogin,limpar);
  wrefresh(janelalogin);
  getch();
  wclear(janelalogin);

  delwin(janelalogin);
  refresh();
  mvwprintw(limpar,0,0,"INDIQUE O TOPICO:");
  mvwprintw(limpar,2,0,"INDIQUE O TITULO:");
  mvwprintw(limpar,4,0,"INDIQUE A MENSAGEM:");
  mvwprintw(limpar,0,y/2,"TOPICOS EXISTENTES:");

  wrefresh(limpar);
  wbkgd(quadro1,COLOR_PAIR(2));
  wbkgd(topic,COLOR_PAIR(2));
  wbkgd(mensagem,COLOR_PAIR(2));
  wbkgd(quadro2,COLOR_PAIR(3));
  wrefresh(quadro1);
  wrefresh(quadro2); 
  wrefresh(topic); 
  wrefresh(mensagem); 
  getch();

sair(); 
    
}

