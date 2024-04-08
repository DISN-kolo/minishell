/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:43:45 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/03 15:01:32 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	benv(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].key)
	{
		if (data->env[i].exp)
			printf("%s=%s\n", data->env[i].key, data->env[i].value);
		i++;
	}
}
