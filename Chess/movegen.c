#include <stdio.h>
#include "defs.h"

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

void generate_all_moves(const s_board* pos, s_move_lists* list)
{
	list->count = 0;
}
