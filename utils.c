/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rufurush <rufurush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:48:35 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/25 19:05:19 by rufurush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dprintf(int fd, char *filename, char *err_msg)
{
	ft_putstr_fd("minishell$ ", fd);
	if (!filename || !*filename)
		return ;
	if (filename)
		ft_putstr_fd((char *)filename, fd);
	ft_putstr_fd(": ", fd);
	if (err_msg)
		ft_putstr_fd((char *)err_msg, fd);
	ft_putstr_fd("\n", fd);
}
