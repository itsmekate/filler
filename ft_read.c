/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:19:53 by kprasol           #+#    #+#             */
/*   Updated: 2018/04/19 21:02:59 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_cut_left_more(t_piece *mp)
{
	int row;
	int col;

	row = 0;
	if (mp->cut_left > 0)
	{
		while (row < mp->row)
		{
			col = 0;
			while (col < mp->col - mp->cut_left)
			{
				mp->piece[row][col] = mp->piece[row][col + mp->cut_left];
				mp->piece[row][col + mp->cut_left] = '.';
				col++;
			}
			row++;
		}
		mp->col -= mp->cut_left;
	}
}

void	ft_cut_left(t_piece *my_piece)
{
	t_coord	n;

	ft_set_solution(&n);
	ft_cut_left_even_more(my_piece, n);
	ft_cut_left_more(my_piece);
}

void	ft_piece(t_piece *my_piece)
{
	char	**c;
	char	*map;

	my_piece->cut_top = 0;
	my_piece->cut_left = 0;
	get_next_line(0, &map);
	c = ft_strsplit(map, ' ');
	if (ft_strstr(map, "Piece"))
	{
		my_piece->row = ft_atoi(c[1]);
		my_piece->col = ft_atoi(c[2]);
	}
	my_piece->piece = (char**)malloc(sizeof(char*) * my_piece->row);
}

void	ft_read_p(t_board *my_board, t_coord *solution)
{
	char			*map;

	get_next_line(0, &map);
	map = ft_strstr(map, "p");
	map++;
	my_board->player = ft_atoi(map);
	ft_set_solution(solution);
}

int		main(void)
{
	int		i;
	t_board	my_board;
	t_piece	my_piece;
	t_coord	solution;

	i = 1;
	ft_read_p(&my_board, &solution);
	while (1)
	{
		ft_write_board(&my_board, i++);
		ft_write_piece(&my_piece);
		solution = ft_place(&my_board, &my_piece);
		if (solution.x == 0 && solution.y == 0)
		{
			ft_putstr("0 0\n");
			break ;
		}
		(my_piece.cut_top != 0) ? (solution.y -= my_piece.cut_top) : 0;
		(my_piece.cut_left != 0) ? (solution.x -= my_piece.cut_left) : 0;
		ft_putnbr(solution.y);
		write(1, " ", 1);
		ft_putnbr(solution.x);
		write(1, "\n", 1);
	}
	return (1);
}
