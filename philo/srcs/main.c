/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 15:36:25 by calao             #+#    #+#             */
/*   Updated: 2021/07/12 14:46:41 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "h_philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		monitor;
	int				ret;

	ret = 0;
	if (argc < 5 || argc > 6)
		return (ft_err_msg("Error: Usage: Needs 4 or 5 arguments"));
	if (parsing_error(argv) || ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) > 200)
		return (ft_err_msg("Error: Parsing: argument incorrect value"));
	philo = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (philo == NULL)
		return (ft_err_msg("Error: Malloc: failed"));
	if (ft_set_data(philo, argv, argc) != 0)
	{
		ft_free_philo(philo);
		return (ft_err_msg("Error: Data: Initialisation failed"));
	}
	gettimeofday(&(philo->data->start), NULL);
	ft_launch_threads(philo, &monitor);
	ret = ft_end_threads(philo, &monitor);
	ft_free_philo(philo);
	if (ret == 1)
		printf("Error: Threads: Thread creation or joining failed");
	return (ret);
}

int	ft_err_msg(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_free_philo(t_philo *philo)
{
	if (philo->data->fork_tab)
		free(philo->data->fork_tab);
	if (philo->data)
		free(philo->data);
	if (philo)
		free(philo);
}

int	ft_launch_threads(t_philo *philo, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
	{
		if (pthread_create(&(philo[i].philo), NULL, &routine, philo + i) != 0)
			return (1);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < philo->data->philo_nb)
	{
		if (pthread_create(&(philo[i].philo), NULL, &routine, philo + i) != 0)
			return (1);
		i += 2;
	}
	if (pthread_create(monitor, NULL, &monitor_routine, philo) != 0)
		return (1);
	return (0);
}

int	ft_end_threads(t_philo *philo, pthread_t *monitor)
{
	int	i;

	i = 0;
	i = 0;
	while (i < philo->data->philo_nb)
	{
		if (pthread_join(philo[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(*monitor, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&philo->data->print_lock);
	pthread_mutex_destroy(&philo->data->status_lock);
	while (i < philo->data->philo_nb)
	{
		pthread_mutex_destroy(&philo->data->fork_tab[i]);
		i++;
	}
	return (0);
}
