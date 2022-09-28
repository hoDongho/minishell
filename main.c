/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:04:12 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 15:02:16 by nhwang           ###   ########.fr       */
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
		key = calloc(cnt + 1, sizeof(char));
		memmove(key, env[i], cnt);
		ft_push_env(key, getenv(key), envlist);
		free(key);
		i++;
	}
}
		// printf("env : %s\n", env[i]);
		// printf("key : %s\n", new->key);
		// printf("val : %s\n\n", new->val);

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
	int t;
	t = 0;
	if (g_data.p_size==0)
	{

		printf("\n");
		g_data.exit_code = 1;//nhwang
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return;
	}
	// while(t<g_data.p_size)
	g_data.is_sig = 1; //fork를 뜨는 경우 exev인 모든 경우 // b-in이 여러개인 경우 == 자식을 만드는 경우에 대한 모든 케이스
	while(g_data.pidarr[t])
	{
		kill(g_data.pidarr[t],SIGKILL); //free도 해주긴 해야함?? 잡고있기는 한 상황임
		t++;
	}
	g_data.exit_code = 128+sig;
	g_data.p_size = 0;
}

void	ft_ctrl_bslash(int sig)
{
	int t;
	t = 0;
	if (g_data.p_size==0)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return;
	}
	g_data.is_sig = 1;
	while(t<g_data.p_size)
	{
		kill(g_data.pidarr[t],SIGKILL); //free도 해주긴 해야함?? 잡고있기는 한 상황임
		t++;
	}
	g_data.exit_code = 128+sig;
	g_data.p_size = 0; //ㅈ저ㅂ근을 convert에서 하고있음
}

int main(int argc, char *argv[], char *env[])
{
	char		*input;
	char		**cc;
	int			i;
	t_par_mdata	par_mdata;

	i = 2;
	ft_init(&par_mdata);
	ft_set_env(par_mdata.envlist, env);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_bslash);
	g_data.exit_code = 0; //
	while (1)
	{
		// printf("-----\n\n");
		// system("leaks -quiet a.out");
		// printf("-----\n\n");
		ft_clearcmd(par_mdata.cmdlist);
		input = readline("minishell$ ");
		if (!input)
		{
			break ;
		}
		if (!*input)
		{
			// g_data.exit_code = 0;//nhwang
			free(input);
			continue ;
		}
		add_history(input);
		par_mdata.origin = input;
		if (ft_parse(&par_mdata) == 1)
		{
			free(input);
			continue ;
		}
		free(input);//
		ft_exec(par_mdata.cmdlist, par_mdata.envlist);
		// t_cmdnode *arg;
		// arg = par_mdata.cmdlist->head->next;
		// int a;
		// a = 0;
		// while (arg->next)
		// {
		// 	if (ft_strcmp(arg->str, "|") == 0)
		// 	{
		// 		ft_exec_cmds(par_mdata.cmdlist, par_mdata.envlist);
		// 		a = 1;
		// 		break;
		// 	}
		// 	arg = arg->next;
		// }
		// if (a==1)
		// {
		// 	continue ;
		// }
		// if (ft_strcmp(par_mdata.cmdlist->head->next->str, "echo") == 0)
		// 	ft_echo(par_mdata.cmdlist, par_mdata.envlist);
		// else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "pwd") == 0)
		// 	ft_pwd();
		// else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "cd") == 0)
		// 	ft_cd(par_mdata.cmdlist, par_mdata.envlist);
		// else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "exit") == 0)
		// 	ft_exit(par_mdata.cmdlist, &par_mdata);
		// else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "export") == 0)
		// 	ft_export(&par_mdata);
		// else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "env") == 0)
		// 	ft_env(par_mdata.envlist, 0);
		// else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "unset") == 0)
		// 	ft_unset(&par_mdata);
		// else
		// 	a = 2;
		// int	pid;
		// if (a == 2)
		// {
		// 	ft_exec_cmds(par_mdata.cmdlist, par_mdata.envlist);
		// }
		// printf("\n-----------------------------------------------------------------------\n");
		// system("leaks a.out");
		// printf("-----------------------------------------------------------------------\n\n");
	}
	return (0);
}
