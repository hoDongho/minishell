/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:04:12 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 11:26:03 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(t_envlist *envlist, char **env)
{
	int				i;
	int				cnt;
	char			*key;

	i = 0;
	while (env[i])
	{
		key = env[i];
		cnt = 0;
		while (*key)
		{
			if (*key == '=')
				break ;
			cnt++;
			key++;
		}
		key = 0;
		key = ft_calloc(cnt + 1, sizeof(char));
		ft_memmove(key, env[i], cnt);
		ft_push_env(key, getenv(key), envlist);
		free(key);
		i++;
	}
}

void	ft_clearcmd(t_cmdlist *cmdlist)
{
	t_cmdnode	*curr;
	t_cmdnode	*temp;

	curr = cmdlist->head->next;
	while (curr->next)
	{
		temp = curr;
		curr = curr->next;
		free(temp->str);
		free(temp);
	}
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0;
}

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
		kill(g_data.pidarr[t], SIGKILL); //free도 해주긴 해야함?? 잡고있기는 한 상황임
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
		kill(g_data.pidarr[t], SIGKILL); //free도 해주긴 해야함?? 잡고있기는 한 상황임
		t++;
	}
	g_data.exit_code = 128 + sig;
	g_data.p_size = 0; //ㅈ저ㅂ근을 convert에서 하고있음
}

int	main(int argc, char *argv[], char *env[])
{
	t_par_mdata	par_mdata;

	ft_init(&par_mdata, argc, argv);
	ft_set_env(par_mdata.envlist, env);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_bslash);
	g_data.exit_code = 0;
	ft_start_minishell(&par_mdata);
	return (0);
}
