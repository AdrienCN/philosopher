/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:29:50 by calao             #+#    #+#             */
/*   Updated: 2021/07/01 13:47:01 by calao            ###   ########.fr       */
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
	pthread_t			philo;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		r_fork;
	int					l_fork_id;
	int					r_fork_id;
	int					p_sleep;
	int					p_eat;
	int					p_death;
	int					p_meal;
	int					p_id;
}				t_philo;


typedef	struct s_data
{
	int				philo_nb;
	int				meal_nb;
	int				death;
	int				eat;
	int				sleep;
	struct	timeval	start;
	struct	timeval	end;
	long			now;
	pthread_mutex_t				*fork_tab;
	t_philo			*philo_tab;
}				t_data;

int		parsing_error(char **argv);
int		ft_data_atoi(char *str);
int		ft_set_data(t_data *data, char **argv, int argc);
void	ft_free_philo(t_data *data);
void	get_time(t_data *data);
void	print_time(t_data *data);
void	print_data(t_data *data);
#endif
