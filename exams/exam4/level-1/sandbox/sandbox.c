/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:58:51 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/10/21 00:16:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid;
	pid_t	wait_result;
    int		status;
	int		exit_code;

	if (f == NULL)
		return (-1);

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		f();
		exit(0);
	}

	alarm(timeout);
	wait_result = waitpid(pid, &status, 0);
	alarm(0);

	if (wait_result == -1)
	{
		if (errno == EINTR)
		{
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			return (0);
		}
		return (-1);
	}

	if (WIFSIGNALED(status))
	{
		if (verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		return (0);
	}

	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		else
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", exit_code);
			return (0);
		}
	}

	if (WIFSTOPPED(status))
	{
		kill(pid, SIGKILL);
		waitpid(pid, NULL, 0);
		if (verbose)
			printf("Bad function: %s\n", strsignal(WSTOPSIG(status)));
		return (0);
	}

	return (0);
}