/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:09:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/05 14:03:56 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	print_export(t_data *data)
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
	return (0);
}

int	bexport(t_data *data, char **exports)
{
	int	i;

	if (!exports)
		return (print_export(data));
	i = 0;
	while (exports[i])
	{
		if (export_env(data, exports[i]))
		{
			write(2, "minishell: export: `", 20);
			write(2, exports[i], ft_strlen(exports[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		i++;
	}
	return (0);
}
