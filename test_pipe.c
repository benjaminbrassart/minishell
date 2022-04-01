/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:53:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/31 20:30:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#pragma region
static void		__stop(char const *fn, char const *file, int line, char const *err);
static void		xpipe(int filedes[2]);
static int		xfork(void);
static void		xclose(int fd);
static int		xdup(int fd) __attribute__((unused));
static int		xdup2(int oldfd, int newfd);
static ssize_t	xread(int fd, void *buf, size_t n);
static ssize_t	xwrite(int fd, void *buf, size_t n);
static pid_t	xwait(int *statloc);
static int		get_status(int rawst);

#define stop() __stop(__FUNCTION__, __FILE__, __LINE__, strerror(errno))
#pragma endregion

#define CHILD_COUNT 1000

int	fds[CHILD_COUNT][2];

static void	exec_child(int i)
{
	int	counter;

	xclose(fds[i][0]);
	if (i != 0)
		xdup2(fds[i - 1][0], STDIN_FILENO);
	xclose(fds[i - 1][0]);
	if (i != CHILD_COUNT - 1)
		xdup2(fds[i][1], STDOUT_FILENO);
	xclose(fds[i][1]);
	fprintf(stderr, "Hi from child %d\n", i);
	if (i == 0)
		counter = 0;
	else
		xread(STDIN_FILENO, &counter, sizeof (counter));
	++counter;
	if (i == CHILD_COUNT - 1)
		printf("Result: %d\n", counter);
	else
		xwrite(STDOUT_FILENO, &counter, sizeof (counter));
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(0);
}

int	main(void)
{
	pid_t	pids[CHILD_COUNT];
	int		i;
	int		pid;
	int		st;
	int		gst;

	i = 0;
	while (i < CHILD_COUNT)
	{
		xpipe(fds[i]);
		pids[i] = xfork();
		if (pids[i] == 0)
			exec_child(i);
		if (i == CHILD_COUNT - 1)
			xclose(fds[i][0]);
		if (i != 0)
			xclose(fds[i - 1][0]);
		xclose(fds[i][1]);
		++i;
	}
	gst = 0;
	i = 0;
	while (i < CHILD_COUNT)
	{
		pid = xwait(&st);
		if (pid == pids[CHILD_COUNT - 1])
			gst = st;
		++i;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (get_status(gst));
}

#pragma region

static void	__stop(char const *fn, char const *file, int line, char const *err)
{
	fprintf(stderr, "Error: %s in %s at %s:%d\n", err, fn, file, line);
	exit(1);
}

static void	xpipe(int filedes[2])
{
	if (pipe(filedes) == -1)
		stop();
}

static int	xfork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		stop();
	return (pid);
}

static void	xclose(int fd)
{
	if (close(fd) == -1)
		stop();
}

static int	xdup(int fd)
{
	int	newfd;

	newfd = dup(fd);
	if (newfd == -1)
		stop();
	return (newfd);
}

static int	xdup2(int oldfd, int newfd)
{
	int	fd;

	fd = dup2(oldfd, newfd);
	if (fd == -1)
		stop();
	return (fd);
}

static ssize_t	xread(int fd, void *buf, size_t n)
{
	int	rd;

	rd = read(fd, buf, n);
	if (rd == -1)
		stop();
	return (rd);
}

static ssize_t	xwrite(int fd, void *buf, size_t n)
{
	int	wr;

	wr = write(fd, buf, n);
	if (wr == -1)
		stop();
	return (wr);
}

static pid_t	xwait(int *statloc)
{
	pid_t	pid;

	pid = wait(statloc);
	if (pid == -1)
		stop();
	return (pid);
}

static int	get_status(int rawst)
{
	if (WIFEXITED(rawst))
		return (WEXITSTATUS(rawst));
	if (WIFSIGNALED(rawst))
		return (WTERMSIG(rawst));
	if (WIFSTOPPED(rawst))
		return (WSTOPSIG(rawst));
	return (rawst);
}

#pragma endregion
