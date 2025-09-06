/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:02 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 15:38:16 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

static int	ft_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

double	ft_strtod(char *in, int *flag)
{
	double	out;
	int		sign;
	int		decimals;

	out = 0.0;
	sign = 1;
	decimals = 1;
	while (ft_isspace(*in))
		in++;
	if (*in == '-')
		sign = -1;
	if (*in == '+' || *in == '-')
		in++;
	while (ft_isnum(*in))
		out = out * 10 + (*in++ - '0');
	if (*in == '.')
		in++;
	while (ft_isnum(*in))
	{
		out = out * 10 + (*in++ - '0');
		decimals *= 10;
	}
	if (*in)
		*flag = 1;
	return ((out / decimals) * sign);
}
