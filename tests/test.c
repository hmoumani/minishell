#include <unistd.h>
#include <stdio.h>
#include "includes/minishell.h"


int main(int argc, char **argv, char **env) {
	
	int b;
	write(2, "start\n", 6);
	while (read(0, &b, 1) > 0)
	{
		write(2, &b, 1);
	}
	write(2, "finish\n", 7);
	return (4);
}
