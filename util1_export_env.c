/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_export_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:08:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 11:07:20 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_env(t_envlist *envlist, int b)
{
	t_envnode	*curr;
	t_envnode	*temp;

	g_data.exit_code = 0;
	curr = envlist->head->next;
	while (curr->next)
	{
		if (b && ft_strcmp(curr->key, "_") == 0)
		{
			curr = curr->next;
			continue ;
		}
		if (curr->val)
			printf("%s=%s\n", curr->key, curr->val);
		else
			if (b)
				printf("%s\n", curr->key);
		curr = curr->next;
	}
}

int	ft_push_env(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*new;
	t_envnode	*prev;

	new = ft_newenv();
	new->key = strdup(tkey);
	if (!new || !(new->key))
		return (1);
	if (tval)
		new->val = strdup(tval);
	prev = envlist->tail->prev;
	new->next = envlist->tail;
	new->prev = prev;
	prev->next = new;
	envlist->tail->prev = new;
	envlist->datasize++;
	return (0);
}

int	ft_findenv(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*curr;
	size_t		size;

	curr = envlist->head->next;
	while (curr->next)
	{
		size = strlen(tkey);
		if (ft_strcmp(tkey, curr->key) == 0)
		{
			if (tval)
			{
				free(curr->val);
				curr->val = strdup(tval);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_ex_util(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*prev_tail;

	if (ft_findenv(tkey, tval, envlist) == 0)
		if (ft_push_env(tkey, tval, envlist)==1) //err시 1
			return (1);
	if (tkey) //
		free(tkey); //
	if (tval) //
		free(tval); //
	return (0);
}

int	ft_valid(char *str, char key)
{
	if (ft_isalpha(*str) == 0)
	{
		if (key==0)
			write(2,"unset: `",8);
		else
			write(2,"export: `",9);
		if (*str)
			write(2,str,ft_strlen(str));
		print_error("': not a valid identifier\n", 1);
		return (0);
	}
	str++;
	while (*str && *str != key)
	{
		if (ft_isalnum(*str) == 0)
		{
			if (key)
				write(2,"export: `",9);
			else
				write(2,"unset: `",8);
			if (*str)
				write(2, str,ft_strlen(str));
			print_error("': not a valid identifier\n", 1);
			return (0);
		}
		str++;
	}
	return (1);
}

char	*ft_echk(char *st,int *sz_ek, char *str, char **tkey) //NULL주는 경우 실실패  처처리
{
	st = str; //echk의 값을 바꿔야하며, return 은 st를 해야한다
	while (*st)
	{
		sz_ek[0]++;
		if (*st == '=')
		{
			(*tkey) = calloc(sz_ek[0], sizeof(char)); //size
			if (!(*tkey))//
				return (NULL);//
			strlcpy((*tkey), str, sz_ek[0]); //size
			sz_ek[1] = 1;
		}
		st++;
		if (sz_ek[1]) //(echk)
			break ;
	}
	return (st);
}

int	ft_ex_util2(t_envlist *envlist, t_cmdnode *curr)
{
	char		*st; //st도 필요없음
	char		*tkey; //마찬가지
	char		*tval; //필요없어짐
	int			sz_ek[2];  //[0]==sz [1] = echk

	sz_ek[0] = 0; ///par_mdata, curr,
	sz_ek[1] = 0;
	st = ft_echk(st, sz_ek, curr->str, &tkey);
	if (!st)//!st >> 원본
		return (1);
	sz_ek[0] = strlen(st);//size
	tval = NULL;
	if (sz_ek[1]) //echk
	{
		tval = calloc(sz_ek[0] + 1, sizeof(char));//size
		if (!tval)
			return (1);
		strlcpy(tval, st, sz_ek[0] + 1);//size
	}
	else
	{
		sz_ek[0] = strlen(curr->str);//size
		tkey = calloc(sz_ek[0] + 1, sizeof(char));//size
		if (!tkey)
			return (1);
		strlcpy(tkey, curr->str, sz_ek[0] + 1);//size
	}
	return (ft_ex_util(tkey, tval, envlist));
}

void	ft_export(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*curr;

	g_data.exit_code = 0;
	curr = cmdlist->head->next;
	if (cmdlist->datasize == 1)
	{
		ft_env(envlist, 1);
		return ;
	}
	curr = curr->next;
	while (curr->next)
	{
		if (ft_valid(curr->str, '=') == 0)
		{
			curr = curr->next;
			continue ;
		}
		if (ft_ex_util2(envlist, curr))
			print_error("insufficient memory", 1);
		curr = curr->next;
	}
}





///////
	///////test ft_export
	// test = par_mdata->envlist->head->next;
	// while(test->next)
	// {
	// 	printf("%s=%s\n",test->key,test->val);
	// 	test=test->next;
	// }
	// printf("\n--------cmd--------\n\n");
	// printf("input: %s\n\n", par_mdata->origin);
	// t_cmdnode *test2;
	// test2 = par_mdata->cmdlist->head->next;
	// while(test2->next)
	// {
	// 	printf("%s\n",test2->str);
	// 	test2=test2->next;
