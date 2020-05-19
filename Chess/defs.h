#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

//TODO --- check
#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#include <stdio.h>
#define ASSERT(n) \
    if (!(n)) \
    { \
        printf("%s - FAILED\n", #n); \
        printf("On %s\n", __DATE__); \
        printf("At %s\n", __TIME__); \
        printf("In File %s\n", __FILE__); \
        printf("At Line %d\n", __LINE__); \
        exit(1); \
    }
#endif /* DEBUG */

typedef unsigned long long U64;

#define NAME "Vice 1.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

enum
{
    EMPTY,
    wP, wN, wB, wR, wQ, wK,
    bP, bN, bB, bR, bQ, bK
};

enum
{
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE
};

enum
{
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE
};

enum
{
    WHITE, BLACK, BOTH
};

enum
{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    NO_SQ, OFFBOARD
};

enum
{
    FALSE, TRUE
};

enum
{
    WKCA = 1, WQCA = 2,
    BKCA = 4, BQCA = 8
};

typedef struct
{
    int move;
    int score;
} s_move;

typedef struct
{
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;
} s_undo;

typedef struct
{
    int pieces[BRD_SQ_NUM];
    U64 pawns[3];

    int kingSq[2];

    int side;
    int enPas;
    int fiftyMove;

    int ply;
    int hisPly;

    int castlePerm;

    U64 posKey;

    int pceNum[13];
    int bigPce[2];
    int majPce[2];
    int minPce[2];
    int material[2];

    s_undo history[MAXGAMEMOVES];

    int pList[13][10];
} s_board;

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m) >> 7) & 0x7F)
#define CAPTURED(m) (((m) >> 14) & 0xF)
#define PROMOTED(m) (((m) >> 20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000

#define FR2SQ(f, r) ((21 + (f)) + ((r) * 10))
#define SQ64(sq120) (sq120_to_sq64[(sq120)])
#define SQ120(sq64) (sq64_to_sq120[(sq64)])
#define POP(b) pop_bit(b)
#define CNT(b) count_bits(b)
#define CLRBIT(bb, sq) ((bb) &= clear_mask[(sq)])
#define SETBIT(bb, sq) ((bb) |= set_mask[(sq)])

#define IsBQ(p) (pieceBishopQueen[(p)])
#define IsRQ(p) (pieceRookQueen[(p)])
#define IsKn(p) (pieceKnight[(p)])
#define IsKi(p) (pieceKing[(p)])

extern int sq120_to_sq64[BRD_SQ_NUM];
extern int sq64_to_sq120[64];
extern U64 set_mask[64];
extern U64 clear_mask[64];
extern U64 pieceKeys[13][120];
extern U64 sideKey;
extern U64 castleKeys[16];
extern char pceChar[];
extern char sideChar[];
extern char rankChar[];
extern char fileChar[];

extern int pieceBig[13];
extern int pieceMaj[13];
extern int pieceMin[13];
extern int pieceVal[13];
extern int pieceCol[13];

extern int filesBrd[BRD_SQ_NUM];
extern int ranksBrd[BRD_SQ_NUM];

extern int pieceKnight[13];
extern int pieceKing[13];
extern int pieceRookQueen[13];
extern int pieceBishopQueen[13];

extern void init();

extern void printBitBoard(U64 bb);
extern int pop_bit(U64* bb);
extern int count_bits(U64 b);

extern U64 generate_pos_key(const s_board* pos);

extern void reset_board(s_board* pos);
extern int parse_fen(char* fen, s_board* pos);
extern void print_board(const s_board* pos);
extern void update_lists_material(s_board* pos);
extern int check_board(const s_board* pos);

extern int square_attacked(const int sq, const int side, const s_board* pos);

#endif /* DEFS_H */
