/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:06:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/03 21:48:19 by gyasminalve      ###   ########.fr       */
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
	int		prev_pipe;
	int		counter;
	int		cmds_count;
	int		current_pipes[2];
	pid_t	child_process;

	prev_pipe = -1;
	counter = 0;
	cmds_count = get_cmds_count(cmds);

	while (counter < cmds_count)
	{
		if (counter < (cmds_count - 1))
		{
			if (pipe(current_pipes) == -1)
				return (1);
		}

		child_process = fork();
		if (child_process == -1)
			return (1);
		
		if (child_process == 0)
		{
			if (counter > 0)
			{
				if (dup2(prev_pipe, STDIN_FILENO) == -1)
					exit(1);
				close(prev_pipe);
			}

			if (counter < (cmds_count - 1))
			{
				if (dup2(current_pipes[1], STDOUT_FILENO) ==)
					exit(1);
				close(current_pipes[1]);
				close(current_pipes[0]);
			}
			execvp(cmds[counter][0], cmds[counter]);
			exit(1);
		}

		if (prev_pipe != -1)
			close(prev_pipe);
		if (counter < (cmds_count - 1))
		{
			close(current_pipes[1]);
			prev_pipe = current_pipes[0]
		}

		counter++;
	}
	
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}
