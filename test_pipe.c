/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:53:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/29 22:35:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CHILD_COUNT 40
#define stop() __stop(__FUNCTION__, __FILE__, __LINE__, strerror(errno))

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

typedef struct s_cmd	t_cmd;

int	fds[CHILD_COUNT][2];

static void	__stop(char const *fn, char const *file, int line, char const *error)
{
	fprintf(stderr, "Error: %s in %s at %s:%d\n", error, fn, file, line);
	exit(1);
}

// ls | cat | cat

static void	exec_child(int n)
{
	int	counter;

	counter = 0;
	if (n != 0)
		close(fds[n - 1][1]);
	if (n != 0 && dup2(fds[n - 1][0], STDIN_FILENO) < 0)
		stop();
	close(fds[n - 1][0]);
	if (n != CHILD_COUNT - 1 && dup2(fds[n][1], STDOUT_FILENO) < 0)
		stop();
	close(fds[n][1]);
	if (n == 0)
		counter = 0;
	else if (read(STDIN_FILENO, &counter, sizeof (counter)) < 0)
		stop();
	// if (n == 1000)
	// 	sleep(5);
	++counter;
	if (n == CHILD_COUNT - 1)
		printf("Result: %d\n", counter);
	else if (write(STDOUT_FILENO, &counter, sizeof (counter)) < 0)
		stop();
	fprintf(stderr, "child %d\n", n);
	exit(0);
}

int	main(void)
{
	pid_t	pids[CHILD_COUNT];
	pid_t	pid;
	int		n;
	int		m;
	int		child_st;
	int		global_st;

	n = 0;
	while (n < CHILD_COUNT)
	{
		if (pipe(fds[n]) == -1)
			stop();
		if (n == 0)
			close(fds[n][0]);
		if (n == CHILD_COUNT - 1)
			close(fds[n][1]);
		pids[n] = fork();
		if (pids[n] == -1)
		{
			perror(NULL);
			break ;
		}
		if (pids[n] == 0)
			exec_child(n);
		if (n != 0)
			close(fds[n - 1][1]);
		++n;
	}
	m = 0;
	while (m < n)
	{
		printf("Waiting child %d\n", m);
		pid = waitpid(pids[m], &child_st, 0);
		if (pid == -1)
			stop();
		if (m == CHILD_COUNT - 1)
			global_st = child_st;
		++m;
	}
	return (global_st);
}

struct s_cmd
{
	int		fds[2];
	t_cmd	*next;
};
