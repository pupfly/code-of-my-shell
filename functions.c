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

void input_cmd(char cmd[],int *order)//获取命令函数
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
  if (i != 0)
  {
    cmd[i] = '\0';
    *order = 0;
  }
  else
  {
    memset(cmd,0,strlen(cmd));
  }
}

void get_cmd(char cmd[],char *real_command[256])//解析命令函数,解析后存在command里面
{
  if (strlen(cmd) == 0)
  {
    real_command[0] = NULL;
    return;
  }
  int i = 0,j = 0,k = 0;
  char command[256][256];
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
  i = 0;
  while (command[i++][0] != '\0' && i < 256)
	{
	  real_command[i-1] = (char *)command[i-1];
	}
	real_command[i - 1] = NULL;
}

int search_cmd(char* command[256])//查找命令函数
{
  if (command[0] == NULL)
  {
    return;
  }
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
  if (command[0] == NULL)
  {
    return;
  }
  int flag = 0,flag_of_back = 0;
  int i = -1;
  int num_of_in = 0,num_of_out = 0,num_of_pipe = 0;
  
  while(command[++i] != NULL)
  {
    if (command[i][0] == '<')
    {
      num_of_in++;
    }
    else if (command[i][0] == '>')
    {
      num_of_out++;
    }
    else if (command[i][0] == '|')
    {
      num_of_pipe++;
    }
  }
  
  if (command[i - 1][0] == '&')
  {
    flag_of_back = 1;
  }
    if (num_of_in > 1 || num_of_out > 1 || num_of_pipe > 1 || (num_of_in + num_of_out + num_of_pipe) > 1)
    {
      printf("命令格式错误\n");
      return ;
    }
    
    if (num_of_in)
    {
      flag = 1;//含有输入重定向命令
    }
    else if (num_of_out)
    {
      flag = 2;//含有输出重定向命令
    }
    else if (num_of_pipe)
    {
      flag = 3;//含有管道命令
    }
  int state;
  pid_t pid;
  pid_t pid2;
  pid = fork();
  wait(&state);
    switch(flag)
    {
      case 0:
	if (pid == 0)
	{
	  if (search_cmd(command))	
	  {
	    execvp(command[0],command);
	  }
	  else
	  {
	    printf("未找到命令:%s\n",command[0]);
	    _exit(0);
	  }
	}
	break;
      case 1:
	if (pid == 0)
	{
	   char *file;
	   i = 0;
	   while (command[i++][0] != '<');
	   if (command[i - 1][1] == '\0')
	   {
	      file = command[i];
	      command[i - 1] = NULL;
	   }
	   else
	    {
	      printf("命令格式错误\n");
	      _exit(0);
	    }
	   if (search_cmd(command))	
	   {
	      int fd;
	      fd = open(file,O_RDONLY);
	      dup2(fd ,0);
	      if (execvp(command[0],command) == -1)
	      {
		printf("未找到命令:%s\n",command[0]);
		_exit(0);
	      }
	      _exit(0);
	   }
	    else
	    {
	      printf("未找到命令:%s\n",command[0]);
	      _exit(0);
	    }
	  }
	  break;
      case 2:
	if (pid == 0)
	{
		char *file;
	   i = 0;
	   while (command[i++][0] != '>');
	   if (command[i - 1][1] == '\0')
	   {
	      file = command[i];
	      command[i - 1] = NULL;
	   }
	   else
	    {
	      printf("命令格式错误\n");
	      _exit(0);
	    }
	  if (search_cmd(command))	
	  {
	    int fd;
	    fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
	    dup2(fd ,1);
	    if (execvp(command[0],command) == -1)
	      {
		printf("未找到命令:%s\n",command[0]);
		_exit(0);
	      }
	     _exit(0);
	  }
	  else
	  {
	    printf("未找到命令:%s\n",command[0]);
	    _exit(0);
	  }
	}
	break;
      case 3:
	if (pid == 0)
	{
	   i = 0;
	   int fd2,t1,t2;
	   char *cmd[256];
	   
	   if ((pid2 = fork()) < 0)
	   {
		printf("创建子进程失败!\n");
		exit(0);
	   }
	   while (command[i++][0] != '|');
	   t1 = i - 1;
	   t2 = i;
	  if (command[i - 1][1] != '\0')//命令合适则提取和分离命令
	   {
	     printf("命令格式错误\n");
	     exit(0);
	  }
	  /*command[t] = NULL;
	  t = 0;
	  while(command[t] != NULL)
	    puts(command[t++]);
	  t = 0;
	  while (cmd[t] != NULL)
	    puts(cmd[t]);*/
	  if (pid2 == 0)
	  {
	      command[t1] = NULL;
	      fd2 = open("/tmp/tempfileformyshell",O_WRONLY|O_CREAT|O_TRUNC,0644);
	      dup2(fd2,1);
	      if (search_cmd(command))
	      {
			execvp(command[0],command);
			exit(0);
	      }
	      else
	      {
			printf("命令不存在\n");
			exit(0);
	      }
	  }
	  if (waitpid(pid2,&state,0) == -1)
	  {
	    printf("wait for pid2 error\n");
	  }
	  command += t2;
	  fd2 = open("/tmp/tempfileformyshell",O_RDONLY);
	  dup2(fd2,0);
	  if (search_cmd(command))
	  {
	    if (execvp(command[0],command) == -1 && pid2 == 0)
	    {
	      printf("命令格式错误\n");
	      _exit(0);
	    }
	  }
	  if (remove("/tmp/tempfileformyshell") != 0)
	  {
	    printf("remove temp file error\n");
	  }
	  exit(0);
	}
	break;
	default:break;
    }
    if (flag_of_back == 1)
    {
      printf("[process id %d] running\n",pid);
      return ;
    }
}

void destroy_cmd(char* command[256])//销毁命令函数
{
  int i = 0,j = 0;
  while(command[i++] != NULL)
  {
    memset(command[i - 1],0,strlen(command[i - 1]));
  }
}