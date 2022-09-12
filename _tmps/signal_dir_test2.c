// #include <stdio.h>
// #include <unistd.h>
// #include <signal.h>

// void (*old_fun)( int);

// void sigint_handler( int signo)
// {
//    printf( "Ctrl-C 키를 눌루셨죠!!\n");
//    printf( "또 누르시면 종료됩니다.\n");
//    signal( SIGINT, old_fun);   // 또는 signal( SIGINT, SIG_DFL);
// }

// int main( void)
// {
//    old_fun = signal( SIGINT, sigint_handler);
//    while(1){
//       printf( "dhyun\n");
//       sleep( 1);
//    }
// } signal test

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int main()
{
   char buff[1024];

   mkdir( "test_A"     , 0755);           // 실행 파일이 있는 곳에 생성
   chdir( "-");                    // 작업 디렉토리를 변경
   getcwd( buff, 1024);                   // 작업 디렉토리 구하기
   printf( "작업 디렉토리: %s\n", buff);
   system("pwd");
   // while(1)
   //    printf( "작업 디렉토리: %s\n", buff);
}
