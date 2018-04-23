/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addditional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:41:37 by kprasol           #+#    #+#             */
/*   Updated: 2018/04/22 20:41:38 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_write_board(t_board *my_board, int check)
{
	char	**c;
	char	*map;
	char	*temp;
	int		i;

	i = 0;
	if (check == 1)
	{
		get_next_line(0, &map);
		c = ft_strsplit(map, ' ');
		my_board->row = ft_atoi(c[1]);
		my_board->col = ft_atoi(c[2]);
	}
	else
		get_next_line(0, &map);
	my_board->board = (char**)malloc(sizeof(char*) * my_board->row);
	get_next_line(0, &temp);
	while (i < my_board->row)
	{
		my_board->board[i] = (char*)malloc(sizeof(char) * my_board->col);
		get_next_line(0, &temp);
		my_board->board[i] = temp + 4;
		i++;
	}
}

void	ft_set_solution(t_coord *solution)
{
	solution->x = 0;
	solution->y = 0;
}

void	ft_norm(t_coord *c, t_coord *f, t_piece *mp)
{
	ft_set_solution(c);
	ft_set_solution(f);
	ft_piece(mp);
}

void	ft_write_piece(t_piece *mp)
{
	t_coord	count;
	t_coord	f_cb;
	char	*tmp;

	ft_norm(&count, &f_cb, mp);
	while (count.y < mp->row && get_next_line(0, &tmp))
	{
		(ft_strchr(tmp, '*')) ? (f_cb.x = 1) : 0;
		(!ft_strchr(tmp, '*') && !f_cb.x) ? (mp->cut_top++) : 0;
		if (f_cb.x && ft_strchr(tmp, '*'))
		{
			mp->piece[count.x] = (char *)malloc(sizeof(char) * mp->col);
			mp->piece[count.x] = tmp;
			count.x++;
		}
		if (f_cb.x == 1 && !ft_strchr(tmp, '*'))
		{
			f_cb.y++;
			count.x++;
		}
		count.y++;
	}
	mp->row -= mp->cut_top;
	mp->row -= f_cb.y;
	ft_cut_left(mp);
}

void	ft_cut_left_even_more(t_piece *mp, t_coord n)
{
	int	flag;
	int	count;

	flag = 0;
	while (n.x < mp->col)
	{
		if (flag == 1)
			break ;
		n.y = 0;
		count = 0;
		while (n.y < mp->row)
		{
			if (mp->piece[n.y][n.x] == '*')
			{
				flag = 1;
				n.x++;
				break ;
			}
			else
				count++;
			n.y++;
		}
		(count == mp->row) ? (mp->cut_left++) : 0;
		n.x++;
	}
}
