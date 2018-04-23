/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:16:02 by kprasol           #+#    #+#             */
/*   Updated: 2018/04/23 17:16:04 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		abs(int n)
{
	return ((n < 0) ? (-n) : (n));
}

t_coord	ft_place(t_board *mb, t_piece *mp)
{
	t_coord	res;
	t_coord	imp;
	int		col;
	int		row;
	int		min;

	ft_set_solution(&imp);
	min = mb->col + mb->row;
	row = 0;
	while (row++ < mb->row)
	{
		col = 0;
		while (col++ < mb->col)
		{
			res.x = col;
			res.y = row;
			if (test(mb, mp, &res) && len(res, mb) <= min)
			{
				min = len(res, mb);
				imp.x = col;
				imp.y = row;
			}
		}
	}
	return (imp);
}
