/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:53:55 by bszikora          #+#    #+#             */
/*   Updated: 2024/09/10 14:54:49 by bszikora         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;
}

void setup_signal_handling() // Function to handle 'CTRL + C' and 'CTRL + \'
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_putstr_fd("sigaction error for SIGINT\n", STDERR_FILENO);
		exit(1);
	}
	sa.sa_handler = handle_sigquit;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		ft_putstr_fd("sigaction error for SIGQUIT\n", STDERR_FILENO);
		exit(1);
	}
}