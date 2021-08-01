/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:11:31 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:11:33 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	g_ms(struct timeval old)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	new.tv_sec -= old.tv_sec;
	new.tv_usec -= old.tv_usec;
	if (new.tv_usec < 0)
	{
		--new.tv_sec;
		new.tv_usec += 1000000;
	}
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

void	my_usleep(long time, struct timeval now)
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

void	lock_forks(int cur, int next)
{
	if (cur % 2 == 1)
	{
		pthread_mutex_lock(&g_data->philo[next].fork);
		ft_print("has taken a fork", g_ms(g_data->start_eat), cur + 1);
		pthread_mutex_lock(&g_data->philo[cur].fork);
		ft_print("has taken a fork", g_ms(g_data->start_eat), cur + 1);
	}
	else
	{
		pthread_mutex_lock(&g_data->philo[cur].fork);
		ft_print("has taken a fork", g_ms(g_data->start_eat), cur + 1);
		pthread_mutex_lock(&g_data->philo[next].fork);
		ft_print("has taken a fork", g_ms(g_data->start_eat), cur + 1);
	}
	g_data->philo[cur].last_eat = g_ms(g_data->start_eat);
	ft_print("is eating", g_ms(g_data->start_eat), cur + 1);
	my_usleep(g_data->time_eat, g_data->start_eat);
	pthread_mutex_unlock(&g_data->philo[next].fork);
	pthread_mutex_unlock(&g_data->philo[cur].fork);
}

void	*solve(void *num)
{
	int	cur;
	int	next;

	cur = *(int *)num;
	if (cur == 0)
		next = g_data->number - 1;
	else
		next = cur - 1;
	while (1)
	{
		lock_forks(cur, next);
		ft_print("is sleeping", g_ms(g_data->start_eat), cur + 1);
		my_usleep(g_data->time_sleep, g_data->start_eat);
		ft_print("is thinking", g_ms(g_data->start_eat), cur + 1);
		g_data->philo[cur].count_eat++;
		if (g_data->philo[cur].count_eat == g_data->must_eat)
			g_data->cnt_must_eat++;
	}
}

void	*monitoring(void *arg)
{
	int			i;
	long long	now;

	(void)arg;
	i = 0;
	while (1)
	{
		if (g_data->cnt_must_eat == g_data->number)
			break ;
		now = g_ms(g_data->start_eat);
		if (now - g_data->philo[i].last_eat > g_data->time_dea)
		{
			g_data->is_dead = i + 1;
			g_data->time_dead = now;
			break ;
		}
		i++;
		if (i == g_data->number)
			i = 0;
	}
	return (NULL);
}
