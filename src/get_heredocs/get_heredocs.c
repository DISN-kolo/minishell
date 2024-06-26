/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:12:42 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 13:58:05 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	alloc_heredocs(t_data *data)
{
	int	j;
	int	i;
	int	heredocs_c;

	i = 0;
	j = 0;
	heredocs_c = 0;
	while (data->tokens[i].token && i != data->sp_hdoc)
	{
		if (data->tokens[i].type == HDOC)
			heredocs_c++;
		if (data->tokens[i].type == OR || data->tokens[i].type == AND)
		{
			data->hds[j] = malloc(sizeof (t_hdoc) * (heredocs_c + 1));
			if (!data->hds[j++])
				return (1);
			heredocs_c = 0;
		}
		i++;
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

static int	get_hd_str(t_data *data, char **s, t_token t)
{
	int		i;
	int		j;
	int		in_q;

	(*s) = malloc(hd_str_count(t.token) + 1);
	if (!(*s))
		return (1);
	i = 0;
	j = 0;
	in_q = 0;
	while (t.token[i] && i != data->sp_hdoc)
	{
		determine_q(&in_q, t.token[i]);
		if (!((in_q == 1 && t.token[i] == '\'')
				|| (in_q == 2 && t.token[i] == '"')
				|| (!in_q && ft_strchr("'\"", t.token[i]))))
			(*s)[j++] = t.token[i];
		i++;
	}
	(*s)[j] = 0;
	return (0);
}

static int	fill_heredocs(t_data *d)
{
	int	j;
	int	i;
	int	hd_c;

	i = 0;
	j = 0;
	hd_c = 0;
	while (d->tokens[i].token && i != d->sp_hdoc)
	{
		if (d->tokens[i].type == HDOC)
		{
			if (get_hd_str(d, &(d->hds[j][hd_c].str), d->tokens[i + 1]))
				return (1);
			d->hds[j][hd_c].latest = is_latest_hd(&d->tokens[i + 1]);
			d->hds[j][hd_c++].expand = strchars(d->tokens[i + 1].token,
					"'\"") == NULL;
		}
		if (d->tokens[i].type == OR || d->tokens[i].type == AND)
			d->hds[j++][hd_c].str = NULL;
		hd_c -= hd_c * (d->tokens[i].type == OR || d->tokens[i].type == AND);
		i++;
	}
	d->hds[j][hd_c].str = NULL;
	return (0);
}

t_error	get_heredocs(t_data *data)
{
	int	i;
	int	cmd_c;

	i = 0;
	cmd_c = 0;
	while (data->tokens[i].token && i != data->sp_hdoc)
	{
		cmd_c += data->tokens[i].type == OR || data->tokens[i].type == AND;
		i++;
	}
	cmd_c++;
	data->hds = malloc(sizeof (t_hdoc *) * (cmd_c + 1));
	if (!data->hds || alloc_heredocs(data) || fill_heredocs(data))
		return (MALLOC_ERR);
	data->hds[cmd_c] = NULL;
	return (NULL_ERR);
}
