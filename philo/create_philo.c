/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:36:44 by bbosnak           #+#    #+#             */
/*   Updated: 2023/12/13 20:36:45 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int	eating(t_philosopher *philo, t_generic *main_struct)
{
	int	i;
	int	total_meals;

	i = 0;
	total_meals = 0;
	while (i < philo->generic_struct->num_philo)
	{
		pthread_mutex_lock(&philo->generic_struct->eating);
		if (philo[i].eaten == main_struct->number_of_meals)
			total_meals++;
		if (total_meals >= main_struct->num_philo)
		{
			pthread_mutex_unlock(&philo->generic_struct->eating);
			death(main_struct);
			return (1);
		}
		pthread_mutex_unlock(&philo->generic_struct->eating);
		i++;
	}
	return (0);
}

t_generic	*fill_in_struct(t_generic *main, char **argv, int argc)
{
	if (!argv)
		return (NULL);
	main = malloc(sizeof(t_generic));
	if (!main)
		return (error_messages(1), NULL);
	main->num_philo = philo_atoi(argv[1]);
	main->life_time = philo_atoi(argv[2]);
	main->eat_time = philo_atoi(argv[3]);
	main->sleep_time = philo_atoi(argv[4]);
	main->number_of_meals = 0;
	if (argc == 6)
		main->number_of_meals = philo_atoi(argv[5]);
	main->dead_or_alive = 1;
	main->philo = malloc(sizeof(t_philosopher) * main->num_philo);
	if (!main->philo)
		return (free(main), error_messages(1), NULL);
	main->right_fork = malloc(sizeof(pthread_mutex_t) * main->num_philo);
	if (!main->right_fork)
		return (free(main->philo), free(main), error_messages(1), NULL);
	return (main);
}

void	philo_init(t_generic *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->num_philo)
	{
		main_struct->philo[i].generic_struct = main_struct;
		main_struct->philo[i].last_eaten = get_time();
		main_struct->philo[i].sleeping = 0;
		main_struct->philo[i].dying = main_struct->life_time;
		main_struct->philo[i].eaten = 0;
		i++;
	}
}

void	*life(void *data_struct)
{
	t_generic		*main_struct;
	t_philosopher	*philo;

	main_struct = data_struct;
	philo = main_struct->philo;
	while (1)
	{
		if (main_struct->number_of_meals > 0 && eating(philo, main_struct))
			return (NULL);
		if (monitoring(philo, main_struct))
			return (NULL);
	}
	return (NULL);
}

int	create_philo(t_generic *main_struct)
{
	int			i;
	pthread_t	life_check;

	i = 0;
	philo_init(main_struct);
	main_struct->start_time = get_time();
	while (i < main_struct->num_philo)
	{
		main_struct->philo[i].philosopher_id = i + 1;
		if (pthread_create(&main_struct->philo[i].philo, NULL,
				routine, &main_struct->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&life_check, NULL, life, main_struct) != 0)
		return (0);
	if (pthread_join(life_check, NULL) != 0)
		return (error_messages(4), 1);
	return (0);
}
