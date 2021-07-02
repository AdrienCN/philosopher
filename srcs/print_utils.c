#include "h_philo.h"

void	print_data(t_data *data)
{
	printf("Number of philosophers: %d \n", data->philo_nb);
	printf("Lifetime : %d ms\n", data->death);
	printf("Time to eat : %d ms\n", data->eat);
	printf("Time to sleep : %d ms\n", data->sleep);
	if (data->meal_goal != -1)
		printf("Number of meals : %d| miam miam|\n", data->meal_goal);
	else
		printf("No Meals limits\n");
}

int		print_status(t_philo *philo)
{
		print_time(philo);
		check_for_philo_death(philo);
		if (philo->is_dead == 1 || philo->someone_died == 1)
		{
			if (philo->is_dead == 1)
				printf(""YLW"Philo [%d] is DEAD\n"WHT"", philo->p_id);
			pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
			pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);
			return (-1);
		}
		if (philo->p_status == FORK)
			printf("philo_id -%d- has taken a fork\n", philo->p_id);
		else if (philo->p_status == EAT)
			printf("philo_id - %d eats ... \n"WHT"", philo->p_id);
		else if (philo->p_status == SLEEP)
			printf("philo_id - %d drops the forks ... & sleeps \n"WHT"", philo->p_id);
		else if (philo->p_status == THINK)
			printf(""RED"philo_id = %d wake up & thinks...\n"WHT"", philo->p_id);
		else
			printf(""MAG"WTF are you doing philo -%d- ???\n", philo->p_id);
		return (0);
}

