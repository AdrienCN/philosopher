/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:05:52 by calao             #+#    #+#             */
/*   Updated: 2021/07/11 14:15:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"


void	check_for_philo_death(t_philo *philo)
{
	long last_meal_time;

	last_meal_time = get_time_diff(philo->p_last_meal);
	if (last_meal_time > philo->data->death)
	{
		pthread_mutex_lock(&(philo->death_lock));
		philo->is_dead = 1;
		pthread_mutex_unlock(&(philo->death_lock));
	}
}

long	get_time_diff(struct timeval start)
{
	struct timeval  now;
	long			 diff;

	gettimeofday(&now, NULL);
	diff = ((now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000));
	return (diff);
}
/*
void	print_time(t_philo *philo)
{
	long	time;

	time = get_time_diff(philo->data->start);
	printf(""GRN"%ld ms\t"WHT"", time);
}*/

