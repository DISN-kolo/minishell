/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:09:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/20 16:19:15 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].key)
	{
		if (data->env[i].exp)
			printf("declare -x %s=\"%s\"\n",
				data->env[i].key, data->env[i].value);
		else
			printf("declare -x %s\n", data->env[i].key);
		i++;
	}
}

int	bexport(t_data *data, char **exports)
{
	int	i;
	int	error;

	if (!exports[0])
		return (print_export(data), 0);
	error = 0;
	i = 0;
	while (exports[i])
	{
		if (!(ft_isalpha(exports[i][0]) || exports[i][0] == '_')
			|| export_env(data, exports[i]))
		{
			print_error("minishell: export", exports[i],
				"not a valid identifier");
			error = 1;
		}
		i++;
	}
	return (error);
}
