/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:12:42 by akozin            #+#    #+#             */
/*   Updated: 2024/04/15 14:52:52 by akozin           ###   ########.fr       */
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
			data->hds[j] = malloc(sizeof (t_hdoc) * (heredocs_c + 1));
			if (!data->hds[j++])
				return (1);
			heredocs_c = 0;
		}
	}
	data->hds[j] = malloc(sizeof (t_hdoc) * (heredocs_c + 1));
	if (!data->hds[j])
		return (1);
	return (0);
}

static void	fill_heredocs(t_data *data)
{
	int	j;
	int	i;
	int	hd_c;

	i = -1;
	j = 0;
	hd_c = 0;
	while (data->tokens[++i].token)
	{
		if (!ft_strncmp(data->tokens[i].token, "<<", 3))
		{
			data->hds[j][hd_c].str = data->tokens[i + 1].token;
			data->hds[j][hd_c++].expand = (data->tokens[i + 1].token[0] != '\''
					&& data->tokens[i + 1].token[0] != '"');
		}
		if (!ft_strncmp(data->tokens[i].token, "||", 3)
			|| !ft_strncmp(data->tokens[i].token, "&&", 3))
		{
			data->hds[j++][hd_c].str = NULL;
			hd_c = 0;
		}
	}
	data->hds[j][hd_c].str = NULL;
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
	data->hds = malloc(sizeof (t_hdoc *) * (cmd_c + 1));
	if (!data->hds)
		return ; // TODO
	if (alloc_heredocs(data))
		return ; // TODO
	fill_heredocs(data);
	data->hds[cmd_c] = NULL;
	// TODO remove this! debug stuff vvvvvvvvvvvvvvvvvvvvvvvv
	for (int x = 0; x < cmd_c; x++)
	{
		printf("inside command #%3d,\n", x);
		for (int y = 0; data->hds[x][y].str; y++)
			printf("\theredoc #%3d: %s\n"
					"\tdo we expand? %d\n", y, data->hds[x][y].str, data->hds[x][y].expand);
	}
}
