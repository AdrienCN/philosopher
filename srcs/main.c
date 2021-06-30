#include "h_philo.h"

int		parsing_error(char **argv);
int		ft_data_atoi(char *str);
int		ft_set_data(t_data *data, char **argv, int argc);
void	ft_free_philo(t_data *data);

void	print_data(t_data *data)
{
	printf("Number of philosophers: %d \n", data->philo_nb);
	printf("Lifetime : %d ms\n", data->death);
	printf("Time to eat : %d ms\n", data->eat);
	printf("Time to sleep : %d ms\n", data->sleep);
	if (data->meal_nb != -1)
		printf("Number of meals : %d| miam miam|\n", data->meal_nb);
}

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

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: arg count = %d: Philo needs 4 or 5 arguments\n", argc);
		return (1);
	}
	if (parsing_error(argv))
	{
		printf("Error: parsing: wrong args\n");
		return (1);
	}
	if (ft_set_data(&data, argv, argc) != 0)
		return (-1);
	print_data(&data);
	ft_free_philo(&data);
	return (42);
}

void	ft_free_philo(t_data *data)
{
	if (data->fork_tab != NULL)
		free(data->fork_tab);
	if (data->philo_tab != NULL)
		free(data->philo_tab);
}

int		ft_set_data(t_data *data, char **argv, int argc)
{
	int i;
	
	data->philo_nb = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc ==  6)
		data->meal_nb = ft_atoi(argv[5]);
	else
		data->meal_nb = -1;
	data->fork_tab = malloc(sizeof(int) * (data->philo_nb));
	data->philo_tab = malloc(sizeof(t_data) * (data->philo_nb));
	if (data->fork_tab == NULL || data->philo_tab == NULL)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		data->fork_tab[i] = i;
		data->philo_tab[i].r_fork = i;
		if (i == 0)
			data->philo_tab[i].l_fork = data->philo_nb - 1;
		else
			data->philo_tab[i].l_fork = i - 1;
		printf("fork_tab[%d] = %d; ", i, data->fork_tab[i]);
		i++;
	}
	printf("\n");
	/*
	i = 0;
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
