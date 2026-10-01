#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> //fork, execvp
#include <sys/wait.h> //waitpid

#define DELIMS " \t"

char **parser(char *line, size_t *n);

void execute(char **args);

int main(void)
{
    size_t n=0; //numero de tokens
    char *line = NULL;
    size_t cap = 0;

    

    while(1)
    {

        printf("minishell>");
        fflush(stdout); //limpa o buffer

        ssize_t len = getline(&line, &cap, stdin); //&line pq getline recebe ** e &cap pq recebe * 
        //e o getline aloca e realoca o buffer sozinho, então só precisa dar free uma vez no final

        if(len == -1)//ctrl d, (EOF) ou erro
        {
            printf("\n");
            break;
        }
        
        
        if(len>0 && line[len -1] == '\n')
        line[len-1] = '\0';
        
        if(line[0] =='\0')
        continue;
        
        if(strcmp(line, "exit") == 0)
            break;  
        
        char **tokenized = parser(line,&n);

        execute(tokenized);
        free(tokenized);
    }

    
    free(line);
    return 0;
}

char **parser(char *line, size_t *n) //transformar "ski bidi" em ["ski","bidi",NULL]
{
    *n = 0;
    size_t cap = 16; 
    char **toks = malloc(cap*sizeof(char*));

    if (toks == NULL)
        perror("erro de alocação");
    

    char *tok = strtok(line, DELIMS);
    while(tok!=NULL)
    {
        if((*n)+1>=cap) //pensando em deixar sempre um espaço a mais pro NULL 
        {
            cap*=2; //dobrando o espaço caso necessario
            toks = realloc(toks, cap*sizeof(char*));
            if (toks == NULL)
                perror("erro de realocação");
            
        }

        toks[(*n)++] = tok;//ou toks[n] = tok; n++;
        tok = strtok(NULL, DELIMS);
    }

    toks[*n] = NULL;

    return toks;
}

void execute(char **args)
{
    int status;
    pid_t pid = fork(); //duplica o processo

    if(pid == -1)
    {
        perror("erro do fork");
        return;
    }

    if(pid==0) //fork retorna 0 quando chama o child process
    {
        execvp(args[0], args); //onde de fato sao chamados os comandos

        perror("minishell");//so chega aqui se ^ der errado 
        exit(127);//convençao de comando nao encontrado
    }

    //guarda no status como o child terminou, da pra ver funcionando dando "sleep (numero)"
    waitpid(pid,&status,0);

}