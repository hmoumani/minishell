/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:26:19 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/21 19:33:25 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_return(long num, int add, int sign)
{
	if (sign == 1 && (num > 922337203685477580 ||
	(num == 922337203685477580 && add > 7)))
		return (-1);
	else if (sign == -1 && (num > 922337203685477580 && add > 8))
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	long long	num;
	int			i;
	int			neg;

	num = 0;
	i = 0;
	neg = 1;
	if (*str == '-' || *str == '+')
	{
		neg = -*str + 44;
		i++;
	}
	else if (*str == ' ' || (*str > 8 && *str < 14))
		return (ft_atoi((str + 1)));
	while (*(str + i))
	{
		if (ft_return(num, *(str + i) - 48, neg) != 1)
			return (ft_return(num, *(str + i) - 48, neg));
		if (*(str + i) < 58 && *(str + i) > 47)
			num = num * 10 + (*(str + i) - 48);
		else
			break ;
		i++;
	}
	return ((int)(num * neg));
}

int			ft_custom_atoi(const char *str, int i, int *error)
{
	int					sign;
	unsigned long long	result;

	i = 0;
	while (str[0] == '\t' || str[0] == '\n' || str[0] == '\v' ||
			str[0] == '\f' || str[0] == ' ' || str[0] == '\r')
		str++;
	result = 0;
	sign = (str[0] == '-' ? -1 : 1);
	str = (str[0] == '-' || str[0] == '+') ? str + 1 : str;
	while (str[0] == '0')
		str++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i++] - '0');
		if ((result > 9223372036854775808ULL && sign == -1) ||
		(result >= 9223372036854775808ULL && sign == 1))
		{
			*error = 1;
			return (sign == 1 ? -1 : 0);
		}
	}
	return (result * sign);
}
