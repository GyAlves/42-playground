/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:07:30 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/03 21:40:14 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int     current_pipes[2];
    pid_t   child_process;

    if (pipe(current_pipes) == -1)
        return (-1);
    
    child_process = fork();
    if (child_process == -1)
        return (-1);
    
    if (child_process == 0)
    {
        if (type == 'r')
        {
            if (dup2(current_pipes[1], 1) == -1)
                exit(1);
            close(current_pipes[1]);
            close(current_pipes[0]);

            execvp(file, argv);
            exit(-1);
        }
        else if (type == 'w')
        {
            if (dup2(current_pipes[0], 0) == -1)
                exit(-1);
            close(current_pipes[0]);
            close(current_pipes[1]);

            execvp(file, argv);
            exit(-1);
        }
        else
        {
            exit(-1);
        }
    }

    if (type == 'r')
    {
        close(current_pipes[1]);
        return (current_pipes[0]);
    }
    else if (type == 'w')
    {
        close(current_pipes[0]);
        return (current_pipes[1]);
    }
    else
        return (-1);
}