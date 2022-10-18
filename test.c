char *get_next_line(int fd)
{
	char *buffer = malloc(10000), *caractere = buffer;
	while (read(fd,buffer,1) && *caractere++ != '\n');
	return ((caractere > buffer ) ? *(caractere = 0, buffer) : (free(buffer), NULL));

}