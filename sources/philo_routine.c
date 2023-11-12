#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	philo_print(philo, philo_get_time(), M_TAKEFORK);
	pthread_mutex_lock(philo->left);
	philo_print(philo, philo_get_time(), M_TAKEFORK);
	philo_print(philo, philo_get_time(), M_EATING);
	pthread_mutex_lock(philo_get(PHILO_LOCK_LML));
	philo->last_meal = philo_get_time();
	pthread_mutex_unlock(philo_get(PHILO_LOCK_LML));
	usleep(philo->params->t_toeat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

static void	philo_sleep(t_philo *philo)
{
	philo_print(philo, philo_get_time(), M_SLEEPING);
	usleep(philo->params->t_tosleep * 1000);
}

static void	philo_think(t_philo *philo)
{
	philo_print(philo, philo_get_time(), M_THINKING);
	usleep(100);
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo_get(PHILO_LOCK_LML));
	philo->last_meal = philo_get_time();
	pthread_mutex_unlock(philo_get(PHILO_LOCK_LML));
	if (!(philo->id % 2))
		usleep(100);
	while (true)
	{
		philo_eat(philo);
		if (philo->params->n_meals)
		{
			pthread_mutex_lock(philo_get(PHILO_LOCK_MCT));
			philo->count_meal++;
			if (philo->count_meal == philo->params->n_meals)
			{
				pthread_mutex_unlock(philo_get(PHILO_LOCK_MCT));
				break ;
			}
			pthread_mutex_unlock(philo_get(PHILO_LOCK_MCT));
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);	
}
