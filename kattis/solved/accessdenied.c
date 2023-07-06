#include <stdio.h>
#include <stdlib.h>

int q;
char const TABLE[] = "etaoinshrdlcumwfgypbvkjxqzETAOINSHRDLCUMWFGYPBVKJXQZ0123456789";
char str[22], *end = str;

void qry()
{
	for (char *ptr = str; ptr != end; ptr++)
		putchar_unlocked(TABLE[(int)*ptr]);
	putchar_unlocked('\n');
	fflush(stdout);

	for (int i = 0; i < 7; i++)
		getchar_unlocked();
	if (getchar_unlocked() == 'G')
		exit(0);
	for (int i = 0; i < 7; i++)
		getchar_unlocked();

	q = 0;
	char c;
	while ((c = (char)getchar_unlocked()) != ' ')
		q = q * 10 + c - '0';

	for (int i = 0; i < 4; i++)
		getchar_unlocked();
}

int main()
{
	do
	{
		end++;
		qry();
	} while (q == 5);

	int x = 14;
	for (char *ptr = str;; x += 9, ptr++)
	{
		while (q == x)
		{
			++*ptr;
			qry();
		}
	}
}
