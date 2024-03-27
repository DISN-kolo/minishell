/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:23:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/27 17:35:59 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*read_env(t_data *data, char *prop, int envi)
{
	char	*key;
	int		i;

	key = ft_strjoin(prop, "=");
	if (!key)
		return (NULL);
	i = 0;
	while (data->env[envi][i])
	{
		if (!ft_strncmp(key, data->env[envi][i], ft_strlen(key)))
			break ;
		i++;
	}
	free(key);
	if (data->env[envi][i])
		return (data->env[envi][i] + ft_strlen(key));
	return (NULL);
}

void	print_env(t_data *data, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i])
		printf("%s\n", data->env[envi][i++]);
}
