#include <stdio.h>
#include "defs.h"

void reset_board(s_board* pos)
{
	int i = 0;

	for (i = 0; i < BRD_SQ_NUM; i++)
	{
		pos->pieces[i] = OFFBOARD;
	}

	for (i = 0; i < 64; i++)
	{
		pos->pieces[SQ64(i)] = EMPTY;
	}

	for (i = 0; i < 3; i++)
	{
		pos->bigPce[i] = 0;
		pos->majPce[i] = 0;
		pos->minPce[i] = 0;
		pos->pawns[i] = 0ULL;
	}

	for (i = 0; i < 13; i++)
	{
		pos->pceNum[i] = 0;
	}

	pos->kingSq[WHITE] = pos->kingSq[BLACK] = NO_SQ;

	pos->side = BOTH;
	pos->enPas = NO_SQ;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->posKey = 0ULL;
}
