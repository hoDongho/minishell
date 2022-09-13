#include "minishell.h"

void	ft_env(t_envlist *envlist, int b) //ft_env(par_mdata->envlist, 0) env로 명령어가 확실하면 이렇게 호출한다.
{
	t_envnode	*curr;
	t_envnode	*temp;

	curr = envlist->head->next;
	while(curr->next)
	{
		if (b && curr->key == "_")
		{
			curr = curr->next;
			continue;
		}
		printf("%s=%s\n", curr->key, curr->val);
		curr = curr->next;
	}
}

void	ft_export(t_par_mdata *par_mdata) //cmd도 필요함 =의 유무를 그냥 체크하고 분기처리하는게 맞아보인다
{
	t_cmdnode	*curr;

	curr = par_mdata->cmdlist->head->next;
	if (par_mdata->cmdlist->tail->prev == curr)
	{
		ft_env(par_mdata->envlist, 1); //env에서 분기처리
		return ;
	}
	while(curr->next)
	{

	}
}

///export a=b=c >>> a="b=c" 최초의 =만 찾는것.
///export a =c >> a저장, =c에선 key 없음으로 오류메시지 띄우고 저장하지 않음
///export a= c >> a에 빈문자열 저장, c는 c만 저장
///export를 그냥할 것이 아니라, 기존에 저장해둔 환경변수 내에서 찾은 다음 덮어쓸지, 새로 만들지를 결정해야한다.
///x=10 > export x하면 나와야함.... 이건 어떻게???