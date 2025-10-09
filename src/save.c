#include "fractal.h"

int	save_scene(t_data *data)
{
	char	*stringed_float;
	int		fd;

	stringed_float = calloc(SAVE_PRECISION + 1, 1);
	if (!stringed_float)
		return (EXIT_FAILURE);
	fd = open("saved_scenes", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (!fd)
	{
		free(stringed_float);
		return (EXIT_FAILURE);
	}
	stringed_float = gcvt(data->location.r, SAVE_PRECISION, stringed_float);	
	write(fd, stringed_float, SAVE_PRECISION);
	write(fd, ",", 1);
	stringed_float = gcvt(data->location.i, SAVE_PRECISION, stringed_float);	
	write(fd, stringed_float, SAVE_PRECISION);
	write(fd, ",", 1);
	stringed_float = gcvt(data->scale, SAVE_PRECISION, stringed_float);	
	write(fd, stringed_float, SAVE_PRECISION);
	write(fd, ",\n", 2);

	close(fd);
	

	return (EXIT_SUCCESS);	
}
