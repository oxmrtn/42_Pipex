/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:24:51 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 14:35:24 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs_bonus/pipex_bonus.h"

//	This func get the input of the user if a here_doc is detected.
char	*get_input(t_DATA *data)
{
	char	*buffer;
	char	*line;

	buffer = NULL;
	ft_printf("pipe heredoc> ");
	line = get_next_line(1);
	if (!line)
		return (NULL);
	while (ft_strncmp(data->limiter, line, ft_strlen(line) - 1))
	{
		ft_printf("pipe heredoc> ");
		buffer = ft_strjoin_s1(buffer, line);
		free(line);
		line = get_next_line(1);
	}
	if (line)
		free(line);
	return (buffer);
}

//	Fill a fd with the user input and set the infill of the 
//	first function to this fd
int	buffer_to_input(t_DATA *data)
{
	int		fd[2];
	char	*input;	

	if (pipe(fd) == -1)
		return (perror("Pipe"), 0);
	input = get_input(data);
	write(fd[1], input, ft_strlen(input));
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (perror("Dup2"), close(fd[0]), free(input), 0);
	close(fd[0]);
	free(input);
	return (1);
}
