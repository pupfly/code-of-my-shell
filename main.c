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
	int order = 1;
	while (1)
	{
	  char *command[256];
	  char cmd[256];
	  while(order == 1)
	  {
	    print_tip();
	    input_cmd(cmd,&order);
	  }
	  get_cmd(cmd,command);
	  if (strcmp(command[0],"exit") == 0 || strcmp(command[0],"logout") == 0)
	  {
	    break;
	  }
	 // execvp(command[0],command);
	  executive_cmd(command);
	  //input_cmd(cmd);
	  //get_cmd(cmd,command);
	  destroy_cmd(command);
	  order = 1;
	}
	/*pid_t pid;
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
	}*/
}

