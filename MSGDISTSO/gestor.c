#include "gestor_default.h"
#include "geraldefinc.h"
    pthread_t lermensagem;
    pthread_t enviartop;

    msg_cli *mensagem=NULL;
    cli_dados * clientes=NULL;
    subs *listatopics=NULL;

    int nMensagem=0;
    int nUsers=0;
    int nTopics=0;
    void imprimirin()
{
    printf("************************************************\n");
    printf("**       BEM-VINDO AO GESTOR DO MSGDIST       **\n");
    printf("**Comando:[help] para listar todos os comandos**\n");
    printf("************************************************\n");
}

void imprimirfi()
{
    printf("*************************************************\n");
    printf("**           Trabalho realizado por:           **\n");
    printf("**       Jesualdo Matos/Francisco Silva        **\n");
    printf("*************************************************\n");
}
void acrescentaMensagagem(msg_cli m){
    msg_cli *temp;
  if (mensagem == NULL) {
  temp = (msg_cli*) malloc(sizeof(msg_cli) * 1);
      if(temp==NULL){
                 printf("Erro a  alocar  memoria para o vetor das mensagens");
             }else{
                 temp->total=nMensagem;
                 temp->duracao=10;
            mensagem = temp;     
            mensagem[nMensagem] = m;
            acrescentartopic(mensagem[nMensagem]);

           nMensagem++;
          }
        } else {
             temp = realloc(mensagem, ( nMensagem+ 1) * sizeof(msg_cli));
             if(temp==NULL){
                 printf("Erro a  realocar memoria para o vetor das mensagens");
             }else{
                 temp->total=nMensagem;
                 temp->duracao=10;
             mensagem=temp;
              mensagem[nMensagem] = m;
            acrescentartopic(mensagem[nMensagem]);
             nMensagem++;
             

         
         }
        }
         
}

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}


void verificaDadosCliente(cli_dados *c){
    int i=0;
    int j=0;
    char numero[2]="";
    char nome[MAX_USER]="";
    for ( i=0; i< strlen(c->username);i++){
    if(isdigit(c->username[i])==0){
        nome[i]=c->username[i];
    }else {
    numero[j]= c->username[i];
    j++;
    }
    }
    char *num=strtok(numero," ");
    char *nom=strtok(nome," ");


}





void acrescentartopic (msg_cli informacao){
    subs *temp;
  if (listatopics == NULL) {
  temp = (subs*) malloc(sizeof(subs) * 1);
      if(temp==NULL){
                 printf("Erro a  alocar  memoria para o vetor das mensagens");
             }else{
            listatopics = temp;     
            strcpy(listatopics[nTopics].topicos,informacao.topico);
           nTopics++;

          
          }
        } else {        
             temp = realloc(listatopics, ( nTopics + 1) * sizeof(subs));
             if(temp==NULL){
                 printf("Erro a  realocar memoria para o vetor das mensagens");
             }else{
             listatopics=temp;
              strcpy(listatopics[nTopics].topicos,informacao.topico);
             nTopics++;

         }
        }

}

void acrescentaCliente (cli_dados c){
    cli_dados *temp;
  if (clientes == NULL) {
  temp = (cli_dados*) malloc(sizeof(cli_dados) * 1);
      if(temp==NULL){
                 printf("Erro a  alocar  memoria para o vetor das mensagens");
             }else{
            clientes = temp;     
            clientes[nUsers] = c;
           nUsers++;
          }
        } else {        
             temp = realloc(clientes, ( nUsers + 1) * sizeof(cli_dados));
             if(temp==NULL){
                 printf("Erro a  realocar memoria para o vetor das mensagens");
             }else{
             clientes=temp;
             verificaDadosCliente(&c);
              clientes[nUsers] = c;
             nUsers++;
         }
        }

}

