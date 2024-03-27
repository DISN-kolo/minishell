/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 12:01:02 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../readline/readline.h"
#include "../readline/history.h"

static void	double_array_free(char ***a)
{
	int	i;

	i = 0;
	if (!(*a))
		return ;
	while ((*a)[i])
		free((*a)[i++]);
	free(*a);
}

static void	data_cleaner(t_data *data)
{
	int	i;

	if (data->env)
		ft_lstclear(&data->env, free);
	data->env = 0;
	if (data->tokens)
		double_array_free(&data->tokens);
	data->tokens = 0;
	i = 0;
	if (data->coms)
	{
		while (data->coms[i].type != END)
		{
			double_array_free(&(data->coms[i].com));
			i++;
		}
		free(data->coms);
	}
	data->coms = 0;
	data->errored = 0;
}

static void	exit_handler(t_data *data)
{
	data_cleaner(data);
	printf("exit\n");
}

/*
 * tokenize line packs stuff neatly into tokens like
 *
 * asd
 * -l
 * "asjsaudhiuoouaisdul"
 * qwe
 * 'asdj hds   jds jf    l a sd  " asdjasd "" '
 *
 *
 * expand etc is concerned with splitting and quote removal as well
 */
void	shell_loop(t_data *data)
{
	char	*s;

	s = readline("totally-not-bash $ ");
	while (s != 0)
	{
		add_history(s);
		tokenize_line(s, data);
		free(s);
		parse_line(data);
		redir_exec(data);
		data_cleaner(data);
		s = readline("totally-not-bash $ ");
	}
	if (s == 0)
		exit_handler(data);
}
