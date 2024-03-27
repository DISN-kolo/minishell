/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:19:46 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 15:05:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pass_exp(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (!ft_strncmp(data->tokens[i], "export", 7))
		{
			if (ft_strncmp(data->tokens[i + 2], "|", 2))
				i++;
			else if (env_add_to_the_end_of_envs_whatever(data->tokens[i + 1])) // TODO
				return (1);
		}
		i++;
	}
	return (0);
}

int	count_alloc_com(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->tokens[i])
	{
		if (!ft_strncmp(data->tokens[i], "&&", 3)
				|| !ft_strncmp(data->tokens[i], "||", 3)
				|| !ft_strncmp(data->tokens[i], "|", 2))
			count++;
		i++;
	}
	data->coms = malloc(sizeof (t_com) * (count + 2));
	if (!data->coms)
		return (1);
	data->coms[count + 1] = NULL;
	return (0);
}

char	*ft_strjoin_free(char *b1, char *b2)
{
	char	*t;

	t = ft_strjoin(b1, b2);
	if (!t)
		return (NULL);
	if (b1)
		free(b1);
	return (t);
}


int	pass_com(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->tokens[i])
	{
		while (ft_strncmp(data->tokens[i], "&&", 3)
				&& ft_strncmp(data->tokens[i], "||", 3)
				&& ft_strncmp(data->tokens[i], "|", 2))
		{
			data->coms
			i++;
		}
		i++;
	}
	return (0);
}

/*
 * pass 1:
 * check for exports.
 * with each export, set the new env
 *
 * pass 2:
 * grab commands. expand $. when an export command is encountered (without
 * a | in the end), incriment the index of env used by 1.
 * each grabbed command is ran with its parameters. the exit status is given.
 */
void	parse_exec(t_data *data)
{
	if (pass_exp(data)) // TODO
		return ; // TODO exit with export checking error
	if (count_alloc_com(data))
		return ; // TODO exit with command counter/allocator error
	if (pass_com(data)) // TODO
		return ; // TODO exit with a meta exec error or with a parse error
	if (data->errored)
		return ;
}
