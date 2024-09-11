/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:18:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 13:51:48 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

//	Wait in the parent process the die of a children so the program 
//	can continue properly
int	run_parent(int fd[2], int islast, pid_t pid, int *exit_status)
{
	pid_t	endpid;
	int		status;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (perror("Dup2"), close(fd[0]), 0);
	close(fd[0]);
	if (islast)
	{
		while (1 == 1)
		{
			endpid = waitpid(-1, &status, 0);
			if (endpid == pid)
				if (WIFEXITED(status))
					*exit_status = WEXITSTATUS(status);
			if (endpid == -1)
				break ;
		}
	}
	return (1);
}

//	Execute command in a child process. islast is use to define the
//	outfile of the command.
int	run_child(t_DATA *data, int i, int islast, int fd[2])
{
	close(fd[0]);
	if (islast)
	{
		if (set_outstream(data) == 0)
			return (close(fd[1]), 0);
	}
	else if (!islast)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("Dup2"), close(fd[1]), 0);
	}
	close(fd[1]);
	if (execve(data->commands[i][0], data->commands[i], NULL) == -1)
	{
		ft_free_data(data);
		perror("Execve");
		exit(127);
	}
	return (1);
}

//	Execute each command, one command at a time
int	execute_commands(t_DATA *data, int i, int islast, int *status)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("Pipe"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 0);
	else if (pid == 0)
	{
		if (run_child(data, i, islast, fd) == 0)
			return (0);
	}
	else
	{
		if (run_parent(fd, islast, pid, status) == 0)
			return (0);
	}
	return (1);
}

//	Run every commands from the struct data
int	run_commands(t_DATA *data, int *status)
{
	int	i;

	i = 0;
	set_instream(data, &i);
	while (data->commands[i + 1])
	{
		if (execute_commands(data, i, 0, status) == 0)
			return (0);
		i++;
	}
	if (execute_commands(data, i, 1, status) == 0)
		return (0);
	return (1);
}
