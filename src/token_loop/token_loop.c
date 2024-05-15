/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/05/07 17:57:06 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_cmd(t_data *data, t_cmdtree *tree)
{
	t_token	*tokens;
	int		open_error;

	tokens = token_expander(data, tree->tokens);
	if (!tokens)
		return (1);
	cmd_loop(data, tokens);
	open_error = open_everything(data);
	if (!open_error)
	{
		run_cmds(data);
		if (dup2(data->std_out, 1) < 0 || dup2(data->std_in, 0) < 0)
			return (print_perror("Dup stdout and stdin", -1), 1);
	}
	else if (open_error == -3)
		return (1); // no command entered but there are redirs or something
	else
		printf("in token loop, open error = %d\n", open_error);
	return (0);
}

static int	btree_apply_infix(t_data *data, t_cmdtree *root)
{
	if (root)
	{
		if (btree_apply_infix(data, root->left))
			return (1);
		if (root->tokens[0].type != AND && root->tokens[0].type != OR
			&& !data->skip_cmd && data->skip_brackets <= root->brackets
			&& run_cmd(data, root))
			return (1);
		if (root->tokens[0].type != AND && root->tokens[0].type != OR
			&& data->skip_cmd && data->skip_brackets >= root->brackets)
			data->skip_cmd = 0;
		if ((root->tokens[0].type == AND && data->status_code)
			|| (root->tokens[0].type == OR && !data->status_code))
		{
			data->skip_cmd = 1;
			data->skip_brackets = root->brackets;
		}
		if (btree_apply_infix(data, root->right))
			return (1);
	}
	return (0);
}

int	token_loop(t_data *data)
{
	if (btree_apply_infix(data, data->cmdtree))
		return (1); // TODO control errors
	data->skip_brackets = 0;
	return (0);
}
