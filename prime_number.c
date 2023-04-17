/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 02:29:41 by hachi-gbg         #+#    #+#             */
/*   Updated: 2023/04/18 03:08:39 by hachi-gbg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PRIME_NUMBERS 100000

int	g_prime_number[MAX_PRIME_NUMBERS];
int	g_num;

int	is_prime(int m)
{
	int	i;

	i = 0;
	while (i < g_num)
	{
		if (m % g_prime_number[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

//素数判定したらg_prime_numberに格納
int	count_prime_numbers(int n)
{
	int	i;

	g_num = 0;
	i = 2;
	while (i < n)
	{
		if (is_prime(i))
		{
			if (g_num >= MAX_PRIME_NUMBERS)
			{
				printf("Oops, too many prime numbers.\n");
				exit(1);
			}
			g_prime_number[g_num] = i;
			g_num++;
		}
		i++;
	}
	return (g_num);
}

void	*thread_func(void *arg)
{
	int	n;
	int	x;

	n = (intptr_t)arg;
	x = count_prime_numbers(n);
	printf("Number of prime numbers under %d is %d\n", n, x);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread1, NULL, thread_func, (void *)100000);
	pthread_create(&thread2, NULL, thread_func, (void *)200000);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (0);
}