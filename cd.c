/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:59:47 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/16 12:50:47 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	if (s1 == 0 && s2 == 0)
		return (new);
	else if (s1 == 0)
		return (strdup(s2));
	else if (s2 == 0)
		return (strdup(s1));
	len1 = strlen(s1);
	len2 = strlen(s2);
	new = calloc(len1 + len2 + 1, sizeof(char));
	if (new == 0)
		return (0);
	memmove(new, s1, len1);
	memmove(new + len1, s2, len2);
	return (new);
}

char	*find_val(t_envlist *envlist, char *key)
{
	t_envnode	*curr;

	curr = envlist->head->next;
	while(curr->next)
	{
		if (strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	if (!curr->next)
		return (0);
	return (curr->val);
}

void	change_val(t_envlist *envlist, char *key, char *val)
{
	t_envnode	*curr;
	t_envnode	*new;

	curr = envlist->head->next;
	while(curr->next)
	{
		if (strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	if (!curr->next)
	{
		new = ft_newenv();
		new->key = strdup(key);
		new->val = val;
		envlist->tail->prev->next = new;
		new->next = envlist->tail;
		new->prev = envlist->tail->prev;
		envlist->tail->prev = new;
		envlist->datasize++;
		return ;
	}
	if (curr->val != 0)
		free(curr->val);
	curr->val = val;
}

int	ft_cd(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*arg;
	char		*home;
	char		*old_pwd;
	char		*path;

	arg = cmdlist->head->next->next;
	home = find_val(envlist, "HOME");
	old_pwd = getcwd(0, 0);
	path = ft_strdup(home);
	if (arg->next)
	{
		free(path);
		if(*arg->str == 0)
			path = ft_strdup(old_pwd);
		else if (arg->str[0] == '~')
		{
			path = ft_strjoin(home, &arg->str[1]);
		}
		else if (arg->str[0] == '-' && arg->str[1] == 0)
		{
			path = find_val(envlist, "OLDPWD");
			if (path == 0)
				printf("cd: OLDPWD not set\n");
			else
			{
				path = ft_strdup(path);
				printf("%s\n", path);
			}
		}
		else
		{
			path = ft_strdup(arg->str);
		}


	}
	errno = 0;
	if (chdir(path) != 0)
		printf("errno : %d\n", errno);
	free(path);
	change_val(envlist, "PWD", getcwd(0, 0));
	change_val(envlist, "OLDPWD", old_pwd);
	return (0);
}
