#include "philo.h"

void		 philo_destroy_mutex(int last)
{
    t_lock *locks;
    int     i;

    locks = philo_get(PHILO_DATA_MTX);
    i = 0;
    while (i < last)
    {
        if (pthread_mutex_destroy(locks + i))
        {
            perror("ERROR!\npthread mutex destroy");
            break;
        }
        i++;
    }
}

void 		philo_release_res() // to review
{
    t_data *philo_data;

    philo_data = philo_get(PHILO_DATA_PTR);
    free(philo_data->tid);
    free(philo_data->locks);
    free(philo_data->philos);
    philo_destroy_mutex(philo_data->params->n_philo + 3);
}

void		philo_err(char const *err_msg) // may not bee necessary
{
	printf("%s\n", err_msg);
}

uint64_t	philo_get_time()
{
	static uint64_t	first_ms;
	uint64_t		now_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (!first_ms)
		first_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	now_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now_ms - first_ms);
}

void		philo_print(t_philo *p, uint64_t c_ms, char const *msg)
{
	t_lock	*print_lock;

	print_lock = (t_lock *)philo_get(PHILO_LOCK_PRT);
	pthread_mutex_lock(print_lock);
	printf("%"PRId64" %d %s\n", c_ms, p->id, msg);
	pthread_mutex_unlock(print_lock);
}