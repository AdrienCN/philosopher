#include "h_philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	//printf(""RED"philo_id = %d waits...\n"WHT"", philo->p_id);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	printf(""GRN"entering routine:"WHT"\n");
	printf("\tphilo_id = %d \n"WHT"", philo->p_id);
	printf("\tl_fork = %d | r_fork = %d\n", philo->l_fork_id, philo->r_fork_id);
	printf("\tphilo_id = %d is leaving \n"WHT"", philo->p_id);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_data			data;
	int				i;
	
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
	i = 0;
	while (i < data.philo_nb)
	{
		printf("before : philo_id = %d\n", data.philo_tab[i].p_id);
		pthread_create(&(data.philo_tab + i)->philo, NULL, &routine, data.philo_tab	+ i);
		//pthread_create(&(data.philo_tab + i)->philo, NULL, &routine, &i);
	//	pthread_create(&(data.philo_tab + i)->philo, NULL, &routine_2, &test);
		i++;
	}
	i = 0;
	while (i < data.philo_nb)
	{
		pthread_join((data.philo_tab + i)->philo, NULL);
		i++;
	}
	printf("test = %d \n", test);
	//faire un pthread_join
	*/ft_free_philo(&data);
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
