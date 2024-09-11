/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:59:59 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/14 17:25:22 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs_bonus/pipex_bonus.h"

//	Free the struct
void	ft_free_data(t_DATA *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (data->commands)
	{
		while (data->commands[i])
			ft_freetab(data->commands[i++]);
		free(data->commands);
	}
	if (data->in)
		free(data->in);
	if (data->out >= 0)
		free(data->out);
	if (data->limiter)
		free(data->limiter);
	free(data);
}
