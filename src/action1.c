/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizsak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 08:17:36 by aizsak            #+#    #+#             */
/*   Updated: 2023/02/12 08:18:32 by aizsak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lock_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(\
		&philo->data_ptr->fork[philo->data_ptr->nb_philo - 1]);
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
		ft_write(philo, LOCK_FORK);
		ft_write(philo, LOCK_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 2]);
		ft_write(philo, LOCK_FORK);
		ft_write(philo, LOCK_FORK);
	}
}

void	ft_unlock_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_unlock(\
		&philo->data_ptr->fork[philo->data_ptr->nb_philo - 1]);
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 2]);
	}
}

void	ft_death(t_data *data, t_philo *philo)
{
	int	i;

	while (!ft_check_die(philo))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&philo->data_ptr->check_last_eat);
			if ((ft_get_time() - data->time - philo[i].last_eat) >= data->ttd)
			{
				pthread_mutex_unlock(&philo->data_ptr->check_last_eat);
				pthread_mutex_lock(&philo->data_ptr->check_die);
				data->die = philo->id;
				pthread_mutex_unlock(&philo->data_ptr->check_die);
				ft_write(philo + i, DIE);
				return ;
			}
			else
				pthread_mutex_unlock(&philo->data_ptr->check_last_eat);
			i++;
		}
	}
}
