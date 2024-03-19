/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/03/19 16:27:43 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_wtype
{
	COMMAND,
	OPERATOR
}	t_wtype;

typedef struct s_com
{
	t_wtype	type;
	char	*com;
	char	*flags;
	char	*file;
}	t_com;

typedef struct s_data
{
	char	**tokens;
	t_com	*coms;
}	t_data;

void	shell_loop(t_data *data);

#endif
