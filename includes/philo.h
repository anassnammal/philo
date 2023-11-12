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

#define PHILO_DATA_PTR 0x0
#define PHILO_DATA_TID 0x1
#define PHILO_DATA_MTX 0x2
#define PHILO_DATA_PRM 0x4
#define PHILO_DATA_PHL 0x8
#define PHILO_LOCK_PRT 0x10
#define PHILO_LOCK_LML 0x20
#define PHILO_LOCK_MCT 0x40

#define M_TAKEFORK	"has taken a fork"
#define M_EATING	"is eating"
#define M_SLEEPING	"is sleeping"
#define M_THINKING	"is thinking"
#define M_DIE		"die"

typedef pthread_mutex_t	t_lock;

typedef struct s_var
{
	int	n_philo;
	int	t_todie;
	int	t_toeat;
	int	t_tosleep;
	int	n_meals;
}		t_var;

typedef struct s_philo
{
	int			id;
	int			count_meal;
	uint64_t	last_meal;
	t_lock		*right;
	t_lock		*left;
	t_var		*params;
}			t_philo;

typedef struct s_data
{
	pthread_t	*tid;
	t_lock		*locks;
	t_philo		*philos;
	t_var		*params;
}	t_data;

int			ft_atoi(const char *);
void		*philo_get(uint8_t);
bool 		philo_init(t_var *);
void		philo_destroy_mutex(int);
void		philo_release_res();
void		philo_err(char const *);
uint64_t	philo_get_time();
void		philo_print(t_philo *, uint64_t, char const *);
void		*philo_routine(void *ptr);
#endif

/*
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