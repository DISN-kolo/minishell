/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:12:42 by akozin            #+#    #+#             */
/*   Updated: 2024/04/15 13:47:00 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	alloc_heredocs(t_data *data)
{
	int	j;
	int	i;
	int	heredocs_c;

	i = -1;
	j = 0;
	heredocs_c = 0;
	while (data->tokens[++i].token)
	{
		if (!ft_strncmp(data->tokens[i].token, "<<", 3))
			heredocs_c++;
		if (!ft_strncmp(data->tokens[i].token, "||", 3)
			|| !ft_strncmp(data->tokens[i].token, "&&", 3))
		{
			data->heredocs[j] = malloc(sizeof (char **) * (heredocs_c + 1));
			if (!data->heredocs[j])
				return (1);
			heredocs_c = 0;
			j++;
		}
	}
	data->heredocs[j] = malloc(sizeof (char **) * (heredocs_c + 1));
	if (!data->heredocs[j])
		return (1);
	return (0);
}

static void	fill_heredocs(t_data *data)
{
	int	j;
	int	i;
	int	heredocs_c;

	i = -1;
	j = 0;
	heredocs_c = 0;
	while (data->tokens[++i].token)
	{
		if (!ft_strncmp(data->tokens[i].token, "<<", 3))
		{
			data->heredocs[j][heredocs_c] = data->tokens[i + 1].token;
			heredocs_c++;
		}
		if (!ft_strncmp(data->tokens[i].token, "||", 3)
			|| !ft_strncmp(data->tokens[i].token, "&&", 3))
		{
			data->heredocs[j][heredocs_c] = NULL;
			heredocs_c = 0;
			j++;
		}
	}
}

void	get_heredocs(t_data *data)
{
	int	i;
	int	cmd_c;

	i = -1;
	cmd_c = 0;
	while (data->tokens[++i].token) 
		cmd_c += !ft_strncmp(data->tokens[i].token, "||", 3)
			|| !ft_strncmp(data->tokens[i].token, "&&", 3);
	cmd_c++;
	data->heredocs = malloc(sizeof (char ***) * (cmd_c + 1));
	if (!data->heredocs)
		return ; // TODO
	if (alloc_heredocs(data))
		return ; // TODO
	fill_heredocs(data);
	data->heredocs[cmd_c] = NULL;
	// TODO remove this! debug stuff vvvvvvvvvvvvvvvvvvvvvvvv
	for (int x = 0; x < cmd_c; x++)
	{
		printf("inside command #%3d,\n", x);
		for (int y = 0; data->heredocs[x][y]; y++)
			printf("\theredoc #%3d: %s\n", y, data->heredocs[x][y]);
	}
}
