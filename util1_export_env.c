/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_export_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:08:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/19 12:25:41 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_env(t_envlist *envlist, int b)
{
	t_envnode	*curr;
	t_envnode	*temp;

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

void	ft_push_env(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*new;
	t_envnode	*prev;

	new = ft_newenv();
	new->key = strdup(tkey);
	if (tval)
		new->val = strdup(tval);
	prev = envlist->tail->prev;
	new->next = envlist->tail;
	new->prev = prev;
	prev->next = new;
	envlist->tail->prev = new;
	envlist->datasize++;
}

int	ft_findenv(char *tkey, char *tval, t_par_mdata *par_mdata)
{
	t_envnode	*curr;
	size_t		size;

	curr = par_mdata->envlist->head->next;
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

int	ft_ex_util(char *tkey, char *tval, t_par_mdata *par_mdata)
{
	t_envnode	*prev_tail;

	if (!tkey) //key가 없는 경우 >>> err msg를 띄워야 함
	{
		if (tval) //
			free(tval); //
		return (0); //free를 해주는건 그 전단에서 해주니 문제없을것 같긴하다/////
	}
	else
	{
		if (ft_findenv(tkey, tval, par_mdata) == 0)
			ft_push_env(tkey, tval, par_mdata->envlist);
	}
	if (tkey) //
		free(tkey); //
	if (tval) //
		free(tval); //
	return (1);
}

int	ft_valid(char *str, char key)
{
	if (ft_isalpha(*str) == 0)
	{
		printf("첫문자\n");//
		return (0);
	}
	str++;
	while (*str && *str != key)
	{
		if (ft_isalnum(*str) == 0)
		{
			printf("key:::\n");//
			return (0);///오류
		}
		str++;
	}
	return (1);
}

char	*ft_echk(char *st,int *sz_ek, char *str, char **tkey)
{
	st = str; //echk의 값을 바꿔야하며, return 은 st를 해야한다
	while (*st)
	{
		sz_ek[0]++;
		if (*st == '=')
		{
			(*tkey) = calloc(sz_ek[0], sizeof(char)); //size
			strlcpy((*tkey), str, sz_ek[0]); //size
			sz_ek[1] = 1;
		}
		st++;
		if (sz_ek[1]) //(echk)
			break ;
	}
	return (st);
}

void	ft_ex_util2(t_par_mdata *par_mdata, t_cmdnode *curr)
{
	char		*st; //st도 필요없음
	char		*tkey; //마찬가지
	char		*tval; //필요없어짐
	int			sz_ek[2];  //[0]==sz [1] = echk

	sz_ek[0] = 0; ///par_mdata, curr,
	sz_ek[1] = 0;
	st = ft_echk(st, sz_ek, curr->str, &tkey);
	sz_ek[0] = strlen(st);//size
	tval = NULL;
	if (sz_ek[1]) //echk
	{
		tval = calloc(sz_ek[0] + 1, sizeof(char));//size
		strlcpy(tval, st, sz_ek[0] + 1);//size
	}
	else
	{
		sz_ek[0] = strlen(curr->str);//size
		tkey = calloc(sz_ek[0] + 1, sizeof(char));//size
		strlcpy(tkey, curr->str, sz_ek[0] + 1);//size
	}
	ft_ex_util(tkey, tval, par_mdata);//echk->삭제 가능해서 지움..
}

void	ft_export(t_par_mdata *par_mdata)
{
	t_cmdnode	*curr;

	curr = par_mdata->cmdlist->head->next;
	if (par_mdata->cmdlist->datasize == 1)
	{
		ft_env(par_mdata->envlist, 1);
		return ;
	}
	curr = curr->next;
	while (curr->next)
	{
		if (ft_valid(curr->str, '=') == 0)
		{
			///error 출력 후
			curr = curr->next;
			continue ;
		}
		ft_ex_util2(par_mdata, curr);
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