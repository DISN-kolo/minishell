/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename_creator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:27:50 by akozin            #+#    #+#             */
/*   Updated: 2024/05/23 11:36:45 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	on_error_free(char *c_num, char *h_num)
{
	if (c_num)
		free(c_num);
	if (h_num)
		free(h_num);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
		return (free(s1), NULL);
	free(s1);
	return (str);
}

char	*ft_strjoin3_free(char *s1, char *s2, char *s3)
{
	char	*str;

	str = ft_strjoin3(s1, s2, s3);
	if (!str)
		return (free(s1), NULL);
	free(s1);
	return (str);
}

char	*gen_h_fname(t_data *data, int *i)
{
	char	*fname;
	char	*c_num;
	char	*h_num;

	c_num = ft_itoa(i[0]);
	if (!c_num)
		return (NULL);
	h_num = ft_itoa(i[1]);
	if (!h_num)
		return (free(c_num), NULL);
	fname = ft_strjoin3("/tmp/.hdoc_temp_", c_num, "-");
	if (!fname)
		return (on_error_free(c_num, h_num), NULL);
	fname = ft_strjoin3_free(fname, h_num, "-");
	if (!fname)
		return (on_error_free(c_num, h_num), NULL);
	fname = ft_strjoin_free(fname, data->hdoc_id);
	if (!fname)
		return (on_error_free(c_num, h_num), NULL);
	free(c_num);
	free(h_num);
	return (fname);
}
