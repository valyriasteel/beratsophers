/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:37:09 by bbosnak           #+#    #+#             */
/*   Updated: 2023/12/13 20:37:10 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free(t_generic *main)
{
	if (main->philo)
		free(main->philo);
	if (main->right_fork)
		free(main->right_fork);
	if (main)
		free(main);
}

void	error_messages(int which_error)
{
	if (which_error == 1)
		printf("Allocation went wrong\n");
	else if (which_error == 2)
		printf("Too few or too many arguments\n");
	else if (which_error == 3)
		printf("Input error: each input must be bigger than 0\n");
	else if (which_error == 4)
		printf("Threads not running\n");
	else if (which_error == 5)
		printf("Mutexes have some conflicts\n");
	else if (which_error == 6)
		printf("Destroying mutexes was unsuccessful\n");
}

void	special_case(t_generic *main)
{
	if (!main)
		return ;
	printf("0 1 has taken a fork\n");
	my_usleep(main->life_time, main);
	printf(BOLD"%ld 1 died\n"RESET, main->life_time);
}

int	main(int argc, char **argv)
{
	t_generic	*main;

	main = NULL;
	if ((argc < 5 || argc > 6) || !argv)
		return (error_messages(2), 0);
	if (check_inputs(argv) == 0)
		return (error_messages(3), 0);
	main = fill_in_struct(main, argv, argc);
	if (!main)
		return (0);
	mutex_init(main);
	if (philo_atoi(argv[1]) == 1)
		special_case(main);
	else if (philo_atoi(argv[1]) > 1 && philo_atoi(argv[1]) <= 200)
		threads_and_routine(main);
	else
		printf("Please type num of philo between 1 and 200\n");
	mutex_destroy(main);
	ft_free(main);
	return (0);
}
