/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaba <sbaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:14:35 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/26 17:46:49 by sbaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_parent_builtin_then_cleanup(t_ast *node_list, t_pipex *ps, char *line,
		int *handled)
{
	*handled = 0;
	if (is_parent_builtin(node_list) == SUCCESS)
	{
		exec_builtin(ps, node_list);
		ast_free_a(node_list);
		free(line);
		*handled = 1;
		return (0);
	}
	return (0);
}

int	run_pipeline_and_cleanup(t_ast *node_list, t_pipex *ps)
{
	int	status;

	status = run_node(ps, node_list);
	ast_free_a(node_list);
	return (status);
}

int	build_nodes_from_line(const char *line, t_ast **out, t_pipex *ps)
{
	t_token_list	*tokens;
	t_token_list	*head;

	*out = NULL;
	tokens = create_token_list((char *)line);
	if (!tokens)
		return (-1);
	head = tokens;
	*out = parse_pipeline(&tokens);
	if (!*out)
	{
		free_token_list(&head);
		return (-1);
	}
	expand_command_line(*out, ps);
	if (!*out)
	{
		free_token_list(&head);
		return (1);
	}
	free_token_list(&head);
	return (0);
}

char	*ms_readline(void)
{
	return (readline("minishell$"));
}

int	post_read_signal_handle(char *line, t_pipex *ps, int *should_continue)
{
	*should_continue = 0;
	if (g_sigflags == SIGINT)
		ps->last_status = 130;
	else if (g_sigflags == SIGQUIT)
		ps->last_status = 131;
	if (g_sigflags == SIGINT || g_sigflags == SIGQUIT)
	{
		if (line[0] == '\0')
		{
			g_sigflags = 0;
			free(line);
			*should_continue = 1;
			return (1);
		}
		g_sigflags = 0;
	}
	return (0);
}

// int	build_nodes_from_line(const char *line, t_ast **out, t_pipex *ps)
// {
// 	t_token_list	*tokens;

// 	*out = NULL;
// 	tokens = create_token_list((char *)line);
// 	if (!tokens)
// 		return (-1);
// 	*out = parse_pipeline(&tokens);
// 	if (!*out)
// 		return (-1);
// 	expand_command_line(*out, ps);
// 	if (!*out)
// 		return (1);
// 	return (0);
// }
