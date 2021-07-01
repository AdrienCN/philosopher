#include "h_philo.h"

int		ft_atoi(char *str)
{
	int i;
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

void	get_time(t_philo *philo)
{
	gettimeofday(&philo->p_end, NULL);
	philo->p_now = ((philo->p_end.tv_sec * 1000 + philo->p_end.tv_usec) - (philo->data->start.tv_sec * 1000 + philo->data->start.tv_usec));	
}

int		ft_set_data(t_philo *philo, char **argv, int argc)
{
	int i;
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->philo_nb = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc ==  6)
		data->meal_nb = ft_atoi(argv[5]);
	else
		data->meal_nb = -1;
	data->fork_tab = malloc(sizeof(pthread_mutex_t) * (data->philo_nb));
	if (data->fork_tab == NULL)
		return (1);
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(data->fork_tab + i, NULL);

	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].data = data;
		philo[i].p_death = 0;
		philo[i].p_is_alive = 1;
		philo[i].p_id = i;
		philo[i].r_fork = data->fork_tab[i];
		philo[i].r_fork_id = i;
		if (i == 0)
		{
			philo[i].l_fork = data->fork_tab[data->philo_nb - 1];
			philo[i].l_fork_id = data->philo_nb - 1;
		}
		else
		{
			philo[i].l_fork = data->fork_tab[i - 1];
			philo[i].l_fork_id = i - 1;
		}
		printf("set data i = %d | p_id = %d\n", i, philo[i].p_id);
		i++;
	}
	/*i = 0;
	while (i < data->philo_nb)
	{
		printf("LEFT_fork = %d <-- philo[ %d ] --> RIGHT_f = %d\n", data->philo_tab[i].l_fork, i, data->philo_tab[i].r_fork);
		i++;
	}
	printf("\n");
*/
	return (0);
}

int		ft_data_is_digit(char *str)
{
	int i;
	
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

int		parsing_error(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_data_is_digit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
