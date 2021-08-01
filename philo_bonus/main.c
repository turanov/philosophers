/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:12:03 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:12:04 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long long time, struct timeval now)
{
	long long	cur_time;

	cur_time = g_ms(now);
	while (1)
	{
		usleep(100);
		if (g_ms(now) == cur_time + time)
			break ;
	}
}

int	init_data(char **argv)
{
	g_data->number = ft_atoi(argv[1]);
	g_data->time_dea = ft_atoi(argv[2]);
	g_data->time_eat = ft_atoi(argv[3]);
	g_data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_data->must_eat = ft_atoi(argv[5]);
	else
		g_data->must_eat = -1;
	g_data->cnt_must_eat = 0;
	g_data->last_eat = 0;
	gettimeofday(&g_data->start_eat, NULL);
	sem_unlink("sem_print");
	sem_unlink("sem_is_dead");
	sem_unlink("sem_forks");
	sem_unlink("sem_wait_dead");
	g_data->sem_print = sem_open("sem_print", O_CREAT, 0777, 1);
	g_data->sem_is_dead = sem_open("sem_is_dead", O_CREAT, 0777, 0);
	g_data->sem_forks = sem_open("sem_forks", O_CREAT, 0777, g_data->number);
	g_data->sem_wait_dead = sem_open("sem_wait_dead", O_CREAT, 0777, 0);
	if (g_data->sem_forks == SEM_FAILED || g_data->sem_is_dead == SEM_FAILED
		|| g_data->sem_print == SEM_FAILED
		|| g_data->sem_wait_dead == SEM_FAILED)
		return (0);
	return (1);
}

int	error_input(int code)
{
	if (code == 1)
		printf("Error, arguments must be 5 or 6\n");
	else if (code == 2)
		printf("Error, invalid arguments\n");
	else if (code == 3)
		printf("Error, can't malloc\n");
	else if (code == 4)
		printf("Error, can't create threads\n");
	return (1);
}

void	create_forks(int id)
{
	int	i;

	i = 0;
	gettimeofday(&g_data->start_eat, NULL);
	while (i < g_data->number)
	{
		id = fork();
		if (id < 0)
			exit(2);
		if (id == 0)
		{
			g_data->last_eat = 0;
			g_data->name = i ;
			if (!solve(&g_data->name))
			{
				g_data->number = i;
				sem_post(g_data->sem_is_dead);
				exit(0);
			}
		}
		i++;
	}
	while (g_data->number--)
		sem_wait(g_data->sem_wait_dead);
	exit(0);
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
	if (g_data->must_eat == 0)
		exit(0);
	create_forks(0);
	exit(0);
}
