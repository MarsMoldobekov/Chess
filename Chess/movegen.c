#include <stdio.h>
#include "defs.h"

#define MOVE(f, t, ca, pro, fl) \
(\
	(f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl) \
)
#define SQOFFBOARD(sq) (filesBrd[(sq)] == OFFBOARD)

void add_quiet_move(const s_board* pos, int move, s_move_lists* list)
{
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void add_capture_move(const s_board* pos, int move, s_move_lists* list)
{
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void add_enPassant_move(const s_board* pos, int move, s_move_lists* list)
{
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void add_white_pawn_capture_move(const s_board* pos, const int from, const int to, const int cap, s_move_lists* list)
{
	if (ranksBrd[from] == RANK_7)
	{
		add_capture_move(pos, MOVE(from, to, cap, wQ, 0), list);
		add_capture_move(pos, MOVE(from, to, cap, wR, 0), list);
		add_capture_move(pos, MOVE(from, to, cap, wB, 0), list);
		add_capture_move(pos, MOVE(from, to, cap, wN, 0), list);
	}
	else
	{
		add_capture_move(pos, MOVE(from, to, cap, EMPTY, 0), list);
	}
}

void add_white_pawn_move(const s_board* pos, const int from, const int to, s_move_lists* list)
{
	if (ranksBrd[from] == RANK_7)
	{
		add_quiet_move(pos, MOVE(from, to, EMPTY, wQ, 0), list);
		add_quiet_move(pos, MOVE(from, to, EMPTY, wR, 0), list);
		add_quiet_move(pos, MOVE(from, to, EMPTY, wB, 0), list);
		add_quiet_move(pos, MOVE(from, to, EMPTY, wN, 0), list);
	}
	else
	{
		add_quiet_move(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
	}
}

void add_black_pawn_capture_move(const s_board* pos, const int from, const int to, const int cap, s_move_lists* list)
{
	if (ranksBrd[from] == RANK_2)
	{
		add_capture_move(pos, MOVE(from, to, cap, bQ, 0), list);
		add_capture_move(pos, MOVE(from, to, cap, bR, 0), list);
		add_capture_move(pos, MOVE(from, to, cap, bB, 0), list);
		add_capture_move(pos, MOVE(from, to, cap, bN, 0), list);
	}
	else
	{
		add_capture_move(pos, MOVE(from, to, cap, EMPTY, 0), list);
	}
}

void add_black_pawn_move(const s_board* pos, const int from, const int to, s_move_lists* list)
{
	if (ranksBrd[from] == RANK_2)
	{
		add_quiet_move(pos, MOVE(from, to, EMPTY, bQ, 0), list);
		add_quiet_move(pos, MOVE(from, to, EMPTY, bR, 0), list);
		add_quiet_move(pos, MOVE(from, to, EMPTY, bB, 0), list);
		add_quiet_move(pos, MOVE(from, to, EMPTY, bN, 0), list);
	}
	else
	{
		add_quiet_move(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
	}
}

void generate_all_moves(const s_board* pos, s_move_lists* list)
{
	ASSERT(check_board(pos));

	list->count = 0;

	int pce = EMPTY;
	int side = pos->side;
	int sq = 0, t_sq = 0;
	int pceNum = 0;

	if (side == WHITE)
	{
		for (pceNum = 0; pceNum < pos->pceNum[wP]; pceNum++)
		{
			sq = pos->pList[wP][pceNum];
			ASSERT(square_on_board(sq));

			if (pos->pieces[sq + 10] == EMPTY)
			{
				add_white_pawn_move(pos, sq, sq + 10, list);

				if (ranksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY)
				{
					add_quiet_move(pos, MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), list);
				}
			}

			if (!SQOFFBOARD(sq + 9) && pieceCol[pos->pieces[sq + 9]] == BLACK)
			{
				add_white_pawn_capture_move(pos, sq, sq + 9, pos->pieces[sq + 9], list);
			}

			if (!SQOFFBOARD(sq + 11) && pieceCol[pos->pieces[sq + 11]] == BLACK)
			{
				add_white_pawn_capture_move(pos, sq, sq + 9, pos->pieces[sq + 9], list);
			}

			if (sq + 9 == pos->enPas)
			{
				add_capture_move(pos, MOVE(sq, sq + 9, EMPTY, EMPTY, MFLAGEP), list);
			}
			
			if (sq + 11 == pos->enPas)
			{
				add_capture_move(pos, MOVE(sq, sq + 11, EMPTY, EMPTY, MFLAGEP), list);
			}
		}
	}
	else
	{
		for (pceNum = 0; pceNum < pos->pceNum[bP]; pceNum++)
		{
			sq = pos->pList[bP][pceNum];
			ASSERT(square_on_board(sq));

			if (pos->pieces[sq - 10] == EMPTY)
			{
				add_black_pawn_move(pos, sq, sq - 10, list);

				if (ranksBrd[sq] == RANK_7 && pos->pieces[sq - 20] == EMPTY)
				{
					add_quiet_move(pos, MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), list);
				}
			}
			
			if (!SQOFFBOARD(sq - 9) && pieceCol[pos->pieces[sq - 9]] == WHITE)
			{
				add_black_pawn_capture_move(pos, sq, sq - 9, pos->pieces[sq - 9], list);
			}

			if (!SQOFFBOARD(sq - 11) && pieceCol[pos->pieces[sq - 11]] == WHITE)
			{
				add_black_pawn_capture_move(pos, sq, sq - 11, pos->pieces[sq - 1], list);
			}

			if (sq - 9 == pos->enPas)
			{
				add_capture_move(pos, MOVE(sq, sq - 9, EMPTY, EMPTY, MFLAGEP), list);
			}

			if (sq - 11 == pos->enPas)
			{
				add_capture_move(pos, MOVE(sq, sq - 11, EMPTY, EMPTY, MFLAGEP), list);
			}
		}
	}
}
