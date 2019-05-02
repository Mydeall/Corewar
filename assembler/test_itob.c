#include <stdio.h>
#include <stdlib.h>

void	insert_value(char *str, unsigned int value, int size)
{
	int i;
	
	i = -1;
	while (++i < size)
	{
		*str = value >> (size * 8 - (i + 1) * 8) & 0xFF;
		str++;
	}
}


int main(int ac, char **av)
{
	char *str;
	unsigned int nb;
	int size;

	if (ac < 3)
		return (0);
	nb = (unsigned int)atoi(av[1]);
	size = atoi(av[2]);
	str = (char*)malloc(4);
	insert_value(str, nb, size);
	return (0);
}
