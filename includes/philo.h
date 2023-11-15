/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:22:56 by anammal           #+#    #+#             */
/*   Updated: 2023/11/15 08:22:58 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <inttypes.h>
# include <sys/time.h>

#define M_TAKEFORK	"has taken a fork"
#define M_EATING	"is eating"
#define M_SLEEPING	"is sleeping"
#define M_THINKING	"is thinking"
#define M_DIE		"die"

typedef	pthread_mutex_t t_mutex;

typedef	struct s_var
{
	uint64_t	n_philo;
	uint64_t	t_die;
	uint64_t	t_eat;
	uint64_t	t_sleep;
	uint64_t	n_meals;
}	t_var;

typedef struct s_philo
{
	uint64_t	id;
	uint64_t	last_meal;
	bool		state;
	t_mutex		*right_l;
	t_mutex		*left_l;
	t_mutex		*state_l;
	t_mutex		*print_l;
}	t_philo;
void		philo_simulation(t_philo *p, pthread_t *t, t_mutex *l, uint64_t n);
t_var		*philo_get_params();
void		*philo_routine(void *ptr);
void		philo_monitor(t_philo *p);
uint64_t	philo_atoui64(const char *str);
uint64_t	philo_get_time();
void		philo_update_state(t_philo	*p, bool new);
bool		philo_state(t_philo *p);
void		philo_print(t_philo	*p, uint64_t t_ms, char *msg);

#endif
