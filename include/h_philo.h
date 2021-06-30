/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:29:50 by calao             #+#    #+#             */
/*   Updated: 2021/06/30 15:12:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PHILO_H
# define H_PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

typedef	struct	s_philo
{
	pthread_t	philo;
	int			l_fork;
	int			r_fork;
	int			p_sleep;
	int			p_eat;
	int			p_death;
	int			p_meal;
}				t_philo;


typedef	struct s_data
{
	int				philo_nb;
	int				*fork_tab;
	int				meal_nb;
	int				death;
	int				eat;
	int				sleep;
	struct	timeval	start;
	struct	timeval	now;
	t_philo			*philo_tab;
}				t_data;

#endif
