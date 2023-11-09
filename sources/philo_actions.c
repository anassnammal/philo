#include "philo.h"

uint64_t	philo_get_time()
{
	static uint64_t	bef_ms;
	uint64_t		now_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (!bef_ms)
		bef_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	now_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now_ms - bef_ms);
}

void	philo_print(t_lock *p_lock, int i, char const *msg)
{
	uint64_t	current_ms;

	current_ms = philo_get_time();
	pthread_mutex_lock(p_lock);
	printf("%"PRId64" %d %s\n", current_ms, i, msg);
	pthread_mutex_unlock(p_lock);
}

void	*philo_life_cycle(void *ptr)
{
	t_philo		*philo;
	uint64_t	last_meal;

	philo = (t_philo *)ptr;
	last_meal = philo_get_time();
	
	return (NULL);	
}
