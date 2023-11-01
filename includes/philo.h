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

typedef struct s_var
{
	uint64_t	n_philo;
	uint64_t	n_meals;
	uint64_t	t_todie;
	uint64_t	t_toeat;
	uint64_t	t_tosleep;
}				t_var;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING
}	t_state;

typedef struct s_philo
{
	pthread_mutex_t	*r_forks;
	pthread_mutex_t	*l_forks;
	t_state			state;
	uint64_t		meal_count;
}					t_philo;

typedef struct s_philos
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_var			*params;
}					t_philos;


t_philos	*philo(uint8_t operation);
// parse utils
int	ft_atoi(const char *str);



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