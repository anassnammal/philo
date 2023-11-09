#include "philo.h"



// void		philo_print(int i, char const *msg)
// {
// 	pthread_mutex_t 	*print_lock;
// 	uint64_t			current_ms;

// 	current_ms = philo_get_time();
// 	print_lock = (pthread_mutex_t *)philo_get(GET_LOCKS_PTR);
// 	pthread_mutex_lock(print_lock);
// 	printf("%"PRId64" %d %s\n", current_ms, i, msg);
// 	pthread_mutex_unlock(print_lock);
// }

// void		philo_destroy_mutex(uint64_t last)
// {
// 	t_philo_vars	*philos;
// 	uint64_t		i;

// 	philos = philo_get(GET_PHILOS_PTR);
// 	i = 0;
// 	while (i < last)
// 	{
// 		if (pthread_mutex_destroy(philos->locks + i))
// 		{
// 			perror("ERROR!\npthread mutex destroy");
// 			break ;
// 		}
// 		i++;
// 	}
// }

// bool		philo_launch_threads()
// {
// 	t_philo_vars	*p;
// 	int				i;

// 	p = philo_get(PHILOS_PTR);
// 	i = 0;
// 	while (i < p->params->n_philo)
// 	{
// 		p->philos[i] = i + 1;
// 		if (pthread_mutex_init(p->locks + i, NULL))
// 			return (perror("ERROR!\npthread mutex init"), false);
// 		if (pthread_create(p->thread_id + i, NULL, philo_life_cycle, *(p + i)->philos))
// 			return (perror("ERROR!\npthread create"), false);
// 		if (pthread_detach(*(p->thread_id + i)))
// 			return (perror("ERROR!\npthread detach"), false);

// 		i++;
// 	}
// 	return (true);
// }


