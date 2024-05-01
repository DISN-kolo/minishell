/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:12:42 by akozin            #+#    #+#             */
/*   Updated: 2024/05/01 14:48:10 by akozin           ###   ########.fr       */
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
		return (NULL); // TODO ? or is it ok
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
			data->hds[j][hd_c].str = get_hd_str(data->tokens[i + 1]);
			data->hds[j][hd_c].latest = is_latest_hd(&data->tokens[i + 1]);
			data->hds[j][hd_c++].expand = (strchars(data->tokens[i + 1].token,
						"'\"") == NULL);
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
}
