#include "h_philo.h"

void	end_philo_routine(t_philo *philo)
{
	if (philo->p_status == SLEEP || philo->p_status == THINK)
		return ;
	if (philo->p_status == FORK_B || philo->p_status == EAT)
	{
		pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
		pthread_mutex_unlock(philo->data->fork_tab + philo->r_fork_id);
	}
	else if (philo->p_status == FORK_L)
		pthread_mutex_unlock(philo->data->fork_tab + philo->l_fork_id);
}

void	print_philo_status(t_philo *philo)
{
	long	time;
	int		i;

	i = philo->p_id + 1;
	time = get_time_diff(philo->data->start);
	if (philo->p_status == FORK_L || philo->p_status == FORK_B)
		printf(""GRN"%ld ms "WHT"philo_[%d] has taken a fork\n", time, i);
	else if (philo->p_status == EAT)
		printf(""GRN"%ld ms"WHT" philo_[%d] is eating\n", time, i);
	else if (philo->p_status == SLEEP)
		printf(""GRN"%ld ms"WHT" philo_[%d] is sleeping.\n", time, i);
	else if (philo->p_status == THINK)
		printf(""GRN"%ld ms "WHT"philo_[%d] is thinking\n", time, i);
}

int	print_status(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&(philo->data->print_lock));
	ret = 0;
	if (philo->is_dead == 1 || philo->data->someone_died == 1
		|| (philo->data->meal_goal != -1
			&& philo->p_meal_count >= philo->data->meal_goal))
	{
		end_philo_routine(philo);
		ret = 1;
	}
	else
	{
		print_philo_status(philo);
		ret = 0;
	}
	pthread_mutex_unlock(&(philo->data->print_lock));
	return (ret);
}
