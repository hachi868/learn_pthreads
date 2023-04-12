/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi <dev@hachi868.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:44:38 by hachi             #+#    #+#             */
/*   Updated: 2023/04/13 02:16:34 by hachi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	repeat_print(int n, const char *func_name)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("Fire %s: %d\n", func_name, i);
		sleep(1);
		i++;
	}
}

// pthread_createの第3引数として渡す。
// voidポインタをreturnし、voidポインタの引数を1つ取る関数でないといけない。
// 引数はpthread_create第4引数から受け取れるが、今回は使わないのでNULLとなっている
void	*thread_func(void *arg)
{
	const char	*func_name;

	(void)arg;
	func_name = __func__;
	repeat_print(3, func_name);
	return (NULL);
}

//thread => pthread_createの第1引数として渡す
int	main(void)
{
	const char	*func_name;
	pthread_t	thread;

	func_name = __func__;
	if (pthread_create(&thread, NULL, thread_func, NULL) != 0)
	{
		printf("Error!スレッド作れなかった");
		exit(1);
	}
	repeat_print(5, func_name);
	return (0);
}
