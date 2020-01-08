#include "gestor_default.h"
#include "geraldefinc.h"
    pthread_t lermensagem;
    pthread_t gestorc;

    msg_cli *mensagem=NULL;
    cli_dados * clientes=NULL;
    subs *listatopics=NULL;
    utsub *subscricoes=NULL;
    int nMensagem=0;
    int nUsers=0;
    int nTopics=0;
    int pipe1[2];
      int nSubs=0;
    int pipe2[2], filtro = 0;

void atualizaident(){
    int i=0;
        for(i=0; i< nMensagem; i++){
        mensagem[i].ident=i;

        }

}
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




void subsfunc(atendercli cli){
    utsub *temp;
    int res;
  if (subscricoes == NULL) {
  temp = (utsub*) malloc(sizeof(utsub) * 1);
      if(temp==NULL){
                 printf("Erro a  alocar  memoria para o vetor das mensagens");
             }else{
            subscricoes = temp;     
        
            strcpy(subscricoes[nSubs].nome_pipe_escrita,cli.nome_pipe_escrita);
                        strcpy(subscricoes[nSubs].topicos,cli.topico);

           nSubs++;

          
          }
        } else if(res ==1) {        
             temp = realloc(subscricoes, ( nSubs + 1) * sizeof(utsub));
             if(temp==NULL){
                 printf("Erro a  realocar memoria para o vetor das mensagens");
             }else{
             subscricoes=temp;
            
                  strcpy(subscricoes[nSubs].nome_pipe_escrita,cli.nome_pipe_escrita);
                        strcpy(subscricoes[nSubs].topicos,cli.topico);
                nSubs++;

         }
        }

}
void acrescentaMensagagem(msg_cli m){
    msg_cli *temp;
  if (mensagem == NULL) {
  temp = (msg_cli*) malloc(sizeof(msg_cli) * 1);
      if(temp==NULL){
                 printf("Erro a  alocar  memoria para o vetor das mensagens");
             }else{
            
            m.total=nMensagem;
            m.duracao=50;
            mensagem = temp;     
            mensagem[nMensagem] = m;
            acrescentartopic(mensagem[nMensagem]);
           nMensagem++;
        atualizaident();
          }
        } else {
             temp = realloc(mensagem, ( nMensagem+ 1) * sizeof(msg_cli));
             if(temp==NULL){
                 printf("Erro a  realocar memoria para o vetor das mensagens");
             }else{
             
                 m.total=nMensagem;
                 m.duracao=50;
             mensagem=temp;
              mensagem[nMensagem] = m;
            acrescentartopic(mensagem[nMensagem]);
             nMensagem++;
             atualizaident(); 
         }
        }
        
      fprintf(stderr,"Foi adicionada uma mensagem com o id %d\n",m.ident);   
}

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

void segementaNome(char username[] ,char * nome, char *numero){
  int i=0;
    int j=0, p=0;

    for ( i=0; i< strlen(username);i++){
    if(isdigit(username[i])==0){
        nome[j] =username[i];
        j++;
       nome= realloc(nome,j* sizeof(char));
    }else {
    numero[p]=username[i];
    p++;
    numero= realloc(numero, p*sizeof(char));
    }
    }

}

bool verificaDadosCliente(cli_dados *c){
    int i=0,numat, num;
    int conta=0;
    int maior=0;
    char *str;
    char *numero=(char*) malloc(sizeof(char));
    char *nome=(char*) malloc(sizeof(char));
   segementaNome(c->username,nome,numero);

       num= atoi(numero);
   char *atualizanum;
   char *atualizanome;
for( int i; i< nUsers;i++){
    printf("estou dentro do ciclo");
atualizanum=(char*) malloc(sizeof(char));
atualizanome=(char*) malloc(sizeof(char));

   segementaNome(clientes[i].username,atualizanome,atualizanum);
printf("nome %s", clientes[i].username);
printf("intoduzido:%s",nome);
    if( strcmp(nome,atualizanome)==0){// caso o nome seja o mesmo
    printf("sao iguais");
    conta ++;
      numat= atoi(atualizanum);
    if(maior < numat){
        maior =numat;
    }
    }
  
 free(atualizanome);
free(atualizanum); 
        }

maior +=1;
    str = malloc(strlen(nome)*sizeof(char));//+1* sizeof(char));
     if(maior !=0 && conta !=0){
         int l=0;
        for(  l=0; l< strlen(nome); l++)
        str[l] = nome[l];
    
        //str[l+1]=  maior;
        for(int k=0; k< strlen(str); i++)
        c->username[k] = str[k];
  printf("maior-> %d   \n", maior);  
        return true;
    }
free(str);
     free(numero);
    free(nome);

}




