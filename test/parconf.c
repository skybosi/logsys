#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define MAXSIZE 1024
int parse_conf(char *path);		// 解析配置文件
bool isblank(char *str);		// 判断是否为空行
int strpos(char *s, char *a);	// 返回子串在母串的下标
char *del_coment(char *soustr, bool way, char *head, char *tail);	// 删除注释(way为真返回去除注释，为假保留注释部分)

int main(int argc, char *argv[])
{
	/* parse_conf("./sample.conf"); */
	char *test = "/*sfghhghij#vffuuujhhgh=*/ddn";
	char *head = "/*";
	char *tail = "*/";
	char *res;
	res = del_coment(test, 0, head, tail);
	printf("res=%s\n", res);
	 return 0;
}

int parse_conf(char *path)
{
	if (path == NULL)
		return 0;
	FILE *fpi = NULL;
	fpi = fopen(path, "r");
	if (!fpi)
	{
		printf("ERROR");
		exit(0);
	}
	char str[2048];
	char *res;
	fgets(str, sizeof(str) - 1, fpi);
	while (!feof(fpi))
	{
		// printf("str:%s",str);
		if (res = del_coment(str,0, "#", "\n"))
			if (!isblank(res))
				printf("%s", res);
		fgets(str, sizeof(str), fpi);
	}
	fclose(fpi);
	fpi = NULL;
}

int strpos(char *src, char *str)
{
	assert(src && str);
	int ls = 0, la = 0, pos = 0;
	ls = strlen(src);
	la = strlen(str);
	if (la > ls)
		return -1;
	for (pos = 0; pos <= ls - la; pos++)
	{
		if (strncmp(src + pos, str, la) == 0)
			return pos;
	}
}

char *del_coment(char *soustr, bool way, char *head, char *tail)
{
	assert(soustr && head && tail);
	char *str = soustr;
	// printf("test:%s\n", soustr);
	int hpos = strpos(soustr, head);
	// printf("head:%d\n", hpos);
	int tpos = strpos(soustr, tail);
	// printf("tail:%d\n", tpos);
	if (tpos <= hpos)
		return soustr;
	char tmp[MAXSIZE];
	memset(tmp, 0, MAXSIZE);
	if (way)//去除注释(分段的部分做分行处理)
	{
		int i = 0;
		for (int pos = 0; pos < hpos; pos++, i++)
			tmp[i] = str[pos];
		tmp[i++] = '\n';
		for (int pos = tpos + 1; pos < strlen(str); pos++, i++)
			tmp[i] = str[pos];
	}
	else//获取注释(包括注释符号)
	{
		for (int pos = hpos, i = 0; pos < tpos + strlen(tail); pos++, i++)
			tmp[i] = str[pos];
	}
	// printf("tmp:%s\n", tmp);
	// strcpy(soustr, tmp);
	// printf("res=%s\n", soustr);
	return tmp;
}

bool isblank(char *str)//没有可见字符
{
	while (*str)
	{
		if (!isspace(*str++))
			return false;
		else
			continue;
	}
	return true;
}