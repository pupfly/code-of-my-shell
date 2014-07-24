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

void print_tip()
{
  printf("My shell running>>:");
}

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

void get_cmd(char cmd[],char command[256][256])//解析命令函数,解析后存在command里面
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

int search_cmd(char* command[256])//查找命令函数
{
  DIR *dir;
  struct dirent *temp;
  if (strncmp(command[0],"./",2) != 0)
  {
	  char *path[] = {"/bin","/usr/bin"};
    if ((dir = opendir(path[0])) == NULL)
    {
      perror("opendir");
      return 0;
    }
    while((temp = readdir(dir)) != NULL)
    {
      if (strcmp(temp->d_name,command[0]) == 0)
      {
		closedir(dir);
		return 1;
      }
    }
    closedir(dir);
    if ((dir = opendir(path[1])) == NULL)
    {
      perror("opendir");
      return 0;
    }
    while ((temp = readdir(dir)) != NULL)
    {
      if (strcmp(temp->d_name,command[0]) == 0)
      {
		closedir(dir);
		return 1;
      }
    }
  closedir(dir);
  return 0;
  }
  else if (strncmp(command[0],"./",2) == 0)
  {
    char filename[strlen(command[0])];
    int i = 1;
    while(command[0][i++] != '\0')
    {
      filename[i-2]=command[0][i];
    }
    puts(filename);
    if ((dir = opendir("./")) == NULL)
    {
      perror("opendir");
      return 0;
    }
    while ((temp = readdir(dir)) != NULL)
    {
      if (strcmp(temp->d_name,filename) == 0)
      {
		closedir(dir);
		return 1;
      }
    }
    closedir(dir);
    return 0;
  }
}
void executive_cmd(char* command[256])//执行获取的命令
{
  
}
