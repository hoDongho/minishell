/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:53:55 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 12:22:20 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_standard(char *st)
{
	// int		dchk;
	int		schk;
	int		standard;

	standard = 0;
	// dchk = 0;
	schk = 0;
	while (*st)
	{
		if ((*st == '\'' || *st == '\"') && standard == 0)
		{
			if (*st == '\'')
				standard = QUOTE;
			else if (*st == '\"')
				standard = D_QUOTE;
		}
		if ((*st == '\'' && standard == QUOTE)
			|| (*st == '\"' && standard == D_QUOTE))
		{
			schk++;
			if (schk % 2 == 0)
				standard = 0;
		}
		// else if (*st == '\"' && standard == D_QUOTE)
		// {
		// 	dchk++;
		// 	if (dchk % 2 == 0)
		// 		standard = 0;
		// }
		st++;
	}
	return (standard);
}

int	ft_checkq(char *str)
{
	int	standard;

	standard = ft_check_standard(str);
	if (standard == QUOTE)
	{
		print_error("syntax error near unexpected token `\''\n", 258);
		return (1);
	}
	else if (standard == D_QUOTE)
	{
		print_error("syntax error near unexpected token `\"'\n", 258);
		return (2);
	}
	return (0);
}

int	ft_syntax_redir(t_cmdnode *curr)
{
	if (!curr->next->str)
	{
		print_error("syntax error near unexpected token `newline'\n",
			258);
		return (1);
	}
	else if (ft_is_redir(curr->next->str) || curr->next->str[0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(curr->next->str, 2);
		print_error("'\n", 258);
		return (1);
	}
	return (0);
}

int	ft_syntax_pipe(t_cmdnode *curr)
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
	return (0);
}

int	ft_check_syntax(t_cmdlist *cmdlist)
{
	t_cmdnode	*curr;

	curr = cmdlist->head->next;
	while (curr->next)
	{
		if (ft_is_redir(curr->str) && curr->p_type == 3)
		{
			if (ft_syntax_redir(curr))
				return (1);
		}
		if (curr->str[0] == '|' && curr->p_type == 3)
		{
			if (ft_syntax_pipe(curr))
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}
