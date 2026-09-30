#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
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

        printf("digitado: %s\n", line);
    }

    free(line);
    return 0;
}