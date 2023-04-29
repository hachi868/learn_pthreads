/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:14:37 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/30 03:18:24 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fly.h"

t_fly	g_list_fly[NUM_FLY];
const char	*g_fly_mark_list = "o@*+.#";
int	g_flag_stop_request;//スレッド終了フラグ

//sleep
void	m_sleep(int msec)
{
	struct timespec	ts;

	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

//ランダム値 取得
double	get_rand(double min_val, double max_val)
{
	return (min_val + (double)rand() / ((double)RAND_MAX + 1) * (max_val - min_val));
}

//描画クリア
void	clear_screen(void)
{
	fputs("\033[2J", stdout);
}

//カーソル移動
void	move_cursor(int x, int y)
{
	printf("\033[%d;%dH", y, x);
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

//fly destroy
void	destroy_fly(t_fly *fly)
{
	pthread_mutex_destroy(&fly->mutex);
}

//fly move
void	move_fly(t_fly *fly)
{
	pthread_mutex_lock(&fly->mutex);
	fly->x += cos(fly->angle);
	fly->y += sin(fly->angle);
	if (fly->x < 0)
	{
		fly->x = 0;
		fly->angle = M_PI - fly->angle;
	}
	else if (fly->x >= WIDTH)
	{
		fly->x = WIDTH - 1;
		fly->angle = M_PI - fly->angle;
	}
	if (fly->y < 0)
	{
		fly->y = 0;
		fly->angle *= -1;
	}
	else if (fly->y >= HEIGHT)
	{
		fly->y = HEIGHT - 1;
		fly->angle *= -1;
	}
	pthread_mutex_unlock(&fly->mutex);
}

//fly 座標確認
bool	check_pos_fly(t_fly *fly, int x, int y)
{
	bool	is_pos;

	pthread_mutex_lock(&fly->mutex);
	//printf("%d:%d %d:%d\n", x, (int)fly->x, y, (int)fly->y);
	is_pos = (x == (int)fly->x && y == (int)fly->y);
	pthread_mutex_unlock(&fly->mutex);
	return (is_pos);
}

//fly 動かす
void	*do_move(void *arg)
{
	t_fly	*fly;

	fly = (t_fly *)arg;
	while (!g_flag_stop_request)
	{
		move_fly(fly);
		m_sleep((int)(1000.0 / fly->speed));
	}
	return (NULL);
}

//screen 描画
void	draw_screen(void)
{
	int		x;
	int		y;
	char	ch;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	move_cursor(0, 0);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			ch = 0;
			while (i < NUM_FLY)
			{
				if (check_pos_fly(&g_list_fly[i], x, y))
				{
					ch = g_list_fly[i].mark;
					break ;
				}
				i++;
			}
			i = 0;
			if (ch != 0)
			{
				putchar(ch);
			}
			else if ((y == 0) || (y == HEIGHT - 1))
			{
				putchar('-');
			}
			else if ((x == 0) || (x == WIDTH - 1))
			{
				putchar('|');
			}
			else
			{
				putchar(' ');
			}
			x++;
		}
		putchar('\n');
		x = 0;
		y++;
	}
}

//while screen 描画
void	*repeat_draw_screen(void)
{
	while (!g_flag_stop_request)
	{
		draw_screen();
		m_sleep(DRAW_CYCLE);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	draw_thread;
	pthread_t	move_thread[NUM_FLY];
	int			i;
	char		buf[40];

	i = 0;
	srand((unsigned int)time(NULL));
	clear_screen();
	// fly生成
	while (i < NUM_FLY)
	{
		init_fly(&g_list_fly[i], g_fly_mark_list[i]);
		i++;
	}
	i = 0;
	// fly threadに。
	while (i < NUM_FLY)
	{
		if (pthread_create(&move_thread[i], NULL, do_move, (void *)&g_list_fly[i]) != 0)
		{
			printf("Error!スレッド作れなかった");
			exit(1);
		}
		i++;
	}
	//draw thread
	if (pthread_create(&draw_thread, NULL, (void *)repeat_draw_screen, NULL) != 0)
	{
		printf("Error!スレッド作れなかった");
		exit(1);
	}
	//main thread 入力待ち
	fgets(buf, sizeof(buf), stdin);
	g_flag_stop_request = 1;

	//終了処理
	pthread_join(draw_thread, NULL);
	i = 0;
	while (i < NUM_FLY)
	{
		if (pthread_join(move_thread[i], NULL) != 0)
		{
			printf("Error!スレッド終了待ちに失敗した");
			exit(1);
		}
		destroy_fly(&g_list_fly[i]);
		i++;
	}
	return (0);
}
