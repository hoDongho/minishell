// echo 테스트
echo $?
echo $?
echo ??
echo ?
echo $??
echo $USERname
echo $USER name
echo "$USER na"me
echo '$USER na'me
echo "$$USER"
echo hi$USER
echo hi"$USER"
echo $USEEER
echo ?$USER
echo hell"o"" "from " 42"
echo "$USER ?"

// ls 테스트
ls
ls -l
ls -al

// quit, 반환값 테스트
./minishell
quit 113
echo $?
wrongcmd
echo $?
ls
echo $?

// 잡다하게 섞은거
< infile cat
< infile cat | grep a
< infile cat | grep a | wc
< infile cat | grep a | wc -l
cat < infile

// 환경변수, export, unset
env
env | grep SHLVL
./minishell
env | grep SHLVL -> SHLVL 값 바껴야됨.
export a=b b=c c=d
export a=aa b=cc
export A=B B=C
unset a
unset b c A B

// cd
cd ~
cd
cd -
echo $OLDPWD -> OLDPWD가 변경되야됨.

// ctrl + [d, c, \] 테스트

// pwd 테스트
pwd

// heredoc + append
<< eof cat >> infile -> infile 뒤에 추가됨


by donpark, joonpark :)
