/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:05:10 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/29 14:53:09 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_flags(const char *orig, int *has_quote, int *has_dollar)
{
	*has_quote = 0;
	*has_dollar = 0;
	if (ft_strchr(orig, '\'') || ft_strchr(orig, '"'))
		*has_quote = 1;
	if (ft_strchr(orig, '$'))
		*has_dollar = 1;
}

int	should_remove_arg(const char *orig, const char *new_val)
{
	int	has_quote;
	int	has_dollar;

	init_flags(orig, &has_quote, &has_dollar);
    fprintf(stderr,"[DEBUG] should_remove_arg? orig='%s' has_q=%d has_$=%d new[0]=%d\n",orig, has_quote, has_dollar, (unsigned char)new_val[0]);
	if (!has_quote && has_dollar && new_val[0] == '\0')
		return (1);
	return (0);
}

void	remove_current_arg(t_arg **pp, t_arg **cur,
		char *orig, char *new_val)
{
	t_arg	*next;

	next = (*cur)->next;
	*pp = next;
	free(orig);
	free(new_val);
	free(*cur);
	*cur = next;
}

void	replace_arg_value(t_arg *cur, char *orig, char *new_val)
{
	free(orig);
	cur->value = new_val;
}

int	process_one_arg(t_arg **pp, t_arg **cur, t_pipex *ps, int *removed)
{
	char	*orig;
	char	*new_val;

	orig = (*cur)->value;
	new_val = expand_one(orig, ps);
    fprintf(stderr, "[DEBUG] orig='%s', new_val='%s'\n",orig, new_val ? new_val : "(null)");
	if (!new_val)
		return (FAILURE);
	if (should_remove_arg(orig, new_val))
	{
        fprintf(stderr, "[DEBUG] remove arg (orig='%s')\n", orig);
		remove_current_arg(pp, cur, orig, new_val);
		*removed = 1;
		return (SUCCESS);
	}
    fprintf(stderr, "[DEBUG] keep arg (orig='%s', new='%s')\n",orig, new_val);
	replace_arg_value(*cur, orig, new_val);
	*removed = 0;
	return (SUCCESS);
}

