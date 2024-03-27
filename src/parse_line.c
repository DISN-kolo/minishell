/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:19:46 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 14:17:02 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pass_exp(t_data *data)
{
	int	i;

	i = -1;
	while (data->tokens[i++])
		printf("%s ", data->tokens[i]);
	printf("\n");
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
//	if (pass_com(data)) // TODO
//		return ; // TODO exit with a meta exec error or with a parse error
	if (data->errored)
		return ;
}
