#include "h_philo.h"

void	ft_myusleep(long time_ms)
{
	struct timeval	start;
	long			sleep_ms;
	int i;

	sleep_ms = 0;
	gettimeofday(&start, NULL);
	i = 0;
	while (sleep_ms < time_ms)
	{
		i++;
		usleep(time_ms / 5);
		sleep_ms = get_time_diff(start);
	}
}

void	*monitor_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	while (everyone_is_alive(philo) && everyone_needs_to_eat(philo))
		usleep(100);
	return (NULL);
}

int		everyone_needs_to_eat(t_philo *philo)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	if (philo->data->meal_goal == -1)
		return (1);
	pthread_mutex_lock(&(philo->data->print_lock));
	while (i < philo->data->philo_nb)
	{
		if (philo[i].p_meal_count < philo->data->meal_goal)
			ret = 1;
		if (philo[i].p_meal_count == philo->data->meal_goal 
				&& philo[i].p_belly_print == 0)
		{
			philo[i].p_belly_print = 1;
			printf(""BLE"Philo[%d] finished eating his [%d]meals\n", i + 1, philo[i].p_meal_count);
		}
		i++;
	}
	pthread_mutex_unlock(&(philo->data->print_lock));
	return (ret);
}

void	ft_print_death(t_philo *philo)
{
	long time;

	time = get_time_diff(philo->data->start);
	printf(""GRN"%ld ms "YLW"philo_[%d] is DEAD(from main)\n"WHT"",time, philo->p_id + 1);
	if (philo->p_status == SLEEP || philo->p_status == THINK)
		return;
	if (philo->p_status == FORK_B || philo->p_status == EAT)
	{
		pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
		pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);
	}
	else if (philo->p_status == FORK_L)
		pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
}

int		everyone_is_alive(t_philo *philo)
{
	int i;
	int ret;

	i = 0;
	ret = 1;
	pthread_mutex_lock(&philo->data->status_lock);
	pthread_mutex_lock(&(philo->data->print_lock));
	while (i < philo->data->philo_nb)
	{
		check_for_philo_death(&philo[i]);		
		if (philo[i].is_dead == 1)
		{
			ft_print_death(philo);
			philo->data->someone_died = 1;
			ret = 0;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&(philo->data->print_lock));
	pthread_mutex_unlock(&philo->data->status_lock);
	return (ret);
}
