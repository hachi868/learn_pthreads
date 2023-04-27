/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:14:37 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/28 03:37:51 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fly.h"

t_fly	g_list_fly[NUM_FLY];
const char	*g_fly_mark_list = "o@*+.#";
int	g_flag_stop_request;//スレッド終了フラグ

//sleep
void	m_sleep(int msec)
{

}

//ランダム値 取得
double	get_rand(double min_val, doubel max_val)
{

}

//描画クリア
void	clear_screen(void)
{

}

//カーソル移動
void	move_cursor(int x, int y)
{

}

//fly init ランダム
void	init_fly(t_fly *fly, char mark_fly)
{
	fly->mark = mark_fly;
	fly->x = get_rand(0, (double)(WIDTH - 1));
	fly->y = get_rand(0, (double)(HEIGHT - 1));
	fly->angle = get_rand(0, M_2_PI);
	fly->speed = get_rand(MIN_SPEED, MAX_SPEED);
	pthread_mutex_init(&fly->mutex, NULL);//直に構造体の中身にinit
}

void	destroy_fly(t_fly *fly)
{
	pthread_mutex_destroy(&fly->mutex);
}


