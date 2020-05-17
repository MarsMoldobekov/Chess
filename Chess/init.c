#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

#define RAND_64 ((U64)rand() | \
				 (U64)rand() << 15 | \
				 (U64)rand() << 30 | \
				 (U64)rand() << 45 | \
				 ((U64)rand() & 0xf) << 60)

int sq120_to_sq64[BRD_SQ_NUM];
int sq64_to_sq120[64];

U64 set_mask[64];
U64 clear_mask[64];

U64 pieceKeys[13][120];
U64 sideKey;
U64 castleKeys[16];

int filesBrd[BRD_SQ_NUM];
int ranksBrd[BRD_SQ_NUM];

void init_files_ranks_brd()
{
	int i = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;

	for (i = 0; i < BRD_SQ_NUM; i++)
	{
		filesBrd[i] = OFFBOARD;
		ranksBrd[i] = OFFBOARD;
	}

	for (rank = RANK_1; rank <= RANK_8; rank++)
	{
		for (file = FILE_A; file <= FILE_H; file++)
		{
			sq = FR2SQ(file, rank);
			filesBrd[sq] = file;
			ranksBrd[sq] = rank;
		}
	}
}

void init_hash_keys()
{
	int i = 0;

	for (i = 0; i < 13; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			pieceKeys[i][j] = RAND_64;
		}
	}

	sideKey = RAND_64;

	for (i = 0; i < 16; i++)
	{
		castleKeys[i] = RAND_64;
	}
}

void init_bit_masks()
{
	int i = 0;

	for (i = 0; i < 64; i++)
	{
		set_mask[i] = 0ULL;
		clear_mask[i] = 0ULL;
	}
	
	for (i = 0; i < 64; i++)
	{
		set_mask[i] |= (1ULL << i);
		clear_mask[i] = ~set_mask[i];
	}
}

void initSq120to64()
{
	int i = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;

	for (i = 0; i < BRD_SQ_NUM; i++)
		sq120_to_sq64[i] = 65;

	for (i = 0; i < 64; i++)
		sq64_to_sq120[i] = 120;

	for (rank = RANK_1; rank <= RANK_8; rank++)
	{
		for (file = FILE_A; file <= FILE_H; file++)
		{
			sq = FR2SQ(file, rank);
			sq64_to_sq120[sq64] = sq;
			sq120_to_sq64[sq] = sq64;
			sq64++;
		}
	}
}

void init()
{
	initSq120to64();
	init_bit_masks();
	init_hash_keys();
	init_files_ranks_brd();
}
