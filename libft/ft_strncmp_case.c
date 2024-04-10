/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:54:38 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/10 11:09:31 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_case(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (n--)
	{
		if (!s1[i] || !s2[i] || ft_tolower(str1[i]) != ft_tolower(str2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
