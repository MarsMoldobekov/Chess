#include "defs.h"

int sq120_to_sq64[BRD_SQ_NUM];
int sq64_to_sq120[64];

U64 set_mask[64];
U64 clear_mask[64];

void init_bit_mask()
{
	int index = 0;

	for (index = 0; index < 64; index++)
	{
		set_mask[index] = 0ULL;
		clear_mask[index] = 0ULL;
	}
	
	for (index = 0; index < 64; index++)
	{
		set_mask[index] |= (1ULL << index);
		clear_mask[index] = ~set_mask[index];
	}
}

void initSq120to64()
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;

	for (index = 0; index < BRD_SQ_NUM; index++)
		sq120_to_sq64[index] = 65;

	for (index = 0; index < 64; index++)
		sq64_to_sq120[index] = 120;

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
	init_bit_mask();
}
