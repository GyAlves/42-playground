/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:06:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/01 20:49:28 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	get_cmds_count(char **cmds[])
{
	int	count;

	count = 0;
	while (cmds[count] != NULL)
		count++;
	return (count);
}

int	picoshell(char **cmds[])
{
	int		counter;
	int		prev_pipe;
	int		current_pipe[2];
	int		cmds_count;
	pid_t	child_pid;

	counter = 0;
	prev_pipe = -1;
	cmds_count = get_cmds_count(cmds);
	while (counter < cmds_count)
	{
		if (counter < (cmds_count - 1))
		{
			if (pipe(current_pipe) == -1)
				return (1);
		}
		child_pid = fork();
		if (child_pid == -1)
			return (1);
		if (child_pid == 0)
		{
			if (counter > 0)
			{
				if (dup2(prev_pipe, STDIN_FILENO) == -1)
					exit(1);
				close(prev_pipe);
			}
			if (counter < (cmds_count - 1))
			{
				if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
					exit(1);
				close(current_pipe[1]);
				close(current_pipe[0]);
			}
			execvp(cmds[counter][0], cmds[counter]);
			exit(1);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (counter < (cmds_count - 1))
		{
			close(current_pipe[1]);
			prev_pipe = current_pipe[0];
		}
		counter++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}
