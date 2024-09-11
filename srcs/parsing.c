/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:15:09 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/15 14:03:50 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

t_DATA	*ft_parser(char **args, char **env, int argc)
{
	t_DATA	*data;
	int		i;
	int		j;

	j = 2;
	i = 0;
	data = malloc(sizeof(t_DATA));
	data->commands = NULL;
	if (!data)
		return (NULL);
	data->in = ft_strdup(args[1]);
	data->out = ft_strdup(args[4]);
	if (!data->in || !data->out)
		return (ft_free_data(data), NULL);
	data->env = env;
	data->commands = malloc(sizeof(char **) * (argc - 2));
	if (!data->commands)
		return (ft_free_data(data), NULL);
	while (j < argc - 1)
	{
		data->commands[i] = ft_custom_split(args[j], ' ');
		i++;
		j++;
	}
	return (data->commands[i] = NULL, test_path(data), data);
}

void	test_path(t_DATA *data)
{
	char	**path;
	int		i;
	int		j;
	char	*t;

	i = -1;
	path = find_path(data->env);
	if (!path)
		return ;
	while (path[++i])
	{
		j = 0;
		while (data->commands[j])
		{
			t = ft_strjoin_s1(ft_strjoin(path[i], "/"), data->commands[j][0]);
			if (access(t, X_OK) != -1)
			{
				free(data->commands[j][0]);
				data->commands[j][0] = ft_strdup(t);
			}
			free(t);
			j++;
		}
	}
	ft_freetab(path);
}

char	**find_path(char **env)
{
	int		i;
	char	*buffer;
	char	**result;

	result = NULL;
	buffer = NULL;
	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH=", 5)))
		{
			buffer = ft_strdup(env[i] + 5);
			result = ft_split(buffer, ':');
			return (free(buffer), result);
		}
		i++;
	}
	return (NULL);
}
