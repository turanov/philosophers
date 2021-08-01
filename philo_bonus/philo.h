/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:12:08 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:12:35 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_data
{
	int					name;
	int					number;
	int					time_dea;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					cnt_must_eat;
	long long			last_eat;
	struct timeval		start_eat;
	sem_t				*sem_print;
	sem_t				*sem_forks;
	sem_t				*sem_is_dead;
	sem_t				*sem_wait_dead;
}						t_data;

t_data			*g_data;
void			create_forks(int id);
long long int	g_ms(struct timeval old);
int				ft_strlen(const char *str);
int				is_number(char *str);
int				is_valid(int argc, char **argv);
int				ft_atoi(const char *str);
void			*monitoring(void *arg);
void			*solve(void *num);
void			ft_print(char *str, long long ms, int philo_name);
void			my_usleep(long long time, struct timeval now);
#endif
