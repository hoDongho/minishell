#include "minishell.h"
//int	ft_findenv(char *tkey, char *tval, t_par_mdata *par_mdata)
void	ft_popenv(char *tkey, t_par_mdata *par_mdata) //findenv 개량 수정하는 부분때문에 그대로는 쓸수없음
{
	t_envnode	*curr;
	t_envnode	*next;
	t_envnode	*prev;
	t_envnode	*temp;
	size_t		size;

	curr = par_mdata->envlist->head->next;
	size = strlen(tkey);
	while(curr->next)
	{
		if (ft_strncmp(tkey,curr->key,size)==0) // 같은 문자
		{
			next = curr->next;
			prev = curr->prev;
			prev->next = next;
			next->prev = prev;
			temp = curr;
			curr = curr->next;
			free(temp);
			continue ;
		}
		curr = curr->next; //if를 타고 온 경우에도 다음거로 잘 넘어가는지 논리 전개
	}
}

void	ft_unset(t_par_mdata *par_mdata)
{
	t_cmdnode	*curr;
	curr = par_mdata->cmdlist->head->next;
	if (par_mdata->cmdlist->datasize == 1) //unset만 온  경경우우
		return ;
	curr = curr->next; //unset뒤의 변수명이 되겠따
	while(curr->next)
	{
		if (ft_valid(curr->str, 0)==0) ///export랑 같은 방식으로 받아온다. key검사 부분이 같음
		{
			printf("err unset\n");
			///error 출력 후
			curr = curr->next;
			continue ;
		}
		ft_popenv(curr->str, par_mdata);
		curr = curr->next;
	}
}


///unset a=b
///unset " g"
///위의 두 가지 경우를 보면 유효성 체크를 이전에 해주듯이 해야겠다
