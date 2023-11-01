#include "philo.h"

static void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->r_forks);
	philo_print(p->philo, M_TAKEFORK);
	pthread_mutex_lock(p->l_forks);
	philo_print(p->philo, M_TAKEFORK);
	p->state = EATING;
	if (p->meal_count)
	{
		p->meal_count--;
		if (!p->meal_count)
			p->state = FINICHED;
	}
	philo_print(p->philo, M_EATING);
	usleep(p->t_eat * 1000);
	pthread_mutex_unlock(p->r_forks);
	pthread_mutex_unlock(p->l_forks);
}

static void	philo_sleep(t_philo *p)
{
	p->state = SLEEPING;
	philo_print(p->philo, M_SLEEPING);
	usleep(p->t_sleep * 1000);
}

static void	philo_think(t_philo *p)
{
	p->state = THINKING;
	philo_print(p->philo, M_THINKING);
}

static void	philo_die(t_philo *p)
{
	p->state = DEAD;
	philo_print(p->philo, M_DIE);
}

void	philo_life_cycle(t_philo *p)
{
	uint64_t	last_meal;
	uint64_t	now;

	last_meal = philo_get_time();
	while (p->state < DEAD)
	{
		philo_eat(p);
		now = philo_get_time();
		if ((int)(now - last_meal) - p->t_eat >= p->t_die)
			philo_die(p);
		last_meal = philo_get_time();
		philo_sleep(p);
		philo_think(p);
	}
}