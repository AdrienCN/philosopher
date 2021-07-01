#include "h_philo.h"

void	print_data(t_data *data)
{
	printf("Number of philosophers: %d \n", data->philo_nb);
	printf("Lifetime : %d ms\n", data->death);
	printf("Time to eat : %d ms\n", data->eat);
	printf("Time to sleep : %d ms\n", data->sleep);
	if (data->meal_nb != -1)
		printf("Number of meals : %d| miam miam|\n", data->meal_nb);
}
