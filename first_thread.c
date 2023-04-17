/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:44:38 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/15 17:56:57 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//pthread_exitテスト。
void	another_func(int n, const char *func_name)
{
	if (strcmp(func_name, "thread_func") == 0 && n == 2)
	{
		printf("exit. オワ\n");
		pthread_exit(NULL);
		//exit(0);
	}
}

void	repeat_print(int n, const char *func_name)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("Fire %s: %d\n", func_name, i);
		another_func(i, func_name);
		sleep(1);
		i++;
	}
}

// pthread_createの第3引数として渡す。
// voidポインタをreturnし、voidポインタの引数を1つ取る関数でないといけない。
// 引数はpthread_create第4引数から受け取れるが、今回は使わないのでNULLとなっている
void	*thread_func(void *arg)
{
	intptr_t	n;
	const char	*func_name;

	n = (intptr_t)arg;
	func_name = __func__;
	repeat_print(n, func_name);
	//printf("thread_func:n: %ld\n", n);
	return ((void *)n);
}

//thread => pthread_createの第1引数として渡す
//pthread_join 指定したスレッドが終了するまで戻ってこない。第2引数はスレッドの戻り値の格納先になる。
int	main(int argc, char **argv)
{
	const char	*func_name;
	pthread_t	thread;
	intptr_t	n;
	intptr_t	rtn;

	if (argc > 1)
		n = atoi(argv[1]);
	else
		n = 1;
	rtn = 0;
	func_name = __func__;
	if (pthread_create(&thread, NULL, thread_func, (void *)n) != 0)
	{
		printf("Error!スレッド作れなかった");
		exit(1);
	}
	repeat_print(5, func_name);
	if (thread != NULL)
	{
		if (pthread_join(thread, (void **)&rtn) != 0)
		{
			printf("Error!スレッド終了待ちに失敗した");
			exit(1);
		}
		thread = NULL;
	}
	//pthread_join終わり(すなわちpthread_createで呼び出した処理が終了したら)でここに。
	printf("thread_funcがreturnしてpthread_joinの第2引数に格納されたやつ: %ld\n", rtn);
	printf("bye.\n");
	return (0);
}
