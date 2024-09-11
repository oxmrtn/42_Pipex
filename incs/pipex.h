/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:15 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 13:32:14 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/incs/ft_printf.h"
# include <sys/wait.h>

typedef struct t_DATA
{
	char	*in;
	char	*out;
	char	**env;
	char	***commands;
}				t_DATA;

t_DATA		*ft_parser(char **args, char **env, int argc);
int			run_commands(t_DATA *data, int *status);
int			execute_commands(t_DATA *data, int i, int islast, int *status);
int			run_child(t_DATA *data, int i, int islast, int fd[2]);
int			run_parent(int fd[2], int islast, pid_t pid, int *exit_status);
int			set_outstream(t_DATA *data);
int			set_instream(t_DATA *data, int *i);

char		**find_path(char **env);
char		**ft_custom_split(char const *s, char c);

void		ft_free_data(t_DATA *data);
void		test_path(t_DATA *data);

#endif