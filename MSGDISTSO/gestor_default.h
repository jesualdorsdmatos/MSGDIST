#include "geraldefinc.h"
#ifndef GESTOR_DEFAULT_h
#define GESTOR_DEFAULT_h
//Constantes
#define READ 0
#define WRITE 1
#define MAX 40
//Estrutura Responsável por armazenar o conteudo das variaveis de ambiente
typedef struct variaveisamb{    
    int MAXMSG;
    int MAXNOT;
    char WORDSNOT[MAX];
}varamb;

//Estrutura responsavel por armazenar todos os topicos atualmente existentes.
typedef struct subscritos{
char topicos[MAX_TOPIC];
}subs;

//Destina-se a guardar as subscrições por tópico associada a um utiliador
typedef struct util_subsc{
char topicos[MAX_TOPIC];
 char nome_pipe_escrita[MAX_USER];
    int ident;
}utsub;
// Estruturas para os comandos.
typedef struct cmdguardar{
    char *comando;
    char *argumento;
}cmds;

void imprimirin();// Função responsável por imprimir o texto introdutório inicial.
void imprimirfi();// Função responsável por imprimir o texto de fecho do programa.
void removerespaco(char str[]);// Retira espacos a mais entre os comandos(Utilizado para comandos com dois argumentos).
varamb lervarambiente(); //Função responsável por ler as variavéis de ambiente e armazená-las numa estrutura.
void encerrar(int pidfilho);//Função associada ao comando shutdown responsável por encerrar o verificador corretamente.
void help();//Função associada ao comando help onde elucida o utilizador sobre o funcionamento da consola.
void acrescentartopic (msg_cli c);
void * gestorcliente();
void subsfunc(atendercli cli);
#endif /* GESTOR_DEFAULT_h */
