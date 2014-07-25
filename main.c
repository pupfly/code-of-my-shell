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
	int order = 1;//如果输入命令为空,以此数标志状态让用户继续输入
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
	  executive_cmd(command);
	  destroy_cmd(command);
	  order = 1;
	}
}

