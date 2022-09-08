/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:54:54 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/08 16:42:29 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list	*ft_newlist(char c)
{
	t_list	*new;

	new = calloc(1, sizeof(t_list));
	if (!new)
		return NULL;
	new->c = c;
	return new;
}

void	ft_push(t_data	*data, char c)
{
	t_list	*tt;
	t_list	*new;

	new = ft_newlist(c);
	data->tail->prev->next = new;
	new->next = data->tail;
	new->prev = data->tail->prev;
	data->tail->prev = new;
	data->datasize++;
}

char	*ft_makeword(t_data	*data)
{
	char	*str;
	char	*st;
	t_list	*curr;
	t_list	*temp;

	st = calloc(data->datasize + 1, sizeof(char)); //null포함
	str = st;
	curr = data->head->next;
	while (curr->next)
	{
		*str = curr->c;
		temp = curr;
		curr = curr->next;
		free(temp);
		data->datasize--;
		str++;
	}
	data->head->next = data->tail;
	data->tail->prev = data->head;
	return (st);
}

char	*ft_chgenv(char *st, t_data *data) //$ "$ "
{
	// char	test[2][1];//
	char	*key;
	int		i;
	// $ // "$"
	// test[0][0] = 'a';//name
	// test[1][0] = 'b';//val
	i = 0;
	st++;
	if (ft_switch(*st) != 3)
	{
		ft_push(data, '$');
		return (st);
	}
	else
	{
		while(ft_switch(st[i]) == 3)
		{
			i++;
		}
		key = calloc(i + 1, sizeof(char));
		memmove(key, st, i);
		if(key[0] == 'a') ///반복문으로 구조체 전체 순회하는거
			ft_push(data, 'b'); /// 여기도 와일문에서 푸시해야함
		st = st + i;
	}
	return (st);
	// while()
}

void	ft_removeq2(char *str, char **strarr, int len, t_data *data)
{
	char	*st;
	int		i;
	int		swit;
	int		cnt;

	//ft_switch()
	i = 0;
	swit = 0;
	st = str;
	cnt = 0;
	while(len > i)
	{
		while(*st)
		{
			if (ft_switch(*st) == 0 && swit == 0)
			{
				st++;
				continue;
			}
			if (ft_switch(*st) == 3)//
			{
				swit = ft_switch(*st);//
				while (*st != 0 && ft_switch(*st) == swit)//
				{
					if (*st == '$')
						st = ft_chgenv(st, data);
					//$를 치환해서 던지는 문자열로 던져주는 함수 //(*st)ㅇㅕ기서 전전진진함함///여기도
					else //
					{
						ft_push(data, *st);//
						st++; //치환 시 st에 증가량에 대한 고려
					}
				}
				swit = 0;//
			}
			else if (ft_switch(*st) == 1 || ft_switch(*st) == 2)//
			{
				swit = ft_switch(*st);//
				st++;//
				while (*st != 0 && ft_switch(*st) != swit)//
				{
					if (swit == 2 && *st == '$')
						st = ft_chgenv(st, data);
					//$를 치환해서 던지는 문자열로 던져주는 함수 //(*st)ㅇㅕ기서 전전진진함함
					//copy  --> f_return /// 밑에서 담을거임
					/////
					else //
					{
						ft_push(data, *st);//
						st++; //치환 시 st에 증가량에 대한 고려
					}
					// ft_push(data, *st);
					//담는 함수 abc > 3 a b c
					//stack.size
					// st++; //치환 시 st에 증가량에 대한
				}
				swit = 0;//
				st++;//
			}
			if (ft_switch(*st) == 0)//
				break ;//
			// st++;
		}
		strarr[i] = ft_makeword(data);
		printf("%s\n",strarr[i]);
		i++;
	}
}

// "asdf$aaa asdf"
// "asdf12345 asdf"

//export name=aaa
//		 val=12345

// "asdf$aaa asdf"
// "asdf12345 asdf"





// struct stack_data {
// 	stack;
// 	stack_size;
// }