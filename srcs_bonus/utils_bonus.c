/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:34:15 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 14:20:17 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs_bonus/pipex_bonus.h"

//	Set the outfile, if a heredoc is specified, the outfile 
//	should append the value.
int	set_outstream(t_DATA *data)
{
	int	fd_out;

	if (data->limiter)
		fd_out = open(data->out, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd_out = open(data->out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out == -1)
		return (perror("Open2"), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (perror("Dup2"), close(fd_out), 0);
	close(fd_out);
	return (1);
}

// Set the infile for the first iteration.
int	set_instream(t_DATA *data, int *i)
{
	int	fd_in;
	int	fd[2];

	if (data->limiter)
		buffer_to_input(data);
	else
	{
		if (pipe(fd) == -1)
			return (perror("Pipe"), 0);
		close(fd[1]);
		fd_in = open(data->in, O_RDONLY);
		if (fd_in == -1)
		{
			*i = 1;
			perror("Open");
			if (dup2(fd[0], STDIN_FILENO) == -1)
				return (perror("Dup2"), close(fd[0]), 0);
		}
		else
			if (dup2(fd_in, STDIN_FILENO) == -1)
				return (perror("Dup2"), close(fd_in), close(fd[0]), 0);
		close(fd_in);
		close(fd[0]);
	}
	return (1);
}
