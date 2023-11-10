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

#define PHILOS_PTR	0x0
#define LOCK_PTR	0x1
#define STATE_PTR	0x2
#define PLOCK_PTR	0x4
#define TEAT_PTR	0x8
#define TSLEEP_PTR	0x10
#define TDIE_PTR	0x20
#define NMEALS_PTR	0x40


#define M_TAKEFORK	"has taken a fork"
#define M_EATING	"is eating"
#define M_SLEEPING	"is sleeping"
#define M_THINKING	"is thinking"
#define M_DIE		"die"

typedef struct s_var
{
	int	n_philo;
	int	t_todie;
	int	t_toeat;
	int	t_tosleep;
	int	n_meals;
}		t_var;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	FINICHED
}	t_state;

typedef pthread_mutex_t t_lock;

typedef struct s_philo
{
	int		id;
	t_state	state;
	t_lock	*right;
	t_lock	*left;
	t_lock	*print;
	t_var	*params;
}			t_philo;

int				ft_atoi(const char *);


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