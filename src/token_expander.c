/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 17:20:54 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	inside_dollar_counter(t_data *data, char *t, int i)
{
	int	ret;
	int	in_q;
	int	start;

	ret = 0;
	in_q = 0;
	start = i + 1;
	if (!strchars(&(t[start], " \t\f\v!@#$%^&*()-=+[]{}\\;:,./?")))
}

int	expansion_counter(t_data *data, char *t)
{
	int	ret;
	int	i;
	int	j;
	int	in_q;

	ret = 1;
	i = 0;
	j = 0;
	in_q = 0;
	while (t[i])
	{
		if (in_q && (t[i] == '\'' || t[i] == '"'))
			in_q = 0;
		else if (!in_q && (t[i] == '\'' || t[i] == '"'))
			in_q = 1;
		if (!in_q && t[i] == '$')
			ret += inside_dollar_counter(data, t, i);
	}
}

char **token_expander(t_data *data, char *t)
{
	char	**add_argv;

	add_argv = malloc(sizeof (char *) * (expansion_counter(data, t) + 1));
	if !(add_argv)
		return (NULL); // TODO ?
}
