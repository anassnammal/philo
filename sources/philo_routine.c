#include "philo.h"

void	philo_take_forks(t_philo *p)
{
	if (!philo_state(p))
		return ;
	pthread_mutex_lock(p->right_l);
	if (!philo_state(p))
		return ;
	philo_print(p, philo_get_time(), M_TAKEFORK);
	pthread_mutex_lock(p->left_l);
	if (!philo_state(p))
		return ;
	philo_print(p, philo_get_time(), M_TAKEFORK);
	pthread_mutex_lock(p->state_l);
	p->last_meal = philo_get_time();
	pthread_mutex_unlock(p->state_l);
}

void	philo_act(t_philo *p, uint64_t ms, char *msg)
{
	uint64_t	now;

	now = philo_get_time();
	if (!philo_state(p))
		return ;
	philo_print(p, now, msg);
	while (philo_get_time() - now <= ms)
	{
		usleep(1000);
		if (!philo_state(p))
			break ;
	}
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	t_var		*params;
	uint64_t	meal_count;

	philo = (t_philo *)ptr;
	params = philo_get_params();
	meal_count = params->n_meals;
	while (philo_state(philo))
	{
		philo_take_forks(philo);
		philo_act(philo, params->t_eat, M_EATING);
		pthread_mutex_unlock(philo->right_l);
		pthread_mutex_unlock(philo->left_l);
		if (meal_count)
		{
			meal_count--;
			if (!meal_count)
				philo_update_state(philo, false);
		}
		philo_act(philo, params->t_sleep, M_SLEEPING);
		philo_act(philo, 1, M_THINKING);
	}
	return (NULL);
}