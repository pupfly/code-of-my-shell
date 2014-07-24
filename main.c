/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年07月24日 11时35分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  pupengfei, 792570367@qq.com
 *        Company:  NONE
 *
 * =====================================================================================
 */

#include "declaration.h"
int main()
{
	print_tip();
	char argv[25][256];
	char *command[25];
	char cmd[256];
	int i=0;
	input_cmd(cmd);
	puts(cmd);
	get_cmd(cmd,argv);
	
	while (argv[i++][0] != '\0' && i < 25)
	{
	  command[i-1] = (char *)argv[i-1];
	}
	command[i] = NULL;
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		//char* parameter[] = {"ls",0};
		printf("child process running\n");
		if (search_cmd(command))
		  execvp(command[0],command);
		else
		  printf("未找到命令:%s\n",command[0]);
	}
	else
	{
		wait(&i);
		printf("main function run here\n");
	}
}

