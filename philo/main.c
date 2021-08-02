/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:11:07 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:11:14 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(int i)
{
	while (i-- > 0)
		pthread_detach(g_data->philo[i].thread);
	free(g_data);
}

int	init_data(char **argv)
{
	int	i;

	g_data->number = ft_atoi(argv[1]);
	gettimeofday(&g_data->start_eat, NULL);
	pthread_mutex_init(&g_data->print, NULL);
	if (argv[5])
		g_data->must_eat = ft_atoi(argv[5]);
	else
		g_data->must_eat = -1;
	g_data->philo = malloc(sizeof(t_philo) * g_data->number);
	if (g_data->philo == NULL)
		return (0);
	i = 0;
	g_data->cnt_must_eat = 0;
	g_data->is_dead = 0;
	while (i < g_data->number)
	{
		g_data->philo[i].name = i;
		g_data->philo[i].count_eat = 0;
		if (pthread_mutex_init(&g_data->philo[i].fork, NULL))
			return (1);
		i++;
	}
	return (1);
}

int	create_threads(int i)
{
	pthread_t	monitor;

	while (i < g_data->number)
	{
		gettimeofday(&g_data->start_eat, NULL);
		g_data->philo[i].last_eat = 0;
		if (pthread_create(&g_data->philo[i].thread, NULL,
				solve, &g_data->philo[i].name) != 0)
			return (i);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring, NULL) != 0)
		return (i);
	if (pthread_join(monitor, NULL) != 0)
	{
		pthread_detach(monitor);
		return (i);
	}
	if (g_data->is_dead)
	{
		pthread_mutex_lock(&g_data->print);
		printf("%lldms %d is dead\n", g_data->time_dead, g_data->is_dead);
	}
	free_data(g_data->number);
	return (0);
}

int	start(void)
{
	int	i;

	i = create_threads(0);
	if (i)
	{
		free_data(i);
		return (error_input(4));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (error_input(1));
	if (!is_valid(argc, argv))
		return (error_input(2));
	g_data = malloc(sizeof(t_data));
	if (!g_data)
		return (error_input(3));
	if (!init_data(argv))
	{
		free(g_data);
		return (error_input(4));
	}
	g_data->time_dea = ft_atoi(argv[2]);
	g_data->time_eat = ft_atoi(argv[3]);
	g_data->time_sleep = ft_atoi(argv[4]);
	if (g_data->must_eat == 0)
	{
		free(g_data);
		return (1);
	}
	return (start());
}