void removerespaco(char str[])
{
    int j = 0, i =0;
    for ( i = 0; str[i]; i++)
    {
        if (str[i] != ' ' || (str[i - 1] != ' '))
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

varamb lervarambiente()
{
    varamb var;
    //Maximo de mensagems
    if ((getenv("MAXMSG")) == NULL)
    {
        printf("MAXMSG default.\n");
        var.MAXMSG = MAXMSGD;
    }
    else
        var.MAXMSG = atoi((getenv("MAXMSG")));

    //Maximo numero de palavras rejeitadas
    if ((getenv("MAXNOT")) == NULL)
    {
        printf("MAXNOT default.\n");
        var.MAXNOT = MAXNOTD;
    }
    else
        var.MAXNOT = atoi((getenv("MAXNOT")));

    //Nome da ficheiro com as palavras pro�bidas
    if ((getenv("WORDSNOT")) == NULL)
    {
        printf("WORDSNOT default.\n");
        strcpy(var.WORDSNOT, WORSNOTD);
    }
    else
        strcpy(var.WORDSNOT,getenv("WORDSNOT"));
    return var;
}

void encerrar(int pidfilho)
{
    kill(pidfilho,SIGUSR2);
    printf("Gestor encerrado com sucesso.\n");
    imprimirfi();
    unlink(SERV_PIPE);
    exit(0);
}

void help()
{
    printf("Comando:Shutdown -> Encerrar gestor.\n");
    printf("Comando:Mensagem -> Permitir introduzir mensagem para o verificador.\n");
    printf("Comando:Filter -> Argumento ON ou OFF, Ativar/Desligar filtro de mensagem para o verificador.\n");
    printf("Comando:Users -> Listar utilizadores.\n");
    printf("Comando:Topics -> Listar topicos.\n");
    printf("Comando:Msg -> Listar mensagens.\n");
    printf("Comando:Topic -> Argumento [topico-em-questao], lista mensagens do topico.\n");
    printf("Comando:Del -> Argumento [mensagem-em-questao], Apagar mensagem.\n");
    printf("Comando:Kick -> Argumento [username-em-questao], Excluir um utilizador.\n");
    printf("Comando:Kick -> Argumento [username-em-questao], Excluir um utilizador.\n");
    printf("Comando:Prune -> Eliminar Topicos sem conteudo.\n");
}

void * recebermensagens(void * nomepipe){
    do{
      int fd_cliente=open(nomepipe,O_RDONLY);
      msg_cli m;
       int n=read(fd_cliente,&m,sizeof(msg_cli));
        if(n!=-1){
               acrescentaMensagagem(m);
         }

   }while(1);
}
void * recebelogins(){
   do{
     cli_dados c;
      int fd_serv=open(SERV_PIPE,O_RDONLY);
   read(fd_serv,&c,sizeof(cli_dados));
   acrescentaCliente(c);
   if(c.estado!=1){
    if(mkfifo(c.nome_pipe_leitura,0600)==-1){
        printf("ERRO NA CRIACAO DO PIPE CLIENTE %s",c.nome_pipe_leitura);
    }
     if(mkfifo(c.nome_pipe_escrita,0600)==-1){
        printf("ERRO NA CRIACAO DO PIPE CLIENTE %s",c.nome_pipe_leitura);
    }
    
    int fd_cliente=open(c.nome_pipe_leitura,O_WRONLY);
    c.estado=1;
    close(fd_serv);
    write(fd_cliente,&c,sizeof(cli_dados));
    close(fd_cliente);  
     int res_uti = pthread_create( &lermensagem, NULL, recebermensagens,(void*)&c.nome_pipe_leitura);  
    int res_topicsenviar = pthread_create( &enviartop, NULL, enviartopics, NULL);
    
   }
    }while(1);


}



void * enviartopics(){
    int fd_topics,m=0;
    do{

   int i=0,j=0;
    int r=0;
    atendercli atender;
   
fflush(stdout);
    int fd_flags=open(PIPE_CHAMADA,O_RDONLY);
    read(fd_flags,&atender,sizeof(atendercli));
    close(fd_flags);
    
    if(atender.flag==1){
            fd_topics=open(atender.nome_pipe_escrita,O_WRONLY);

            for(j=0;j<nTopics;j++){
       
    write(fd_topics,&listatopics[j],sizeof(subs));
   
    }
            close(fd_topics);


    }
       

        if(atender.flag==2){
            fd_topics=open(atender.nome_pipe_escrita,O_WRONLY);

            for(j=0;j<nMensagem;j++){
       
    write(fd_topics,&mensagem[j],sizeof(msg_cli));

        }
        close(fd_topics);
        }

        if(atender.flag==3){
            
            fd_topics=open(atender.nome_pipe_escrita,O_WRONLY);
            for(j=0;j<nMensagem;j++){

        for ( m = 0; m < strlen(mensagem[j].titulo); m++)
        mensagem[j].titulo[m] = toupper(mensagem[j].titulo[m]);
                if(strcmp(mensagem[j].titulo,atender.titulo)==0){
                 write(fd_topics,&mensagem[j],sizeof(msg_cli));
  
                }
            }
            close(fd_topics);
        }
         
        atender.flag=0;
}while(1);

}

int main(int argc, char *argv)
{
    char cmd[50], pal[200];
    cmds b;
    char buffer[3];
    b.argumento = NULL;
    int pipe1[2];
    int pipe2[2];
    int filter = 0;
    int numerx = 0;
    int pidfilho = 0;
    int restfork;
  
    imprimirin();
    varamb var = lervarambiente();
   if(access(SERV_PIPE,F_OK)){
         if(mkfifo(SERV_PIPE,0600)==-1){
            perror("[ERRO]na Criação do pipe do servidor.\n");
        }   
       
    }else{
        printf("[Erro] Ja existe uma instancia do servidor a correr.\n");
        exit(0);
    }
     if(access(PIPE_CHAMADA,F_OK)){
         if(mkfifo(PIPE_CHAMADA,0600)==-1){
            perror("[ERRO]na Criação do pipe de chamada.\n");
        }   
       
    }else{
        printf("[Erro] Ja existe uma instancia do pipe chamada a correr.\n");
        exit(0);
    }
    pthread_t tlogin;

    int res_login = pthread_create( &tlogin, NULL, recebelogins, NULL);

    
   
       if (pipe(pipe1) == -1)
    {
        fprintf(stderr, "[ERRO] Criacao pipe1\n");
        exit(1);
    }
    if (pipe(pipe2) == -1)
    {
        fprintf(stderr, "[ERRO] Criacao pipe2\n\n");
        exit(1);
    }


    restfork = fork();
    if (restfork == 0)
    { 
       close(pipe1[WRITE]);     // O dup2 fecha automáticamente a extremidade do pipe que não está a ser usado por exemplo o read.
       close(pipe2[READ]);
       dup2(pipe1[READ], READ);  //depois de fazer a troca dos fd's
       dup2(pipe2[WRITE], WRITE); 
       execl("verificador", "verificador", var.WORDSNOT, NULL);  
    }
    else
    {

        pidfilho = restfork;
        while (1)
        {
            printf("Intoduza um comando: ");
            scanf(" %[^\n]", cmd);
            fflush(stdin);
            removerespaco(cmd);
            int i;
            for ( i = 0; i < strlen(cmd); i++)
                cmd[i] = toupper(cmd[i]);

            b.comando = strtok(cmd, " ");
            b.argumento = strtok(NULL, " ");

            if (strcmp(b.comando, "SHUTDOWN") == 0)
            {
                encerrar(pidfilho);
            }
            else if (strcmp(b.comando, "FILTER") == 0 && b.argumento != NULL)
            {
                if (strcmp(b.argumento, "ON") == 0)
                {
                    printf("Filtro Status[ON].\n");
                    filter = 1;
                }
                else if (strcmp(b.argumento, "OFF") == 0)
                {
                    printf("Filtro Status[OFF].\n");
                    filter = 0;
                }
                else
                    printf("[ERRO] Argumento:%s invalido.\nArgumento:ON/OFF\n", b.argumento);
            }
            else if (strcmp(b.comando, "USERS") == 0)
            {
            }
            else if (strcmp(b.comando, "TOPICS") == 0)
            {   printf("\nTOPICS EXISTENTES:\n");
                int i=0;
                for(i;i<nTopics;i++){
                printf("Topic:%s\n",listatopics[i].topicos);
                }
            }
            else if (strcmp(b.comando, "HELP") == 0)
            {
                help();
            }
            else if (strcmp(b.comando, "MSG") == 0)
            {
            }
            else if (strcmp(b.comando, "MENSAGEM") == 0)
            {
                if (filter == 0)
                {
                    printf("Filtro encontra-se desativo, ativar,[filter on].\n");
                }
                printf("Introduz uma mensagem:");
                getchar();
                fgets(pal, sizeof(pal), stdin);
                if (filter == 1)
                {
                    close(pipe1[READ]);
                    close(pipe2[WRITE]);
                    if (write(pipe1[WRITE], pal, strlen(pal)) != strlen(pal))
                        fprintf(stderr, "[ERRO] Envio da mensagem!\n");

                    if (write(pipe1[WRITE], "\n", strlen("\n")) != strlen("\n"))
                        fprintf(stderr, "[ERRO] Envio do \\n \n");

                    if (write(pipe1[WRITE], "##MSGEND##\n", strlen("##MSGEND##\n")) != strlen("##MSGEND##\n"))
                        fprintf(stderr, "[ERRO] Envio do (##MSGEND##)\n");

                    int nbytes = read(pipe2[READ], buffer, strlen(buffer));
                    if (nbytes == errno)
                        fprintf(stderr, "[ERRO] A Ler do pipe2\n");
                    else
                        numerx = atoi(buffer);

                    printf("Numero de palavras invalidas:%d\n", numerx);
                }
            }
            else if (strcmp(b.comando, "DEL") == 0 && b.argumento != NULL)
            {
            }
            else if (strcmp(b.comando, "KICK") == 0 && b.argumento != NULL)
            {
            }
            else if (strcmp(b.comando, "PRUNE") == 0)
            {
            }
            else
            {
                printf("[ERRO] Comando %s invalido ou falta de argumentos!\n", cmd);
            }
        }
    }
   
}
