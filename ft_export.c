/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:08:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/30 18:35:39 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_val_first(char *str, char key)
{
	if (ft_isalpha(*str) == 0)
	{
		if (key == 0)
			write(2, "unset: `", 8);
		else
			write(2, "export: `", 9);
		if (*str)
			write(2, str, ft_strlen(str));
		print_error("': not a valid identifier\n", 1);
		return (0);
	}
	return (1);
}

int	ft_valid(char *str, char key)
{
	char	*st;

	st = str;
	if (ft_val_first(str, key) == 0)
		return (0);
	str++;
	while (*str && *str != key)
	{
		if (ft_isalnum(*str) == 0)
		{
			if (key)
				write(2, "export: `", 9);
			else
				write(2, "unset: `", 8);
			if (*str)
				write(2, st, ft_strlen(st));
			print_error("': not a valid identifier\n", 1);
			return (0);
		}
		str++;
	}
	return (1);
}

char	*ft_echk(char *st, int *echk, char *str, char **tkey)
{
	int	size;

	size = 0;
	st = str;
	while (*st)
	{
		size++;
		if (*st == '=')
		{
			(*tkey) = ft_calloc(size, sizeof(char));
			ft_strlcpy((*tkey), str, size);
			*echk = 1;
		}
		st++;
		if (*echk)
			break ;
	}
	return (st);
}

void	ft_ex_util2(t_envlist *envlist, t_cmdnode *curr)
{
	char		*st;
	char		*tkey;
	char		*tval;
	int			echk;

	echk = 0;
	st = 0;
	st = ft_echk(st, &echk, curr->str, &tkey);
	tval = NULL;
	if (echk)
	{
		tval = ft_calloc(ft_strlen(st) + 1, sizeof(char));
		ft_strlcpy(tval, st, ft_strlen(st) + 1);
	}
	else
	{
		tkey = ft_calloc(ft_strlen(curr->str) + 1, sizeof(char));
		ft_strlcpy(tkey, curr->str, ft_strlen(curr->str) + 1);
	}
	ft_ex_util(tkey, tval, envlist);
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
		ft_ex_util2(envlist, curr);
		curr = curr->next;
	}
}
