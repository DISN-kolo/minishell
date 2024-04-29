/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:12:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/29 13:08:43 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(char * cmd, char *var, char *error)
{
	if (cmd)
		ft_putstr_fd(cmd, 2);
	else
		ft_putstr_fd("minishell", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}
