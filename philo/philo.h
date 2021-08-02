/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:11:42 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 13:11:43 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	int					name;
	int					count_eat;
	long long			last_eat;
	pthread_mutex_t		fork;
	pthread_t			thread;
}						t_philo;

typedef struct s_data
{
	int					number;
	long long			time_dea;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					cnt_must_eat;
	int					is_dead;
	long long			time_dead;
	struct timeval		start_eat;
	pthread_mutex_t		print;
	t_philo				*philo;
}						t_data;

t_data			*g_data;
int				create_threads(int i );
long long int	g_ms(struct timeval old);
int				ft_strlen(const char *str);
int				is_number(char *str);
int				is_valid(int argc, char **argv);
int				ft_atoi(const char *str);
void			*monitoring(void *arg);
void			*solve(void *num);
void			ft_print(char *str, long long ms, int philo_name);
int				error_input(int code);
#endif
