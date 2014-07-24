/*
 * =====================================================================================
 *
 *       Filename:  functions.c
 *
 *    Description:  functions defination of project myshell
 *
 *        Version:  1.0
 *        Created:  2014年07月24日 13时14分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  pupengfei, 792570367@qq.com
 *        Company:  NONE
 *
 * =====================================================================================
 */

#include "declaration.h"

void input_cmd(char cmd[])//获取命令函数
{
  int i = 0;
  while(i < 256)
  {
    cmd[i++] = getchar();
    if ((cmd[i-1] == '\n') || i == 256)
    {
      i--;
      break;
    }
  }
  cmd[i] = '\0';
}

void get_cmd(char cmd[],char command[25][256])//解析命令函数,解析后存在command里面
{
  int i = 0,j = 0,k = 0;
  while (cmd[j++] == ' ' && strlen(cmd) > j);
  j--;
  while (j < strlen(cmd))
  {
    if (cmd[j++] != ' ')
    {
      command[i][k++] = cmd[j - 1];
      continue;
    }
    else
    {
      command[i][k] = '\0';
      i++;
      k = 0;
      continue;
    }
  }
  command[i + 1][0] = '\0';
}