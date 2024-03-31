/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:04:34 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 15:09:12 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void bpwd(t_data *data, char **args, int envi)
{
	if (ft_strslen(args))
		printf("pwd: too many arguments\n");
	else
		printf("%s\n", read_env(data, "PWD", envi));
}
