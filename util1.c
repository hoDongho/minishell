#include "minishell.h"

void	ft_env(t_envlist *envlist, int b)
{
	t_envnode	*curr;
	t_envnode	*temp;

	curr = envlist->head->next;
	while(curr->next)
	{
		if (b && strcmp(curr->key,"_")==0)
		{
			curr = curr->next;
			continue;
		}
		if (curr->val)
			printf("%s=%s\n", curr->key, curr->val);
		else
			if(b)
				printf("%s\n", curr->key);
		curr = curr->next;
	}
}

void	ft_push_env(char *tkey, char *tval, t_par_mdata *par_mdata)
{
	t_envnode	*new;
	t_envnode	*prev;

	new = ft_newenv();
	new->key = strdup(tkey);
	if (tval)
		new->val = strdup(tval);
	prev = par_mdata->envlist->tail->prev;
	new->next = par_mdata->envlist->tail;
	new->prev = prev;
	prev->next = new;
	par_mdata->envlist->tail->prev = new;
	par_mdata->envlist->datasize++;
}


int	ft_findenv(char *tkey, char *tval, t_par_mdata *par_mdata)
{
	t_envnode	*curr;
	size_t		size;

	curr = par_mdata->envlist->head->next;
	while(curr->next)
	{
		size = strlen(tkey);
		if (strcmp(tkey, curr->key) == 0)
		{
			if (tval)
			{
				free(curr->val);
				curr->val = strdup(tval);
			}
			return (1);
		}
		curr=curr->next;
	}
	return (0);
}

int	ft_ex_util(char *tkey, char *tval, int echk, t_par_mdata *par_mdata)
{
	t_envnode	*prev_tail;

	if (!tkey) //key가 없는 경우 >>> err msg를 띄워야 함
	{
		return (0); //free를 해주는건 그 전단에서 해주니 문제없을것 같긴하다/////
	}
	else
	{
		if(ft_findenv(tkey, tval, par_mdata) == 0)
			ft_push_env(tkey, tval, par_mdata);
	}
	return (1);
}

int	ft_valid(char *str, char key)
{
	if (ft_isalpha(*str)==0)
	{
		printf("첫문자\n");//
		return (0);
	}
	str++;
	while(*str && *str!=key)
	{
		if (ft_isalnum(*str)==0)
		{
			printf("key:::\n");//
			return (0);///오류
		}
		str++;
	}
	return (1);
}


void	ft_export(t_par_mdata *par_mdata)
{
	t_cmdnode	*curr;
	char		*st;
	char		*tkey;
	char		*tval;
	int			echk;
	int			size;
	t_envnode	*test;//test
	char		*tempstr;

	curr = par_mdata->cmdlist->head->next;
	if (par_mdata->cmdlist->datasize == 1)
	{
		ft_env(par_mdata->envlist, 1);
		return ;
	}
	curr = curr->next;
	while(curr->next)
	{
		if (ft_valid(curr->str,'=')==0)
		{
			///error 출력 후
			curr = curr->next;
			continue;
		}
		echk = 0;
		size = 0;
		st = curr->str;
		while(*st)
		{
			size++;
			if (*st=='=')
			{
				tkey = calloc(size, sizeof(char));
				strlcpy(tkey, curr->str, size);
				echk = 1;
			}
			st++;
			if (echk)
				break;
		}
		size = strlen(st);
		tval = NULL;
		if (echk)
		{
			tval = calloc(size + 1, sizeof(char));
			strlcpy(tval, st, size+1);
		}
		else
		{
			size = strlen(curr->str);
			tkey = calloc(size + 1, sizeof(char));
			strlcpy(tkey, curr->str, size + 1);
		}
		ft_ex_util(tkey, tval, echk, par_mdata);
		if (tkey)
			free(tkey);
		if (tval)
			free(tval);
		curr = curr->next;
	}
	///////test
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
	// }
}

///export a=b=c >>> a="b=c" 최초의 =만 찾는것.

///export a= c >> a에 빈문자열 저장, c는 c만 저장
///export를 그냥할 것이 아니라, 기존에 저장해둔 환경변수 내에서 찾은 다음 덮어쓸지, 새로 만들지를 결정해야한다.
///export x=10 한 뒤에 export x 이렇게해도 값을 유지하는게 현재.
///export "기존에 있는 변수"=0 등 실험
///export x=a >>> 이런식으로 1개 단위에서 이슈 없는지 확인해야함
///export b==c
///export a >>> export a=123

///1. =의 존재를 찾는다? 리스트 자체에는 띄어쓰기는 포함되지 않고 전달되므로 붙어있는 것 중에서 찾는 셈.
///2. =전까지를 저장하고 있을 필요가 있겠다. (split이든 리스트이든) =을 만나거나 \0까지가 key인 셈이다.
///3. 2에 의해서 case가 나


//as-is
///export a =c >> a저장, =c에선 key 없음으로 오류메시지 띄우고 저장하지 않음 |||| ing

//export 1234 		x >>> 맨 앞에 숫자면 안된다.
//export "a =c"		x
//export "'a'=c"	x
//export "a    =c"	x >>> 힌트 =의 전을 기점으로 한다면?

//unset의 경우에 없는key 를 찾으면 그냥 무시됌. 에러처리는 없음.


///0. key의 첫 문자는 반드시 문자 ft_swit --> 3값 해당 isalpha >>> 그 다음부터는 isalnum을 돌린다.(_포함해서 개량)
///1. 인자에 해당되는  건 무조건 문자
///2.
///3.