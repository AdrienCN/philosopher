#include "h_philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
		
	philo = (t_philo *)arg;
	printf(""RED"philo_id = %d waits...\n"WHT"", philo->p_id);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
//	philo->p_death = 1;
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
	
	ft_free_philo(&data);
	print_time(&data);
	return (42);
}
/*
void	tmp(void)
{
	data->fork_tab = malloc(sizeof(pthread_mutex_t) * (data->philo_nb));
	data->philo_tab = malloc(sizeof(t_data) * (data->philo_nb));
	if (data->fork_tab == NULL || data->philo_tab == NULL)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(data->fork_tab + i, NULL);
		data->philo_tab[i].p_death = 0;
		data->philo_tab[i].p_id = i;
		//data->philo_tab[i].r_fork = data->fork_tab[i];
		data->philo_tab[i].r_fork_id = i;
		if (i == 0)
		{
		//	data->philo_tab[i].l_fork = data->fork_tab[data->philo_nb - 1];
			data->philo_tab[i].l_fork_id = data->philo_nb - 1;
		}
		else
		{
		//	data->philo_tab[i].l_fork = data->fork_tab[i - 1];
			data->philo_tab[i].l_fork_id = i - 1;
		}
		printf("set data i = %d | p_id = %d\n", i, data->philo_tab[i].p_id);
		i++;
	}
	//printf("\n");
	i = 0;
	while (i < data->philo_nb)
	{
		printf("LEFT_fork = %d <-- philo[ %d ] --> RIGHT_f = %d\n", data->philo_tab[i].l_fork, i, data->philo_tab[i].r_fork);
		i++;
	}
	printf("\n");
}
*/

void	ft_free_philo(t_data *data)
{
	if (data->fork_tab != NULL)
		free(data->fork_tab);
	if (data->philo_tab != NULL)
		free(data->philo_tab);
}