int verificaexisteTopico(char nome[]){
int i=0;
    for(i=0; i< nTopics; i++){
    if (strcmp(nome,listatopics[i].topicos)==0){
        return 0;
        }
    }
return 1;
}






void acrescentartopic (msg_cli informacao){
    subs *temp;
    int res;
     res=verificaexisteTopico(informacao.topico);
  if (listatopics == NULL) {
  temp = (subs*) malloc(sizeof(subs) * 1);
      if(temp==NULL){
                 printf("Erro a  alocar  memoria para o vetor das mensagens");
             }else{
            listatopics = temp;     
        
            strcpy(listatopics[nTopics].topicos,informacao.topico);
           nTopics++;

          
          }
        } else if(res ==1) {        
             temp = realloc(listatopics, ( nTopics + 1) * sizeof(subs));
             if(temp==NULL){
                 printf("Erro a  realocar memoria para o vetor das mensagens");
             }else{
             listatopics=temp;
            
              strcpy(listatopics[nTopics].topicos,informacao.topico);
             nTopics++;

         }
        }
fprintf(stderr,"foi adicionado um novo topico com o nome %s",informacao.topico);
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
              clientes[nUsers] = c;
             nUsers++;
         }
        }
    fprintf(stderr, "Foi adicionado um cliente  com o nome %s", c.username);

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
{   int i;
    for(i=0;i<nUsers;i++){
        printf("PID %d",clientes[i].pid);
        kill(clientes[i].pid,SIGUSR1);
    }
    kill(pidfilho,SIGUSR2);
    printf("Gestor encerrado com sucesso.\n");
    imprimirfi();
    unlink(SERV_PIPE);
    unlink(PIPE_CHAMADA);
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
int verificaUnicoTopico(char topico[]){
int i=0, conta=0;
for(i=0; i< nMensagem;i++){
    if(strcmp(mensagem[i].topico,topico)==0){
        conta++;
    }
}
return conta;
}
void removetopico(char topico[]){
   int ind=0;
    for(int i=0; i< nTopics; i++){
        if(strcmp(listatopics[i].topicos, topico)==0){

    subs *temp = malloc((nTopics - 1) * sizeof(subs)); // allocate an array with a size 1 less than the current one

    if (ind != 0)
        memcpy(temp, listatopics, ind * sizeof(subs)); // copy everything BEFORE the index

    if (ind != (nTopics - 1))
        memcpy(temp+ind, listatopics+ind+1, (nTopics - ind - 1) * sizeof(subs)); // copy everything AFTER the index

    listatopics= temp;
    nTopics--;
    free(temp);


        }
    }
fprintf(stderr, "Foi removido um topico com o nome %s\n", topico);

}
void removeMensagem( int id){

  int ind=0;
    for(int i=0; i< nMensagem; i++){
        if(mensagem[i].ident==id){

    msg_cli*temp = malloc((nMensagem - 1) * sizeof(msg_cli)); // allocate an array with a size 1 less than the current one

    if (i != 0)
        memcpy(temp, mensagem, i * sizeof(msg_cli)); // copy everything BEFORE the index

    if (i != (nMensagem - 1))
        memcpy(temp+i, mensagem+i+1, (nMensagem - i - 1) * sizeof(msg_cli)); // copy everything AFTER the index

    mensagem= temp;
    nMensagem--;
        }
    }
    fprintf(stderr, "Foi removida uma mensagem com o id %d\n", id);

}


//
void * DecrementaTempo(void * ms){
    msg_cli *msg;
     msg =(msg_cli*) ms;
    
    int unico;
    sleep(msg->duracao);
 
        removeMensagem(msg->ident);
        atualizaident();
    
}

void * recebermensagens(void * nomepipe){
int res=0;

    do{
      int fd_cliente=open(nomepipe,O_RDONLY);
      msg_cli m;
       int n=read(fd_cliente,&m,sizeof(msg_cli));
        if(n!=-1){
           
               acrescentaMensagagem(m);
        pthread_t t_msg;        
     
     int res = pthread_create( &t_msg, NULL, DecrementaTempo, (void*) &mensagem[nMensagem-1]);
     
if(res!=0){
    printf("Erro a  lancar a thread para mensagem com o titulo %s", m.titulo);
        }
         }

   }while(1);
}
//NESTA FUNÇÃO  CHAMDO O METODO DE VERIFICAR
void * recebelogins(){
   do{
     cli_dados c;
      int fd_serv=open(SERV_PIPE,O_RDONLY);
   read(fd_serv,&c,sizeof(cli_dados));
//verificaDadosCliente(&c); 

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
    int res_topicsenviar = pthread_create( &gestorc, NULL, gestorcliente, NULL);
    
   }
    }while(1);


}



