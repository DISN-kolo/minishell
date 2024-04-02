/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:43:45 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 13:55:35 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	benv(t_data *data, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i].key)
	{
		if (data->env[envi][i].exp)
			printf("%s=%s\n",
				data->env[envi][i].key, data->env[envi][i].value);
		i++;
	}
}
