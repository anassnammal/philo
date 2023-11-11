#include "philo.h"

void	philo_eat(t_philo *philo)
{
	uint64_t	start_eating;

	pthread_mutex_lock(philo->right);
	philo_print(philo, philo_get_time(), M_TAKEFORK);
	pthread_mutex_lock(philo->left);
	philo_print(philo, philo_get_time(), M_TAKEFORK);
	start_eating = philo_get_time();
	philo_print(philo, start_eating, M_EATING);
	while (philo_get_time() - start_eating < philo->params->t_toeat)
		usleep(1000);
	philo->last_meal = philo_get_time();
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	uint64_t	last_meal;

	philo = (t_philo *)ptr;
	last_meal = philo_get_time();
	if (philo->id % 2)
		usleep(100);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	
	return (NULL);	
}
