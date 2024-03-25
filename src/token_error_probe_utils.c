/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_probe_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:22:53 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 17:32:35 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tokenize_error(char *s, int i)
{
	ft_putstr_fd("incorrect token placement of ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" token at position ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
