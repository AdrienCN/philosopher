#include "h_philo.h"

int		parsing_error(char **argv);
int		ft_philo_atoi(char *str);
void	ft_set_data(t_philo *data, char **argv, int argc);

void	print_philo(t_philo *data)
{
	printf("Number of philosophers: %d \n", data->fork_philo_nb);
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
	t_philo	data;

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
	ft_set_data(&data, argv, argc);
	print_philo(&data);
	return (42);
}

void	ft_set_data(t_philo *data, char **argv, int argc)
{
	data->fork_philo_nb = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc ==  6)
		data->meal_nb = ft_atoi(argv[5]);
	else
		data->meal_nb = -1;
}
int		ft_philo_is_digit(char *str)
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
		if (ft_philo_is_digit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}