void * gestorcliente(){
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

        if(atender.flag==4){
          subsfunc(atender);  
          printf("topic subscrito foi %s \n pelo %s\n",subscricoes[0].topicos,subscricoes[0].nome_pipe_escrita);
        }
         
        atender.flag=0;
}while(1);

}
void listautilizadores(){
for (int i=0; i< nUsers;i++){
    printf("Nome: %s\n",clientes[i].username);
}
}
void cmdPrune(){
int unico=0;
for(int i=0; i<nMensagem; i++){
   unico = verificaUnicoTopico(mensagem[i].topico);

       if(unico==1){
        removetopico(mensagem[i].topico);
    }
     
}

}
void listamensagens(){
int i=0;
for( i=0; i< nMensagem; i++){
printf("Mensagem %d\n", mensagem[i].ident);
printf("Titulo:  %s\n",mensagem[i].titulo);
printf("Topico:  %s\n",mensagem[i].topico);
printf("Corpo:   %s\n",mensagem[i].corpo);
}


}

void listaMensagensDeTopico( char topico[]){
int i=0;
char str[strlen(topico)];
for(i=0; i<strlen(topico);i++){
str[i]=tolower(topico[i]);
}
str[i]='\0';

for(i=0; i<nMensagem;i++){
    if(strcmp(str,mensagem[i].topico)==0){
        printf("Mensagem %d\n", mensagem[i].ident);
        printf("Titulo:  %s\n",mensagem[i].titulo);
        printf("Topico:  %s\n",mensagem[i].topico);
        printf("Corpo:   %s\n",mensagem[i].corpo);
    }

    }

}




int main(int argc, char *argv)
{
    char cmd[50], pal[200];
    cmds b;
    b.argumento = NULL;   
   
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
          // int res=filtramensagem("a maria tem de colocar isto a dar");
            //  printf("%d",res);
char buffer[3];
int numerx;
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
                    filtro = 1;
                }
                else if (strcmp(b.argumento, "OFF") == 0)
                {
                    printf("Filtro Status[OFF].\n");
                    filtro = 0;
                }
                else
                    printf("[ERRO] Argumento:%s invalido.\nArgumento:ON/OFF\n", b.argumento);
            }else if (strcmp(b.comando, "MENSAGEM") == 0)
            {
           
                if (filtro == 1)
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
            
            else if (strcmp(b.comando, "USERS") == 0)
            {
                printf("\nUtilizadores EXISTENTES:\n");
                listautilizadores();
            }
            else if (strcmp(b.comando, "TOPICS") == 0)
            {   if(nTopics==0){
                printf("\nNao existem topicos armazenados\n");

                }else{
                printf("\nTOPICS EXISTENTES:\n");
                int i=0;
                for(i;i<nTopics;i++){
                printf("Topic:%s\n",listatopics[i].topicos);
                }
                }
            }
            else if (strcmp(b.comando, "HELP") == 0)
            {
                help();
            }
            else if (strcmp(b.comando, "MSG") == 0)
            {
                if(nMensagem==0){
                    printf("\nNao existem mensagens armazenadas\n");
                }else{
                    printf("\nMENSAGEM EXISTENTES:\n");
                listamensagens();
                }

            }
            else if(strcmp(b.comando,"TOPIC")==0 && b.argumento!=NULL){
                printf("argumento %s", b.argumento);
                listaMensagensDeTopico(b.argumento);

            }
                        else if (strcmp(b.comando, "DEL") == 0 && b.argumento != NULL)
            {
            int id = atoi(b.argumento);
            removeMensagem(id);

            }
            else if (strcmp(b.comando, "KICK") == 0 && b.argumento != NULL)
            {

            }
            else if (strcmp(b.comando, "PRUNE") == 0)
            {
                cmdPrune();//falta avisar clientes
            }
            else
            {
                printf("[ERRO] Comando %s invalido ou falta de argumentos!\n", cmd);
            }
        }
    }
   
}
