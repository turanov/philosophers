/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshaina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 15:26:59 by sshaina           #+#    #+#             */
/*   Updated: 2021/08/01 15:27:01 by sshaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
