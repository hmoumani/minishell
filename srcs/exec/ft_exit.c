/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:16:16 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/13 10:43:34 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_isnumber(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && (s[i] == '\t' || s[i] == '\f' || s[i] == '\r'))
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	i = 0;
	while (*s == '-' || *s == '+' || *s == '0')
	{
		s++;
	}
	while (s[i])
	{
		i++;
	}
	if (i > 19)
		return (0);
	return (1);
}

void	exit_value(int ret, char **argv)
{
	int		error;
	char	*s;

	error = 0;
	s = "numeric argument required";
	ret = ft_custom_atoi(argv[1], 0, &error);
	if (error)
	{
		ft_mprint("minishell: exit: ", argv[1], ": ", s);
		exit(255);
	}
	if (ret > 255)
		exit(ret - 1 - 255);
	else if (ret < 0)
		exit(256 + ret);
	else
		exit(ret);
}

int		ft_exit(char **argv)
{
	char *s;

	s = "numeric argument required";
	write(2, "exit\n", 5);
	if (!argv || !argv[1])
	{
		exit(g_minishell.return_code);
	}
	if (!ft_isnumber(argv[1]))
	{
		ft_mprint("minishell: exit: ", argv[1], ": ", s);
		exit(255);
	}
	if (ft_ptr_str_len(argv) > 2)
	{
		ft_mprint("minishell: ", "exit: ", NULL, "too many arguments");
		exit(1);
	}
	exit_value(0, argv);
	return (0);
}
