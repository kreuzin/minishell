#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMS " \t"

char **parser(char *line, size_t *n);

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

        if(len == -1)//ctrl d (EOF) ou erro
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


        for (size_t i = 0; i < n+1; i++)
        {
            if(tokenized[i] != NULL)
                printf("%s ",tokenized[i]);
            else
                printf("NULL");
        }
        printf("\n");
        
        
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