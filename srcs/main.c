/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:48:14 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 12:26:44 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_DATA	*data;
	int		status;

	if (argc > 5 || argc < 5)
		return (ft_puterror("Wrong args"), 0);
	data = ft_parser(argv, env, argc);
	if (!data)
		return (0);
	if (run_commands(data, &status) == 0)
	{
		if (status == 0)
			status = 1;
		return (ft_free_data(data), status);
	}
	ft_free_data(data);
	return (status);
}
