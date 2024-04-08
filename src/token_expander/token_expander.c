/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/04/08 13:21:06 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	inside_dollar_counter(t_data *data, char *t, int i)
{
	int		ret;
	char	*env_v_name;
	char	*env_v_val;

	if (t[i + 1] != '_' && !ft_isalpha(t[i + 1]))
		return (0);
	env_v_name = ft_substr(&t[i + 1], 0, var_end(&t[i + 1]) - &t[i + 1]);
	env_v_val = read_env(data, env_v_name);
	if (!env_v_val)
		return (-ft_strlen(env_v_name));
	ret = ft_strlen(env_v_val) - ft_strlen(env_v_name);
	free(env_v_name);
	return (ret);
}

static int	expansion_counter(t_data *data, char *t)
{
	int	ret;
	int	i;
	int	in_q;

	ret = 0;
	i = 0;
	in_q = 0;
	while (t[i])
	{
		if ((in_q == 1 && t[i] == '\'') || (in_q == 2 && t[i] == '"'))
			in_q = 0;
		else if (!in_q && (t[i] == '\'' || t[i] == '"'))
			in_q = (t[i] == '"') + 1;
		if (in_q != 1 && t[i] == '$')
			ret += inside_dollar_counter(data, t, i) - 1;
		i++;
	}
	return (i + ret);
}

/*
 * new tokens = final returned tokens re-made from data->tokens with
 * expansion n stuff
 *
 * local n tokens = tokens received while expanding an existing token from
 * data->tokens. they need to be added to the new tokens
 *
 * exp t is a single token to be expanded. inside of it we push our stuff from
 * the current data->tokens token, then we pass this exp t to the function that
 * creates the local n tokens, dissecting exp t.
 */
void	token_expander(t_data *data, t_token *current_tokens)
{
	int		i;
	t_token	*new_tokens;
	t_token	*local_n_t;
	t_token	exp_t;
	int		exp_len;

	if (data->errored)
		return ;
	i = 0;
	new_tokens = NULL;
	while (current_tokens[i].token) // TODO norm, error returns, CHECK THE THING IF IT WORKS LOL
	{
		printf("======      ======\n");
		printf("in current_tokens[%2d]\n", i);
		exp_len = expansion_counter(data, current_tokens[i].token);
		exp_t.token = malloc(exp_len + 1);
		exp_t.literal = malloc(sizeof (int) * exp_len);
		if (!exp_t.token || !exp_t.literal)
			return ;
		dollar_expander(&exp_t, data, current_tokens[i].token);
		printf("BEHOLD! the new line looks like this: %s\n", exp_t.token);
		printf("while the literal of the first character is %d\n", exp_t.literal[0]);
		local_n_t = new_t_split(exp_t);
		if (!local_n_t)
			return ;
		printf("local n t obtained\n");
		for (int a = 0; a < 5; a++)
		{
			printf("with a = %d\n", a);
			if (local_n_t[a].token)
				printf("local n t token number %d is %s\n", a, local_n_t[a].token);
			else
				break ;
		}
		new_tokens = tokens_join_free(new_tokens, local_n_t);
		if (!new_tokens)
			return ;
		printf("new_tokens joined\n");
		i++;
	}
	free_ret(&(current_tokens));
	current_tokens = new_tokens;
	if (current_tokens)
	{
		for (int j = 0; current_tokens[j].token != NULL; j++)
		{
			printf("new token %3d: %s\n", j, current_tokens[j].token);
		}
	}
}
