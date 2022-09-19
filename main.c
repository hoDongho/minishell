/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:04:12 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/19 12:21:25 by nhwang           ###   ########.fr       */
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

int main(int argc, char *argv[], char *env[])
{
	char		*input;
	char		**cc;
	int			i;
	t_par_mdata	par_mdata;

	i = 2;
	ft_init(&par_mdata);
	ft_set_env(par_mdata.envlist, env);
	while (1)
	{
		ft_clearcmd(par_mdata.cmdlist);
		input = readline("test:");
		if (!input)
			break ;
		add_history(input);
		if (!*input)
		{
			free(input);
			continue ;
		}
		par_mdata.origin = input;
		if (ft_parse(&par_mdata) == 1)
		{
			free(input);
			continue ;
		}
		if (ft_strcmp(par_mdata.cmdlist->head->next->str, "echo") == 0)
			ft_echo(par_mdata.cmdlist, par_mdata.envlist);
		else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "cd") == 0)
			ft_cd(par_mdata.cmdlist, par_mdata.envlist);
		else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "exit") == 0)
			ft_exit(par_mdata.cmdlist, &par_mdata);
		else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "export") == 0)
			ft_export(&par_mdata);
		else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "env") == 0)
			ft_env(par_mdata.envlist, 0);
		else if (ft_strcmp(par_mdata.cmdlist->head->next->str, "unset") == 0)
			ft_unset(&par_mdata);
		free(input);
		printf("\n-----------------------------------------------------------------------\n");
		system("leaks a.out");
		printf("-----------------------------------------------------------------------\n\n");
	}
	return (0);
}
