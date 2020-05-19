#include <stdio.h>
#include "defs.h"

char* sprintf_square(const int sq)
{
	static char squareStr[3];

	int file = filesBrd[sq];
	int rank = ranksBrd[sq];

	sprintf(squareStr, "%c%c", ('a' + file), ('1' + rank));

	return squareStr;
}

char* print_move(const int move)
{
	static char moveStr[6];

	int fileFrom = filesBrd[FROMSQ(move)];
	int rankFrom = ranksBrd[FROMSQ(move)];
	int fileTo = filesBrd[TOSQ(move)];
	int rankTo = ranksBrd[TOSQ(move)];

	int promoted = PROMOTED(move);

	if (promoted)
	{
		char pchar = 'q';

		if (IsKn(promoted))
			pchar = 'n';
		else if (IsRQ(promoted) && !IsBQ(promoted))
			pchar = 'r';
		else if (!IsRQ(promoted) && IsBQ(promoted))
			pchar = 'b';

		sprintf(
			moveStr,
			"%c%c%c%c%c",
			('a' + fileFrom), ('1' + rankFrom), ('a' + fileTo), ('1' + rankTo), pchar
		);
	}
	else
	{
		sprintf(
			moveStr,
			"%c%c%c%c",
			('a' + fileFrom), ('1' + rankFrom), ('a' + fileTo), ('1' + rankTo)
		);
	}

	return moveStr;
}
