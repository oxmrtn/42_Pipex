/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:21:53 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 14:23:19 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

//	Set the outfile
int	set_outstream(t_DATA *data)
{
	int	fd_out;

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

	if (pipe(fd) == -1)
		return (1);
	fd_in = open(data->in, O_RDONLY);
	close(fd[1]);
	if (fd_in == -1)
	{
		*i = 1;
		perror("Open");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (perror("Dup2"), close(fd[0]), 0);
	}
	else
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("Dup2"), close(fd_in), close(fd[0]), 0);
		close(fd_in);
	}
	close(fd[0]);
	return (1);
}
