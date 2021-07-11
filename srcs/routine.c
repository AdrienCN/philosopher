#include "h_philo.h"

int		get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->data->fork_tab + philo->l_fork_id);
	pthread_mutex_lock(&philo->data->status_lock);
	philo->p_status = FORK_L;
	pthread_mutex_unlock(&philo->data->status_lock);
	if (print_status(philo))
		return (1);
	pthread_mutex_lock(philo->data->fork_tab + philo->r_fork_id);
	pthread_mutex_lock(&philo->data->status_lock);
	philo->p_status = FORK_B;
	pthread_mutex_unlock(&philo->data->status_lock);
	if (print_status(philo))
		return (1);
	return (0);
}

int		get_eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	philo->p_status = EAT;
	gettimeofday(&philo->p_last_meal, NULL);
	philo->p_meal_count++;
	pthread_mutex_unlock(&philo->data->print_lock);
	if (print_status(philo))
		return (1);
	ft_myusleep(philo->data->eat);
	pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
	pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);
	pthread_mutex_lock(&philo->data->status_lock);
	philo->p_status = SLEEP;
	pthread_mutex_unlock(&philo->data->status_lock);
	if (print_status(philo))
		return (1);
	ft_myusleep(philo->data->sleep);
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo;
		
	philo = (t_philo *)arg;

	//while (philo->p_meal_count < philo->data->meal_goal || philo->data->meal_goal == -1)
	while ((6 * 7) == 42)
	{
		if (get_forks(philo))
			return (NULL);
		if (get_eat_and_sleep(philo))
			return (NULL);
		pthread_mutex_lock(&philo->data->status_lock);
		philo->p_status = THINK;	
		pthread_mutex_unlock(&philo->data->status_lock);
		if (print_status(philo) == -1)
			return (NULL);
		if (philo->p_meal_count >= philo->data->meal_goal && philo->data->meal_goal != -1)
			break;
	}
	return (NULL);
}
