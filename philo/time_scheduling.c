/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_scheduling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:37:35 by bbosnak           #+#    #+#             */
/*   Updated: 2023/12/13 20:37:36 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <sys/time.h>

long	get_time(void)
{
	struct timeval	start_time;
	long			curr;

	gettimeofday(&start_time, NULL);
	curr = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return (curr);
}

void	my_usleep(long parameter, t_generic *dead_break)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < parameter)
	{
		pthread_mutex_lock(&dead_break->life);
		if (dead_break->dead_or_alive == 0)
		{
			pthread_mutex_unlock(&dead_break->life);
			break ;
		}
		pthread_mutex_unlock(&dead_break->life);
		usleep(100);
	}
}

int	monitoring(t_philosopher *philo, t_generic	*main_struct)
{
	int	i;

	i = 0;
	while (i < philo->generic_struct->num_philo)
	{
		pthread_mutex_lock(&philo->generic_struct->eating);
		if (get_time() - philo[i].last_eaten >= main_struct->life_time)
		{
			pthread_mutex_unlock(&philo->generic_struct->eating);
			death(main_struct);
			print_message(&philo[i], 5);
			return (1);
		}
		pthread_mutex_unlock(&philo->generic_struct->eating);
		i++;
	}
	return (0);
}
