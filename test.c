#include <unistd.h>
#include <stdio.h>
#include "includes/minishell.h"


int main(int argc, char **argv, char **env) {
	
	char **tmp = ft_split("ll=wefwe", '=');
	int i = 0;

	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}

	return (4);
}
