/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:40:57 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:41:04 by hmoumani         ###   ########.fr       */
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
		ft_fprintf(2, "minishell: exit: %s: %s\n", argv[1], s);
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
	if (!argv || !argv[1])
	{
		exit(g_minishell.return_code);
	}
	if (!ft_isnumber(argv[1]))
	{
		ft_fprintf(2, "minishell: exit: %s: %s\n", argv[1], s);
		exit(255);
	}
	if (ft_ptr_str_len(argv) > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		exit(1);
	}
	exit_value(0, argv);
	return (0);
}
