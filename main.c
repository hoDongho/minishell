/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:04:12 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/30 17:03:28 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c(int sig)
{
	int	t;

	t = 0;
	if (g_data.p_size == 0)
	{
		printf("\n");
		g_data.exit_code = 1;
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
	g_data.is_sig = 1;
	while (g_data.pidarr[t])
	{
		kill(g_data.pidarr[t], SIGKILL);
		t++;
	}
	g_data.exit_code = 128 + sig;
	g_data.p_size = 0;
}

void	ft_ctrl_bslash(int sig)
{
	int	t;

	t = 0;
	if (g_data.p_size == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
	g_data.is_sig = 1;
	while (t < g_data.p_size)
	{
		kill(g_data.pidarr[t], SIGKILL);
		t++;
	}
	g_data.exit_code = 128 + sig;
	g_data.p_size = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	t_par_mdata	par_mdata;

	ft_init(&par_mdata, argc, argv);
	ft_set_env(par_mdata.envlist, env);
	g_data.exit_code = 0;
	ft_start_minishell(&par_mdata);
	return (0);
}
