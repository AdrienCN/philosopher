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
	long	time;

	pthread_mutex_lock(&(philo->data->print_lock));
	//check_for_philo_death(philo);
	time = get_time_diff(philo->data->start);
	if (philo->is_dead == 1 || philo->data->someone_died == 1 || philo->p_meal_count
				== philo->data->meal_goal)
	{
		if (philo->p_meal_count == philo->data->meal_goal)
		{
			printf(""GRN"%ld ms "YLW"philo_[%d] has finished eating\n"WHT"", time, philo->p_id);
		}
		if (philo->p_status == FORK_B || 
				philo->p_status == FORK_L || philo->p_status == EAT)
			pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
		if (philo->p_status == FORK_B || philo->p_status == EAT)
			pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);
		pthread_mutex_unlock(&(philo->data->print_lock));
		return (-1);
	}
	if (philo->p_status == FORK_L)
		printf(""GRN"%ld ms "WHT"philo_[%d] has taken LEFT fork\n", time, philo->p_id + 1);
	else if (philo->p_status == FORK_R)
		printf(""GRN"%ld ms "WHT"philo_[%d] has taken RIGHT fork\n", time, philo->p_id + 1);
	else if  (philo->p_status == FORK_B)
		printf(""GRN"%ld ms "WHT"philo_[%d] has taken a SECOND fork\n", time, philo->p_id + 1 );
	else if (philo->p_status == EAT)
		printf(""GRN"%ld ms"WHT" philo_[%d] eats.\n"WHT"", time, philo->p_id + 1);
	else if (philo->p_status == SLEEP)
		printf(""GRN"%ld ms"WHT" philo_[%d] sleeps.\n"WHT"", time, philo->p_id + 1);
	else if (philo->p_status == THINK)
		printf(""GRN"%ld ms "RED"philo[%d] thinks.\n"WHT"", time, philo->p_id + 1);
	else
		printf(""MAG"WTF are you doing philo -%d- ???\n", philo->p_id + 1);
	pthread_mutex_unlock(&(philo->data->print_lock));
	return (0);
}

