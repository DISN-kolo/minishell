/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:01:48 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 13:37:40 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*var_end(char *s)
{
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (s);
		s++;
	}
	return (s);
}

/*
 * basically, an ft_split with "" in mind
 * like we have in tokenize, but isn't bothered by |<>& at all
 */
