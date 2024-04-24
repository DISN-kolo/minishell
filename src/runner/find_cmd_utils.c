/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:44:13 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/23 12:25:13 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	i = 0;
	while (str[i] == '.')
		i++;
	if (i == 1 || i == 2)
		return (1);
	return (0);
}