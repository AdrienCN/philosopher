#include "h_philo.h"

int		everyone_needs_to_eat(t_philo *philo);
int		everyone_is_alive(t_philo *philo);

void	*routine(void *arg)
{
	t_philo *philo;
		
	philo = (t_philo *)arg;
	if (philo->data->meal_goal == -1)
		philo->p_meal_count = -2;
	else
		philo->p_meal_count = 0;
	while (philo->is_dead == 0 && philo->p_meal_count < philo->data->meal_goal)
	{
		pthread_mutex_lock(philo->data->fork_tab + philo->l_fork_id);
		philo->p_status = FORK_L;
		if (print_status(philo) == -1)
			return (NULL);
		pthread_mutex_lock(philo->data->fork_tab + philo->r_fork_id);
		philo->p_status = FORK_B;
		if (print_status(philo) == -1)
			return (NULL);
		
		gettimeofday(&philo->p_last_meal, NULL);
		if (philo->data->meal_goal != -1)
			philo->p_meal_count++;
		philo->p_status = EAT;
		if (print_status(philo) == -1)
			return (NULL);
		usleep(philo->data->eat * 1000);

		pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
		pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);

		philo->p_status = SLEEP;
		if (print_status(philo) == -1)
			return (NULL);
		usleep(philo->data->sleep * 1000);
		
		philo->p_status = THINK;	
		print_status(philo);
	}
	/*if (philo->p_meal_count == philo->data->meal_goal)
		printf(""BLE"Philo [%d] has full belly and ate [%d] meals\n", philo->p_id, philo->p_meal_count);*/
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	while (everyone_is_alive(philo) && everyone_needs_to_eat(philo))
	{
		usleep(100);
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
	printf(""BLE"Everyone ate well."WHT"\n");
	return (0);
}

int		everyone_is_alive(t_philo *philo)
{
	int i;
	int ret;

	i = 0;
	ret = 1;
	pthread_mutex_lock(&(philo->data->print_lock));
	while (i < philo->data->philo_nb)
	{
		check_for_philo_death(&philo[i]);		
		if (philo[i].is_dead == 1)
		{
			print_time(&philo[i]);
			printf(""YLW"philo_[%d] is DEAD(from main)\n"WHT"", philo[i].p_id + 1);
			if (philo[i].p_status == FORK_B || philo[i].p_status == FORK_L)
				pthread_mutex_unlock(philo->data->fork_tab + philo[i].l_fork_id);
			if (philo[i].p_status == FORK_B)
				pthread_mutex_unlock(philo->data->fork_tab + philo[i].r_fork_id);
			philo->data->someone_died = 1;
			ret = 0;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&(philo->data->print_lock));
	return (ret);
}


int		main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		monitor;
	int				i;
	
	if (argc < 5 || argc > 6)
	{
		printf("Error: arg count = %d: Philo needs 4 or 5 arguments\n", argc);
		return (1);
	}
	if (parsing_error(argv) || ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) > 200)
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
		i+= 2;
	}
	usleep(10);
	i = 1;
	while (i < philo->data->philo_nb)
	{
		pthread_create(&(philo[i].philo), NULL, &routine, philo + i);
		i+= 2;
	}
	pthread_create(&monitor, NULL, &monitor_routine, philo);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
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
