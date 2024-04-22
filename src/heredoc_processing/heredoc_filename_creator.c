/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename_creator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:27:50 by akozin            #+#    #+#             */
/*   Updated: 2024/04/22 13:38:46 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_strjoin_free(char *b1, char *b2)
{
	char	*t;

	t = ft_strjoin(b1, b2);
	if (b1)
		free(b1);
	b1 = NULL;
	return (t);
}

char	*gen_h_fname(int com, int hdoc)
{
	char	*fname;
	char	*c_num;
	char	*h_num;
	
	c_num = ft_itoa(com);
	h_num = ft_itoa(hdoc);
	fname = ft_strjoin("/tmp/.hdoc_temp_", c_num);
	fname = ft_strjoin_free(fname, "_");
	fname = ft_strjoin_free(fname, h_num);
	free(c_num);
	free(h_num);
	printf("%s\n", fname);
	return (fname);
}
