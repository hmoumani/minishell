#include <unistd.h>
#include <stdio.h>
#include "includes/minishell.h"


int main(int argc, char **argv, char **env) {
	
	for (int i = 0; i < argc; i++)
	{
		printf("|%s|\n", argv[i]);
	}
	return (5);
}
