#include <unistd.h>
#include <stdio.h>
#include "includes/minishell.h"


int main(int argc, char **argv, char **env) {
	
	int b = 0;
	write(2, "START\n", 6);
	while (b < 1000000000)
	{
		b++;
	}
	write(1, "FINISH\n", 7);
	return (5);
}
