/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:58:17 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 15:00:56 by akozin           ###   ########.fr       */
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
	HDOC_LIMIT_ERR,
}	t_error;

#endif
