/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:29:50 by calao             #+#    #+#             */
/*   Updated: 2021/07/11 16:57:41 by calao            ###   ########.fr       */
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
# define YLW "\e[0;33m"
# define BLE "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define EAT	1
# define FORK_L	2
# define FORK_B 3
# define SLEEP	4
# define THINK	5
# define FORK_R 6
typedef	struct s_data
{
	int				philo_nb;
	int				meal_goal;
	int				death;
	int				eat;
	int				sleep;
	int					someone_died;

	pthread_mutex_t		print_lock;
	pthread_mutex_t		status_lock;
	struct	timeval		start;
	pthread_mutex_t		*fork_tab;
}				t_data;

typedef	struct	s_philo
{
	int					l_fork_id;
	int					r_fork_id;
	int					p_sleep;
	int					p_status;
	int					p_eat;
	int					p_id;
	int					p_meal_count;
	int					p_belly_print;
	int					is_dead;
	long				p_last_meal_diff;
	
	pthread_t			philo;
	pthread_mutex_t		death_lock;

	long				p_now;
	struct	timeval		p_last_meal;
	t_data				*data;

}				t_philo;

int		parsing_error(char **argv);
int		ft_data_atoi(char *str);
int		ft_atoi(char *str);
int		ft_set_data(t_philo *philo, char **argv, int argc);
void	ft_free_philo(t_philo *data);
long	get_time_diff(struct timeval start);
void	print_time(t_philo *data);
void	check_for_philo_death(t_philo *philo);
int		print_status(t_philo *philo);
int		everyone_needs_to_eat(t_philo *philo);
int		everyone_is_alive(t_philo *philo);
void	ft_myusleep(long time);
void	*routine(void *arg);
void	*monitor_routine(void *arg);
void	ft_myusleep(long time_ms);
int		everyone_needs_to_eat(t_philo *philo);
void	ft_print_death(t_philo *philo);
int		everyone_is_alive(t_philo *philo);
int		ft_end_threads(t_philo *philo, pthread_t *monitor);
int		ft_launch_threads(t_philo *philo, pthread_t *monitor);
int		ft_err_msg(char *str);

#endif
