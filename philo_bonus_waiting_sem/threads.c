/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:12:51 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:12:52 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	g_ms(struct timeval old)
{
	struct timeval	new;
	struct timeval	diff;

	gettimeofday(&new, NULL);
	diff.tv_sec = new.tv_sec - old.tv_sec;
	diff.tv_usec = new.tv_usec - old.tv_usec;
	if (diff.tv_usec < 0)
	{
		--diff.tv_sec;
		diff.tv_usec += 1000000;
	}
	return ((diff.tv_sec * 1000) + (diff.tv_usec / 1000));
}

void	*monitoring(void *name)
{
	long long	now;

	while (1)
	{
		now = g_ms(g_data->start_eat);
		if (now - g_data->last_eat > g_data->time_dea)
		{
			sem_wait(g_data->sem_print);
			printf("%lldms %d is dead\n", now, *(int *)name + 1);
			sem_post(g_data->sem_is_dead);
			exit(1);
		}
	}
}

void	lock_forks(int cur)
{
	sem_wait(g_data->sem_forks);
	ft_print("has taken a fork", g_ms(g_data->start_eat), cur + 1);
	sem_wait(g_data->sem_forks);
	ft_print("has taken a fork", g_ms(g_data->start_eat), cur + 1);
	g_data->last_eat = g_ms(g_data->start_eat);
	ft_print("is eating", g_ms(g_data->start_eat), cur + 1);
	my_usleep(g_data->time_eat, g_data->start_eat);
	sem_post(g_data->sem_forks);
	sem_post(g_data->sem_forks);
}

void	*solve(void *num)
{
	int			cur;
	pthread_t	thread;

	sem_wait(g_data->sem_wait_all);
	gettimeofday(&g_data->start_eat,NULL);
	cur = *(int *)num;
	if (pthread_create(&thread, NULL, monitoring, num) != 0)
		return (NULL);
	while (1)
	{
		lock_forks(cur);
		ft_print("is sleeping", g_ms(g_data->start_eat), cur + 1);
		my_usleep(g_data->time_sleep, g_data->start_eat);
		ft_print("is thinking", g_ms(g_data->start_eat), cur + 1);
		g_data->cnt_must_eat++;
		if (g_data->cnt_must_eat == g_data->must_eat)
		{
			sem_post(g_data->sem_is_eat);
			exit(1);
		}
	}
}

int	create_forks(int i, int id)
{
	pthread_t	thread;

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
	if (pthread_create(&thread, NULL, monitor_for_eat, NULL) != 0)
		return (1);
	i = 0;
	while (i++ < g_data->number)
		sem_post(g_data->sem_wait_all);
	sem_wait(g_data->sem_is_dead);
	return (kill(0, SIGKILL));
}
