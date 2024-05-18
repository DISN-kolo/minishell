/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:58:17 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/18 13:21:16 by molasz-a         ###   ########.fr       */
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
	OPEN_ERR,
}	t_error;

#endif
