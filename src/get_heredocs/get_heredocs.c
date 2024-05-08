/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:12:42 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 15:35:03 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		if (data->tokens[i].type == HDOC)
			heredocs_c++;
		if (data->tokens[i].type == OR || data->tokens[i].token == AND)
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

static int	hd_str_count(char *s)
{
	int	i;
	int	c;
	int	in_q;

	i = -1;
	c = 0;
	in_q = 0;
	while (s[++i])
	{
		determine_q(&in_q, s[i]);
		if (!((in_q == 1 && s[i] == '\'')
				|| (in_q == 2 && s[i] == '"')
				|| (!in_q && ft_strchr("'\"", s[i]))))
			c++;
	}
	return (c);
}

static char	*get_hd_str(t_token t)
{
	char	*ret;
	int		i;
	int		j;
	int		in_q;

	ret = malloc(hd_str_count(t.token));
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	in_q = 0;
	while (t.token[++i])
	{
		determine_q(&in_q, t.token[i]);
		if (!((in_q == 1 && t.token[i] == '\'')
				|| (in_q == 2 && t.token[i] == '"')
				|| (!in_q && ft_strchr("'\"", t.token[i]))))
			ret[j++] = t.token[i];
	}
	ret[j] = 0;
	return (ret);
}

static int	fill_heredocs(t_data *data)
{
	int	j;
	int	i;
	int	hd_c;

	i = -1;
	j = 0;
	hd_c = 0;
	while (data->tokens[++i].token)
	{
		if (data->tokens[i].type == HDOC)
		{
			data->hds[j][hd_c].str = get_hd_str(data->tokens[i + 1]);
			if (!data->hds[j][hd_c].str)
				return (1);
			data->hds[j][hd_c].expand = strchars(data->tokens[i + 1].token,
					"'\"") == NULL;
			data->hds[j][hd_c++].latest = is_latest_hd(&data->tokens[i + 1]);
		}
		if (data->tokens[i].type == OR || data->tokens[i].type == AND)
		{
			data->hds[j++][hd_c].str = NULL;
			hd_c = 0;
		}
	}
	data->hds[j][hd_c].str = NULL;
	return (0);
}

int	get_heredocs(t_data *data)
{
	int	i;
	int	cmd_c;

	i = -1;
	cmd_c = 0;
	while (data->tokens[++i].token)
		cmd_c += data->tokens[i].type == OR || data->tokens[i].type == AND;
	cmd_c++;
	data->hds = malloc(sizeof (t_hdoc *) * (cmd_c + 1));
	if (!data->hds || alloc_heredocs(data) || fill_heredocs(data))
		return (1);
	data->hds[cmd_c] = NULL;
	return (0);
}
