/*
 * =====================================================================================
 *
 *       Filename:  declaration.h
 *
 *    Description:  declarations of shell program
 *
 *        Version:  1.0
 *        Created:  2014年07月24日 09时15分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  pupengfei, 792570367@qq.com
 *        Company:  NONE
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

void print_tip();//输出shell名

void input_cmd(char cmd[],int *);//获取命令函数

void get_cmd(char cmd[],char *real_command[256]);//解析命令函数,解析后存在command里面

int search_cmd(char* command[256]);//查找命令函数

void executive_cmd(char* command[256]);//执行获取的命令

void destroy_cmd(char* command[256]);//销毁命令函数
