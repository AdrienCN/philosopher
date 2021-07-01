#include "h_philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
		
	philo = (t_philo *)arg;
	philo->p_meal_count = 0;
	while (philo->p_is_alive != 0 && philo->p_meal_count < philo->data->meal_goal)
	{
		pthread_mutex_lock(philo->data->fork_tab + philo->l_fork_id);
	//	printf("entering routine:"WHT"\n");
		if (!philo->p_is_alive)
			return (NULL);
		print_time(philo);
		printf("philo_id - %d takes l_fork (%d)\n", philo->p_id, philo->l_fork_id); 
		pthread_mutex_lock(philo->data->fork_tab + philo->r_fork_id);
		
		if (!philo->p_is_alive)
			return (NULL);
		print_time(philo);
		printf("philo_id - %d takes r_fork (%d)\n", philo->p_id, philo->r_fork_id); 
//		philo->p_death = 1;
	
		if (!philo->p_is_alive)
			return (NULL);
		print_time(philo);
		gettimeofday(&philo->p_last_meal, NULL);
		printf("philo_id - %d eats ... \n"WHT"", philo->p_id);
		philo->p_meal_count++;
		usleep(philo->data->eat * 1000);

		pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
		pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);
	
		if (!philo->p_is_alive)
			return (NULL);
		print_time(philo);
		printf("philo_id - %d drops the forks ... & sleeps \n"WHT"", philo->p_id);
		usleep(philo->data->sleep * 1000);
	
		if (!philo->p_is_alive)
			return (NULL);	
		print_time(philo);
		printf(""RED"philo_id = %d wake up & thinks...\n"WHT"", philo->p_id);
	}
	return (NULL);
}

int		everyone_needs_to_eat(t_philo *philo)
{
	int i;

	i = 0;
	if (philo->data->meal_goal == -1)
		return (1);
	while (i < philo->data->philo_nb)
	{
		if (philo[i].p_meal_count< philo->data->meal_goal)
			return (1);
		i++;
	}
	printf(""BLE"Everyone ate well.\n");
	return (0);
}

int		everyone_is_alive(t_philo *philo)
{
	int i;
	int ret;
	long time_since_last_meal;

	i = 0;
	ret = 1;
	while (i < philo->data->philo_nb)
	{
		time_since_last_meal = get_time_diff(philo[i].p_last_meal);
		if (time_since_last_meal >= philo->data->death)
		{
			printf(""MAG"Oh no philo -%d- DIED. Anyways... \n"WHT"", philo[i].p_id);
			philo[i].p_is_alive = 0;
			ret = 0;
		}
		i++;
	}
	return (ret);
}


int		main(int argc, char **argv)
{
	t_philo			*philo;
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
	philo = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (philo == NULL)
		return (1);
	if (ft_set_data(philo, argv, argc) != 0)
		return (-1);
	print_data(philo->data);
	gettimeofday(&(philo->data->start), NULL);
	print_time(philo);
	printf("\n");
	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_create(&(philo[i].philo), NULL, &routine, philo + i);
		//pthread_create(&(data.philo_tab + i)->philo, NULL, &routine, &i);
	//	pthread_create(&(data.philo_tab + i)->philo, NULL, &routine_2, &test);
		i++;
	}

	while (everyone_is_alive(philo) && everyone_needs_to_eat(philo))
	{
		printf(""CYN"tout va bien\n");
		sleep(1);
	}
	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	
	print_time(philo);
	printf("\n");
	ft_free_philo(philo);
	return (42);
}

void	ft_free_philo(t_philo *philo)
{
	if (philo->data->fork_tab)
		free(philo->data->fork_tab);
	if (philo->data)
		free(philo->data);
	//free(philo) ou  for (i < philo_nb) free(philo[i]) ? 

}
