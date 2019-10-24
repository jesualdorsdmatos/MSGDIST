/*

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <ncurses.h>

#define ENTER 10
#define ESCAPE 27
#define initx 14
#define inity 6


void iniciarcurses(){
    initscr();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_BLUE,COLOR_WHITE);
    init_pair(3,COLOR_RED,COLOR_WHITE);
    curs_set(0); //TORNAR CURSOR INVISIVEL
    noecho();// aparece dados de teclado
    keypad(stdscr,TRUE);//ativar teclado
}


void criar_menu( WINDOW *menubarra){
wbkgd(menubarra,COLOR_PAIR(2));
 waddstr(menubarra,"OPCOES");
 wmove(menubarra,0,20);
 waddstr(menubarra,"TOPICS");

}
/*
 * 
 */
int main(int argc, char** argv) {
  
    WINDOW *menubarra;
    iniciarcurses();
    menubarra=subwin(stdscr,1,80,0,0);
    criar_menu(menubarra);
     refresh();
 wrefresh(menubarra);
getch();

    delwin(menubarra);
 endwin();
return 0;

    
    /* 
  initscr();
  raw();
  WINDOW * win;
  int y=0,x=0;
  start_color();
  win = newwin(12, 100, y, x);

  init_pair(1,COLOR_RED,COLOR_BLUE);
  
  wbkgd(win,COLOR_PAIR(1));
  bkgd(COLOR_PAIR(1))
    //bkgd(COLOR_PAIR(4));
  /*attron(COLOR_PAIR(1));
  for(y=inity;y<20;y++){
      for(x=initx;x<50;x++){
  mvprintw(y,x," ");
  }
  }
  move(initx,inity);
  attroff(COLOR_PAIR(1));
mvprintw(0,0,"Topic:");
mvprintw(1,0,"Titulo:");
mvprintw(2,0,"mensagem:");
move(0,strlen("Topic:")+1);
wrefresh(win);
getch();
endwin();

*/
}

