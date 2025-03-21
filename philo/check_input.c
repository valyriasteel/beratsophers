/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:36:35 by bbosnak           #+#    #+#             */
/*   Updated: 2023/12/13 20:36:37 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_all_numbers(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
		return (0);
	if (input[i] == '+')
	{
		if (input[i + 1] < '0' || input[i + 1] > '9')
			return (0);
	}
	while (input[i])
	{
		if (input[i] == '\0')
			break ;
		else if ((input[i] >= '0' && input[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

int	philo_atoi(char *s1)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (s1[i] == '+')
		i++;
	while (s1[i] >= '0' && s1[i] <= '9')
	{
		number = number * 10 + s1[i] - 48;
		i++;
	}
	return (number);
}

int	check_inputs(char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		if (is_all_numbers(argv[i]) == 0)
			return (0);
		if (philo_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}
