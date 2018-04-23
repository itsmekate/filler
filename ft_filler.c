/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:31:17 by kprasol           #+#    #+#             */
/*   Updated: 2018/04/16 17:32:31 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			ft_more(t_board *mb, char *p, char *e)
{
	(mb->player == 2) ? (*e = 'O') : 0;
	(mb->player == 1) ? (*e = 'X') : 0;
	(mb->player == 1) ? (*p = 'O') : 0;
	(mb->player == 2) ? (*p = 'X') : 0;
}

int				lovenorm(t_norm norm, t_coord bc, t_coord pc, t_coord *r)
{
	while (bc.y < norm.b.row && pc.x < norm.p.row)
	{
		bc.x = r->x;
		pc.y = 0;
		if (norm.p.col + bc.x > norm.b.col)
			return (0);
		while (bc.x < norm.b.col && pc.y < norm.p.col)
		{
			if ((norm.b.board[bc.y][bc.x] == norm.pl)
				&& (norm.p.piece[pc.x][pc.y] == '*'))
				norm.cross++;
			if (norm.p.piece[pc.x][pc.y] == '*'
				&& norm.b.board[bc.y][bc.x] == norm.en)
				return (0);
			bc.x++;
			pc.y++;
		}
		pc.x++;
		bc.y++;
	}
	return (norm.cross);
}

int				test(t_board *mb, t_piece *mp, t_coord *r)
{
	t_coord	bc;
	t_coord	pc;
	t_norm	norm;

	norm.b = *mb;
	norm.p = *mp;
	norm.cross = 0;
	pc.x = 0;
	ft_more(&norm.b, &norm.pl, &norm.en);
	bc.y = r->y;
	if (norm.p.row + bc.y > norm.b.row)
		return (0);
	norm.cross = lovenorm(norm, bc, pc, r);
	return (norm.cross == 1 ? 1 : 0);
}

void			len_more(t_coord bc, t_board *mb, char enemy, char player)
{
	if (mb->board[bc.y][bc.x] == player)
	{
		while (bc.x < mb->col && mb->board[bc.y][bc.x] != enemy)
			bc.x++;
		while (bc.x < mb->col && mb->board[bc.y][bc.x] == enemy)
			bc.x++;
	}
}

int				len(t_coord res, t_board *mb)
{
	t_coord	bc;
	char	enemy;
	char	player;
	int		min;

	min = mb->col + mb->row;
	ft_more(mb, &player, &enemy);
	bc.y = 0;
	while (bc.y < mb->row)
	{
		bc.x = 0;
		while (bc.x < mb->col)
		{
			len_more(bc, mb, enemy, player);
			if (mb->board[bc.y][bc.x - 1] == enemy
				&& abs(bc.x - res.x) + abs(bc.y - res.y) < min)
				min = abs(bc.x - res.x) + abs(bc.y - res.y);
			bc.x++;
		}
		bc.y++;
	}
	return (min);
}
