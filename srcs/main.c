#include "h_philo.h"

int		parsing_error(char **argv);
int		ft_philo_atoi(char *str);

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
	ft_set_data(&data, argv);
	return (42);
}

void	ft_set_data(t_philo *data, char **argv)
{
	data->fork_philo_nb = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argv[5] != '\0')
		data->meal_nb = ft_atoi[5];
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


