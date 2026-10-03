#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "builtins.h"

//static oq nao eh usado pela main
static int execCd(char **args);
//static int execHelp(char **args);


typedef struct
{
    char *name;
    int (*func)(char **args); 
}Builtins;




static Builtins builtins[] =
    {
        {"cd", &execCd},
        //{"help", &execHelp}
    };
    

static int totalBuiltins = sizeof(builtins) / sizeof(builtins[0]);




static int execCd(char **args) //path
{   
    int i;
    if(args[1] == NULL)
        i = chdir(getenv("HOME"));
    else
        i = chdir(args[1]);   //else pra evitar acessar args 1 quando é null pq da segmentation 
    
    if(i != 0)
    {
        perror("minibash cd");    
        return 1; //n foi
    }
    return 0; //foi
}



int findBuiltin(char *name)  //index ou -1
{
    int builtinIndex = -1;

    for (int i = 0; i < totalBuiltins; i++)
    {
        if(strcmp(name,builtins[i].name) == 0)
        {
            builtinIndex = i;
            return builtinIndex;
        }
    }
    return builtinIndex;
}


int execBuiltin(char **args, int index)
{
    int exec = builtins[index].func(args);
    return exec;
}

