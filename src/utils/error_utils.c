/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:12:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 19:18:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *cmd, char *var, char *error)
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

void	print_perror(char *msg, int error)
{
	perror(msg);
	if (error >= 0)
		exit(error);
}

void	tokenize_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}
