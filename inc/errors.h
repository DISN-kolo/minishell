/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:58:17 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/20 15:45:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_error
{
	NULL_ERR,
	SYNTAX_ERR,
	LEFT_Q_ERR,
	MALLOC_ERR,
	DUP2_ERR,
	FORK_ERR,
	PIPE_ERR,
	HDOC_LIMIT_ERR,
	OPEN_ERR,
	CLOSE_ERR,
}	t_error;

#endif
