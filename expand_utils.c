/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:38:58 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/29 14:50:59 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv_dup(t_pipex *ps, const char *key)
{
	t_env_list	*cur;
	size_t		key_len;

	if (!ps || !key || !*key)
		return (ft_strdup(""));
	cur = ps->env_list;
	key_len = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0
			&& ft_strlen(cur->key) == key_len)
		{
			if (cur->value)
				return (ft_strdup(cur->value));
			else
				return (ft_strdup(""));
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}

char	*expand_one(const char *arg, t_pipex *ps)
{
	t_expand_ctx	ctx;

	ctx.arg = arg;
	ctx.ps = ps;
	ctx.out = ft_strdup("");
	if (!ctx.out)
		return (NULL);
	ctx.i = 0;
	ctx.in_squote = 0;
	ctx.in_dquote = 0;
	ctx.should_break = 0;
	if (!expand_one_loop(&ctx))
		return (NULL);
	return (ctx.out);
}

// char	*ms_getenv_dup(t_pipex *ps, const char *key)
// {
// 	t_env_list	*cur;

// 	if (!ps || !key || !*key)
// 		return (ft_strdup(""));
// 	cur = ps->env_list;
// 	while (cur)
// 	{
// 		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0
// 			&& ft_strlen(cur->key) == ft_strlen(key))
// 			return (ft_strdup(cur->value ? cur->value : ""));
// 		cur = cur->next;
// 	}
// 	return (ft_strdup(""));
// }
