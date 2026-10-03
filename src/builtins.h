//literalmente if not defined, define (garantir que nao vai ter duplicidade)
#ifndef BUILTINS_H
#define BUILTINS_H

int findBuiltin(char *name);  //so precisa receber o nome do comando, ex: cd
int execBuiltin(char **args, int index);

#endif