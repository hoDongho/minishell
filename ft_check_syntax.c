/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:53:55 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 15:38:52 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkq(char *str)
{
	char	*st;
	int		dchk;
	int		schk;
	int		standard;

	standard = 0; // 1 : single , 2 : double
	st = str;
	dchk = 0;
	schk = 0;
	while (*st)
	{
		if ((*st == '\'' || *st == '\"') && standard == 0)
		{
			if (*st == '\'')
				standard = 1;
			else if (*st == '\"')
				standard = 2;
		}
		if (*st == '\'' && standard == 1)
		{
			schk++;
			if (schk % 2 == 0)
				standard = 0;
		}
		else if (*st == '\"' && standard == 2)
		{
			dchk++;
			if (dchk % 2 == 0)
				standard = 0;
		}
		st++;
	}
	if (standard == 1)
	{
		print_error("syntax error near unexpected token `\''\n", 258);//syntax error near unexpected token `<'
		return (1);
	}
	else if (standard == 2)
	{
		print_error("syntax error near unexpected token `\"'\n", 258);
		return (2);
	}
	return (0);
}

int	ft_check_syntax(t_cmdlist *cmdlist)
{
	t_cmdnode	*curr;

	curr = cmdlist->head->next;
	while(curr->next)
	{
		if (ft_is_redir(curr->str))
		{
			if (!curr->next->str)
			{
				print_error("syntax error near unexpected token `newline'\n", 258);
				return (1);
			}
			else if (ft_is_redir(curr->next->str) || curr->next->str[0] == '|')
			{
				write(2, "syntax error near unexpected token `", 36);
				write(2, curr->next->str, ft_strlen(curr->next->str));
				print_error("'\n", 258);
				return (1);
			}
		}
		if (curr->str[0] == '|')
		{
			if (!curr->next->str)
			{
				print_error("syntax error near unexpected token `|'\n", 258);
				return (1);
			}
			if (!curr->prev->str)
			{
				print_error("syntax error near unexpected token `|'\n", 258);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}