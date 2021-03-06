#include "h_philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res);
}

t_data	*ft_setup_data(char **argv, int argc)
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	ft_setup_data_two(data, argv, argc);
	data->fork_tab = malloc(sizeof(pthread_mutex_t) * (data->philo_nb));
	if (data->fork_tab == NULL)
		return (NULL);
	i = -1;
	if (pthread_mutex_init(&(data->print_lock), NULL) != 0
		|| pthread_mutex_init(&(data->status_lock), NULL) != 0)
		return (NULL);
	while (++i < data->philo_nb)
	{
		if (pthread_mutex_init(data->fork_tab + i, NULL) != 0)
			return (NULL);
	}
	return (data);
}

int	ft_set_data(t_philo *philo, char **argv, int argc)
{
	int		i;
	t_data	*data;

	data = ft_setup_data(argv, argc);
	if (data == NULL)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].data = data;
		philo[i].p_belly_print = 0;
		philo[i].p_meal_count = 0;
		philo[i].p_status = 0;
		philo[i].is_dead = 0;
		philo[i].data->someone_died = 0;
		philo[i].p_id = i;
		philo[i].r_fork_id = i;
		gettimeofday(&philo[i].p_last_meal, NULL);
		if (i == 0)
			philo[i].l_fork_id = data->philo_nb - 1;
		else
			philo[i].l_fork_id = i - 1;
		i++;
	}
	return (0);
}

int	ft_data_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parsing_error(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_data_is_digit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
