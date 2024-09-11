/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:48:14 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 12:16:19 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs_bonus/pipex_bonus.h"

//	Program's main.
int	main(int argc, char **argv, char **env)
{
	t_DATA	*data;
	int		status;

	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 6)
			return (ft_puterror("Wrong args"), 0);
	}
	else
	{
		if (argc < 5)
			return (ft_puterror("Wrongs args"), 0);
	}
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
