/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:05:52 by calao             #+#    #+#             */
/*   Updated: 2021/07/12 14:17:24 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "h_philo.h"

void	ft_setup_data_two(t_data *data, char **argv, int argc)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meal_goal = ft_atoi(argv[5]);
	else
		data->meal_goal = -1;
}

void	check_for_philo_death(t_philo *philo)
{
	long	last_meal_time;

	last_meal_time = get_time_diff(philo->p_last_meal);
	if (last_meal_time > philo->data->death)
		philo->is_dead = 1;
}

long	get_time_diff(struct timeval start)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = ((now.tv_sec * 1000 + now.tv_usec / 1000)
			- (start.tv_sec * 1000 + start.tv_usec / 1000));
	return (diff);
}
