int main(int ac, char **av)
{
	size_t size;
	unsigned int nb = ft_atoi(av[1]);
	int_to_bytes(writer, nb, size);
	return (0);
}
