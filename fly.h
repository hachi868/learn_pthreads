/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:23:07 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/30 03:24:21 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLY_H
# define FLY_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>

# define WIDTH 20
# define HEIGHT 15
# define NUM_FLY 4
# define DRAW_CYCLE 50
# define MIN_SPEED 1.0
# define MAX_SPEED 20.0

typedef struct s_fly
{
	char			mark;
	double			x;
	double			y;
	double			angle;
	double			speed;
	pthread_mutex_t	mutex;
}	t_fly;
#endif //FLY_H
