/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:11:22 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:11:24 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str++ != '\0')
		i++;
	return (i);
}

int	is_number(char *str)
{
	int	i;
	int	n;

	n = ft_strlen(str);
	i = 0;
	while (i < n && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i != n || n == 0)
		return (0);
	return (1);
}

int	is_valid(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	ans;

	ans = 0;
	while (*str)
	{
		ans = ans * 10 + (*str - 48);
		str++;
	}
	return (ans);
}

void	ft_print(char *str, long long ms, int philo_name)
{
	pthread_mutex_lock(&g_data->print);
	printf("%lldms %d %s\n", ms, philo_name, str);
	pthread_mutex_unlock(&g_data->print);
}
