/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:06:29 by akozin            #+#    #+#             */
/*   Updated: 2024/05/09 14:02:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_err;

static int	init_data(t_data *data, char **envp)
{
	data->tokens = NULL;
	data->cmdtree = NULL;
	data->coms = NULL;
	data->hds = NULL;
	data->status_code = 0;
	data->skip_cmd = 0;
	data->skip_brackets = 0;
	data->stop_hdoc = -1;
	data->std_in = dup(0);
	data->std_out = dup(1);
	if (data->std_in < 0 || data->std_out < 0)
		return (1);
	data->env = alloc_env(envp);
	if (!data->env)
	{
		close(data->std_in);
		close(data->std_out);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	g_err = 0;
	if (init_data(&data, envp))
		return (1);
	shell_loop(&data);
	return (0);
}
