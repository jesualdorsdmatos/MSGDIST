:7#include "gestor_default.h"
#include "geraldefinc.h"


void imprimirin(){
    printf("************************************************\n");
    printf("**       BEM-VINDO AO GESTOR DO MSGDIST       **\n");
    printf("**Comando:[help] para listar todos os comandos**\n");
    printf("************************************************\n");
}


void imprimirfi(){
    printf("*************************************************\n");
    printf("**           Trabalho realizado por:           **\n");
    printf("**       Jesualdo Matos/Francisco Silva        **\n");
    printf("*************************************************\n");
}

// Retira espacos a mais entre os comandos
void removerespaco(char str[])
{
    int j = 0;
    for (int i = 0; str[i]; i++)
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

    //Maxima de palavras rejeitas
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
        strcpy(var.WORDSNOT, "WORDSNOT");
    return var;
}

void encerrar(int pidfilho)
{
    if(kill(pidfilho,SIGUSR2)!=0)
    printf("[ERRO] a encerrar verificador.\n");
    printf("Gestor encerrado com sucesso.\n");
    imprimirfi();
    exit(0);
}

void help(){
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
    int pidfilho=0;
    int restfork;
    imprimirin();
    varamb var = lervarambiente();
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

    restfork=fork();
    if (restfork==0)
    {
        close(pipe1[WRITE]);// como não são utilizadas estas duas extremidades são fechadas de imediato
        close(pipe2[READ]);
        dup2(pipe1[READ], READ);// depois de fazer a troca dos fd's
        dup2(pipe2[WRITE], WRITE);
        close(pipe1[READ]);// fechamos estas entradas que não vão ser utilizadas
        close(pipe2[WRITE]);
        execl("verificador", "verificador", var.WORDSNOT, NULL);
    }else{

        pidfilho=restfork;
    while (1)
    {
        printf("Intoduza um comando: ");
        scanf(" %[^\n]", cmd);
        fflush(stdin);
        removerespaco(cmd);

        for (int i = 0; i < strlen(cmd); i++)
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
            printf("O filtro das mensagens foi ativado com sucesso.\n");
            filter = 1;
            }
            else if (strcmp(b.argumento, "OFF") == 0)
            {
           printf("O filtro das mensagens foi desativado com sucesso.\n");
            filter = 0;
            }
            else
                printf("[ERRO] Argumento:%s invalido.\nArgumento:ON/OFF\n", b.argumento);
        }
        else if (strcmp(b.comando, "USERS") == 0)
        {
        }
        else if (strcmp(b.comando, "TOPICS") == 0)
        {
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
            if(filter==0){
                printf("Relembro que o filtro de mensagem esta desativado, para ativar comando [filter on].\n");
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

                if(write(pipe1[WRITE], "\n", strlen("\n"))!=strlen("\n"))
                    fprintf(stderr, "[ERRO] Envio do \\n \n");


                if (write(pipe1[WRITE], "##MSGEND##\n", strlen("##MSGEND##\n")) != strlen("##MSGEND##\n"))
                    fprintf(stderr, "[ERRO] Envio do (##MSGEND##)\n");

                int nbytes = read(pipe2[READ], buffer, strlen(buffer));
                if (nbytes ==errno)
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