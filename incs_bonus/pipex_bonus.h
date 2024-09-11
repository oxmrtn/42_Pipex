/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:15 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 14:10:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/incs/ft_printf.h"
# include <sys/wait.h>

typedef struct t_DATA
{
	char	*in;
	char	*out;
	char	**env;
	char	***commands;
	char	*limiter;
}				t_DATA;

t_DATA		*ft_parser(char **args, char **env, int argc);

int			set_outstream(t_DATA *data);
int			buffer_to_input(t_DATA *data);
int			set_instream(t_DATA *data, int *i);
int			execute_commands(t_DATA *data, int i, int islast, int *status);
int			run_commands(t_DATA *data, int *status);

char		**find_path(char **env);
char		**ft_custom_split(char const *s, char c);

void		ft_free_data(t_DATA *data);
void		test_path(t_DATA *data);

#endif