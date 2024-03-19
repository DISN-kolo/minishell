/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/03/19 16:47:45 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_wtype
{
	COMMAND,
	OPERATOR,
	REDIR,
	END
}	t_wtype;

typedef struct s_com
{
	t_wtype	type;
	char	**com;
}	t_com;

typedef struct s_data
{
	char	**tokens;
	t_com	*coms;
}	t_data;

void	shell_loop(t_data *data);

#endif
