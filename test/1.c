#include <stdio.h>
#include <stdarg.h>

void foo(char *fmt, ...)
{
	va_list ap;
	int d;
	char c, *s;
	char p;
	va_start(ap, fmt);
	while (*fmt)
		switch (*fmt++) {
			case 's':              /* string */
				s = va_arg(ap, char *);
				printf("%s", s);
				break;
			case 'd':              /* int */
				d = va_arg(ap, int);
				printf("%d", d);
				break;
			case 'c':              /* char */
				c = (char) va_arg(ap, int);
				printf("%c", c);
				break;
			case 'p':              /* char */
				p = (char) va_arg(ap, int);
				printf("%p", p);
				break;
		}
	va_end(ap);
}
int main()
{

	int a =6;
	char b = 'm';
	char * s =  "test";
	foo("%25s %d %c %p\n",s,a,b,a);
	return 0;
}
