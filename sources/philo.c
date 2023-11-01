#include "philo.h"

static uint64_t	philo_get_time()
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) < 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	print(uint64_t i, char const msg)
{
	t_philos *p;

	p = philo(GET_PHILOS_PTR);
	pthread_mutex_lock(&p->print);
	printf("%"PRId64" %"PRId64" %s\n", msg);
	pthread_mutex_unlock(&p->print);
}