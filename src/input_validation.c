/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:40:10 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:18:35 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static int	valid_number(char *input);
static int	no_digits(char *str);
static int	within_reason(char *str);
static void	print_and_exit(char *message);

void	validate_inputs(int argc, char **argv)
{
	if (argc < 2)
		print_and_exit(INFO_INSTRUCTION);
	if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		if (argc != 2)
			print_and_exit(INFO_BAD_INPUT);
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		if (argc != 4)
			print_and_exit(INFO_BAD_INPUT);
		if (!within_reason(argv[2]) || !within_reason(argv[3]))
			print_and_exit(INFO_BE_REASONABLE);
		if (!valid_number(argv[2]) || !valid_number(argv[3]))
			print_and_exit(INFO_BAD_NUMBER);
		if (fabs(ft_strtod(argv[2], NULL)) >= 4
			|| fabs(ft_strtod(argv[3], NULL)) >= 4)
			print_and_exit(INFO_LARGE_JULIA);
	}
	else
		print_and_exit(INFO_INSTRUCTION);
}

static void	print_and_exit(char *message)
{
	ft_printf("\n%s\n\n", message);
	exit(1);
}

static int	within_reason(char *str)
{
	return (ft_strlen(str) < REASONABLE_PRECISION);
}

static int	no_digits(char *str)
{
	while ((*str < '0' || '9' < *str) && *str)
		str++;
	return (!*str);
}

static int	valid_number(char *input)
{
	int		flag;

	flag = 0;
	if (!*input || !input || no_digits(input))
		return (0);
	ft_strtod(input, &flag);
	if (flag)
		return (0);
	return (1);
}
