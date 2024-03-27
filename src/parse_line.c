/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:19:46 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 16:27:53 by akozin           ###   ########.fr       */
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
			else if (env_add_to_the_end_of_envs_whatever(data->tokens[i + 1])) // TODO also must expand $s
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

char	*ft_sj_free(char *b1, char *b2)
{
	char	*t;

	if (!b1)
		t = b2;
	else
		t = ft_strjoin(b1, b2);
	if (!t)
		return (NULL);
	if (b1)
		free(b1);
	return (t);
}

/*
 * first while is to go thru every token
 *
// * sidenote:
// * it seems that $ substs can NOT join tokens
// * example:
// *
// * tokens: $a, $b
// * a: ", 1, 2, \0
// * b: 3, 4, ", \0
// *
// * $a $b converts to...
// * argv[n]: "12
// * argv[n+1]: 34"
// *
// * NOT argv[n]: 1234
// * THUS, we need some token_opener func
// * returns: char ** of "to-be-argv"s
 *
 *
 * second while is to go through everything that's not an operator.
 * keep in mind that commands are things sepped by operators.
 *
 * if we don't enter this second while, we skip the operator with the i++
 *
 * inside of the 2nd while:
 * if a token is <, <<, >, >>, we need to handle it and the second token
 * like the redirs they are. with susbt.
 * else, just continue filling the currentr command.
 * 
 * exiting the while must increase the j (current command index)
 *
 * speaking of current indices -- each time we meet "export" inside of the
 * second while, we increase the envi from data by 1 and move forward
 * until an op. we have to call the export command with an envi-1 env tho.
 */
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
			if (!ft_strncmp(data->tokens[i], "<", 2)
				|| !ft_strncmp(data->tokens[i], "<<", 3)
				|| !ft_strncmp(data->tokens[i], ">", 2)
				|| !ft_strncmp(data->tokens[i], ">>", 3))
					data->coms[j]->com = ft_sj_free(data->coms[j]->com, data->tokens[i]);
			if (!data->coms[j]->com)
				return (1); // TODO?
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
/*
 * there should be a current env id var in data (envi ?)
 */
void	parse_exec(t_data *data)
{
	if (data->errored)
		return ;
	if (pass_exp(data)) // TODO
		return ; // TODO exit with export checking error
	if (count_alloc_com(data))
		return ; // TODO exit with command counter/allocator error
	if (pass_com(data)) // TODO
		return ; // TODO exit with a meta exec error or with a parse error
}
