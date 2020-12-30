#include <unistd.h>
#include <stdio.h>
#include "includes/minishell.h"

void    ft_export(char **argv)
{
	int fd;

	fd = open("/usr/bin/env", O_APPEND);
	char **sp = ft_split(argv[1], '=');
	ft_putnbr_fd(fd, 2);
	ft_putstr_fd(sp[0], fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd(sp[1], fd);
	ft_putstr_fd("\n", fd);
}
int main(int argc, char **argv, char **env) {
	
	struct stat sb;
	// if (stat(argv[1], &sb) == 0 && sb.st_mode & S_IXUSR) 
	// 	printf("noice");
	// else
	// 	printf("unnoice");
	// for (int i = 0; env[i] != NULL; i++){
	// 	printf("%s", env[i]);
	// }


	int fd;

	fd = open("/usr/bin/env", O_APPEND);
	// char **sp = ft_split("amatersu=hello", '=');
	ft_putnbr_fd(fd, 2);
	ft_putstr_fd("amatersu", fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd("hello", fd);
	ft_putstr_fd("\n", fd);

	return (0);
}
