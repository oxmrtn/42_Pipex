/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:15:09 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/14 17:25:46 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs_bonus/pipex_bonus.h"

//	Second part of parsing, handle the here_doc case and set limiter
int	parsing_bis(char **args, t_DATA *data, int argc, int *j)
{
	if (!ft_strncmp(args[1], "here_doc", ft_strlen(args[1])))
	{
		data->limiter = ft_strdup(args[2]);
		data->in = NULL;
		*j = 3;
	}
	else
	{
		data->in = ft_strdup(args[1]);
		data->limiter = NULL;
		*j = 2;
	}
	data->out = ft_strdup(args[argc - 1]);
	if (!data->out)
		return (ft_free_data(data), 0);
	return (1);
}

//	Parse the input and put it in the struc data
t_DATA	*ft_parser(char **args, char **env, int argc)
{
	t_DATA	*data;
	int		i;
	int		j;

	i = 0;
	data = malloc(sizeof(t_DATA));
	if (!data)
		return (NULL);
	data->commands = NULL;
	if (parsing_bis(args, data, argc, &j) == 0)
		return (NULL);
	data->env = env;
	data->commands = malloc(sizeof(char **) * (argc - 2));
	if (!data->commands)
		return (ft_free_data(data), NULL);
	while (j < argc - 1)
		data->commands[i++] = ft_custom_split(args[j++], ' ');
	return (data->commands[i] = NULL, test_path(data), data);
}

//	Determine wich path to use to execute the commands
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

//	Assign the path to use to the command
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
