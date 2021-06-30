#include "h_philo.h"

int		main(int argc, char **argv)
{
	t_data			data;
	
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
	print_time(&data);
	print_data(&data);
	ft_free_philo(&data);
	print_time(&data);
	return (42);
}

void	ft_free_philo(t_data *data)
{
	if (data->fork_tab != NULL)
		free(data->fork_tab);
	if (data->philo_tab != NULL)
		free(data->philo_tab);
}
