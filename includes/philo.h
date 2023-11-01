#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <pthread.h>
#include <sys/time.h>

#define GET_PHILOS_PTR	0x0
#define LAUNCH_PHILOS	0x1
#define DESTROY_FORKS	0x2
#define	DETACH_PHILOS	0x4
#define JOIN_PHILOS		0x8
#define DESTROY_PRINT	0x10
#define RELEASE_MEMORY	0x20
#define CLEAR_STCVAR	0x40

#define CLEAR_ALL_MEM	0x60
#define RELEASE_ALL		0x72

#define M_TAKEFORK	"has taken a fork"
#define M_EATING	"is eating"
#define M_SLEEPING	"is sleeping"
#define M_THINKING	"is thinking"
#define M_DIE		"die"

typedef struct s_var
{
	int	n_philo;
	int	n_meals;
	int	t_todie;
	int	t_toeat;
	int	t_tosleep;
}		t_var;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	FINICHED
}	t_state;

typedef struct s_philos
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_var			*params;
}					t_philos;

typedef struct s_philo
{
	int				philo;
	pthread_mutex_t	*r_forks;
	pthread_mutex_t	*l_forks;
	t_state			state;
	int				meal_count;
	int				t_eat;
	int				t_sleep;
	int				t_die;
}					t_philo;

t_philos	*philo(uint8_t operation);
void		*philo_routine(void *index);
void		philo_life_cycle(t_philo *p);
// parse utils
int			ft_atoi(const char *str);
uint64_t	philo_get_time();
void		philo_print(int i, char const *msg);
void		philo_destroy_mutex(uint64_t last);



#endif

/*
	memset, printf, malloc, free, write,
	usleep, gettimeofday, pthread_create,
	pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock,
	pthread_mutex_unlock


	F4 P0 F0
	F1 P2 F2

	F0 P1 F1
	F2 P3 F3

	F1 P2 F2
	F3 P4 F4

	F2 P3 F3
	F4 P0 F0

	F3 P4 F4
	F0 P1 F1
*/