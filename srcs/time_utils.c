/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:05:52 by calao             #+#    #+#             */
/*   Updated: 2021/07/01 19:17:28 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

void	get_time(t_philo *philo)
{
	gettimeofday(&philo->p_end, NULL);
	philo->p_now = ((philo->p_end.tv_sec * 1000 + philo->p_end.tv_usec / 1000) - (philo->data->start.tv_sec * 1000 + philo->data->start.tv_usec / 1000));
//	memset(&philo->p_end, 0, sizeof(philo->p_end));
}

void	print_time(t_philo *philo)
{
	get_time(philo);
	printf(""GRN"%ld ms\t"WHT"", philo->p_now);
}

