/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:55:17 by akozin            #+#    #+#             */
/*   Updated: 2024/04/11 16:14:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell/h"

void	com_filler(t_data *data, int *i, t_token *tokens)
{
	int	k;

	k = 0;
	while (++i[2] < i[1])
	{
		if (!ft_strncmp(tokens[i[2] + i[3]].token, "<", 2))
			data->coms[i[0]].com[i[2]].ins[k].dub = 0;
		else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">", 2))
			data->coms[i[0]].com[i[2]].outs[k].dub = 0;
		else if (!ft_strncmp(tokens[i[2] + i[3]].token, "<<", 3))
			data->coms[i[0]].com[i[2]].ins[k].dub = 1;
		else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">>", 3))
			data->coms[i[0]].com[i[2]].outs[k].dub = 1;
		// TODO put all of this in different funcs

		if (!ft_strncmp(tokens[i[2] + i[3]].token, "<", 2)
			|| !ft_strncmp(tokens[i[2] + i[3]].token, "<<", 3))
			data->coms[i[0]].com[i[2]].ins[k].fname = tokens[i[2] + i[3] + 1].token;
		else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">", 2)
			|| !ft_strncmp(tokens[i[2] + i[3]].token, ">>", 3))
			data->coms[i[0]].com[i[2]].outs[k].fname = tokens[i[2] + i[3] + 1].token;
		else
			data->coms[i[0]].com[i[2]] = tokens[i[2] + i[3]].token;
	}
}
