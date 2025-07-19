//https://www.youtube.com/watch?v=ZWcjcn4KVTk&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg&index=37
//Chapter: 37

//Vice Engine Source Code: https://github.com/bluefeversoft/vice/tree/main/Vice11/src
#include "defs.h"

#define FEN1 "r5k1/2pq2p1/ppn4p/2p1p3/2P5/2NPP1P1/PP4KP/1R3Q2 b - - 0 21"
#define FEN2 "4q1k1/2p3p1/pp5p/2p1n3/2P1P3/2N1P1P1/PP2Q2P/5K2 b - - 0 26"
#define FEN3 "8/6p1/pp5p/2p1kP2/4P1P1/5K2/P6P/8 w - - 0 41"
#define FEN4 "r3qrk1/ppp5/3p2n1/3Pp1Q1/4n3/2PN4/P1P3PP/R4RK1 w - - 0 21"
#define FEN5 "8/8/3q4/8/8/3Q4/8/8 w HAha - 0 1"
#define FEN6 "2k5/8/3q4/4pK2/2P5/3Q4/8/8 w - - 0 1"
#define FEN7 "2k4n/6P1/8/8/8/8/8/2K5 w - - 0 1"
#define FEN_W "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define FEN_B "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"
#define Knight_W "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"
#define Knight_B "5k2/1n6/4n3/6N1/8/3N4/8/5K2 b - - 0 1"

#define KnB "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1"
#define Rook "6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1"
#define Queen "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1"
#define Castling "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
#define Tricky_Castle_Right "3rk2r/8/8/8/8/8/6p1/R3K2R b KQk - 0 1"
#define Less_Tricky "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"



int main() {
    AllInit();

    S_BOARD board[1];
    S_MOVELIST list[1];

    Parse_FEN(Less_Tricky, board);
    PrintBoard(board);

    // S_MOVELIST list[1];

    GenerateAllMoves(board, list);

    PrintMoveList(list);

    return 0;
}

    // Display Board position (For viewing chess board position for 10x12 and 8x8)
    // int index = 0;

    // for (index = 0; index < BRD_SQ_NUM; ++index) {
    //     if (index % 10 == 0) printf("\n");
    //     printf("%5d", Sq120ToSq64[index]);
    // }

    // printf("\n");
    // printf("\n");

    // for (index = 0; index < 64; ++index) {
    //     if (index % 8 == 0) printf("\n");
    //     printf("%5d", Sq64ToSq120[index]);
    // }

    // printf("\n");
    

    //Showing Pawn adding position on board
    // U64 playBitBoard = 0ULL;

    // printf("Start: \n\n");
    // PrintBitBoard(playBitBoard);

    // playBitBoard |= (1ULL << SQ64(D2));
    // printf("D2 Added: \n\n");
    // PrintBitBoard(playBitBoard);

    // playBitBoard |= (1ULL << SQ64(F4));
    // printf("F4 Added: \n\n");
    // PrintBitBoard(playBitBoard);

    // int index = 0;
    // U64 playBitBoard = 0ULL;

    // for (index = 0; index < 64; index++) {
    //     printf("Index: %d\n", index);
    //     PrintBitBoard(ClearMask[index]);
    //     printf("\n");
    // }

    // SETBIT(playBitBoard, 61);
    // PrintBitBoard(playBitBoard);

    // CLRBIT(playBitBoard, 61);
    // PrintBitBoard(playBitBoard);


    // int Piece1 = rand();
    // int Piece2 = rand();
    // int Piece3 = rand();
    // int Piece4 = rand();

    // printf("Piece 1: %X\n", Piece1);
    // printf("Piece 2: %X\n", Piece2);
    // printf("Piece 3: %X\n", Piece3);
    // printf("Piece 4: %X\n", Piece4);

    // int key = Piece1 ^ Piece2 ^ Piece3 ^ Piece4;
    // int TempKey = Piece2;
    // TempKey ^= Piece3;
    // TempKey ^= Piece4;
    // TempKey ^= Piece1;

    // printf("Key: %X\n", key);
    // printf("TempKey: %X\n", TempKey);

    // TempKey ^= Piece3;
    // printf("(Three out) TempKey: %X\n", TempKey);

    // TempKey ^= Piece3;
    // printf("(Three in again) TempKey: %X\n", TempKey);



    // printf("\nwP: \n");
    // PrintBitBoard(board -> pawns[WHITE]);
    // printf("\nbP: \n");
    // PrintBitBoard(board -> pawns[BLACK]);
    // printf("\nall Pawns: \n");
    // PrintBitBoard(board -> pawns[BOTH]);



    // void ShowSqAtBySide(const int side, const S_BOARD *pos) {
    //     int rank = 6; int file = 0; int sq = 0; 
    //     printf("\n\nSquares attacked by:%c\n",SideChar[side]);
    //     for (rank = RANK_8; rank >= RANK_1; --rank) {
    //         for (file = FILE_A; file <= FILE_H; ++file) {
    //             sq = FR2SQ(file, rank);
    //             if (SqAttacked(sq, side, pos) == TRUE) {
    //                 printf("x");
    //             } else {
    //                 printf("-");
    //             }
    //         }
    //         printf("\n");
    //     }
    //     printf("\n\n");
    // }


    // void PrintBin(int move) {
    //     int index = 0;
    //     printf("As binary: \n");
    //     for (index = 27; index >= 0; index--) {
    //         if ((1 << index) & move) printf("1");
    //         else printf("0");
    //         if (index != 20 && index%4 == 0) printf(" ");
    //     }
    //     printf("\n");
    // }




    // int move = 0;
    // int from = A2; int to = H7;
    // int cap = wR; int prom = bK;

    // move = ( ( from ) | (to << 7) | (cap << 14) | (prom << 20) );

    // // printf("\ndec: %d hex: %X\n", move, move);
    // // PrintBin(move);

    // printf("From: %d to: %d cap: %d prom: %d\n",
    //     FROMSQ(move), TOSQ(move), CAPTURED(move),
    //     PROMOTED(move));

    // // move |= MFLAG_PS;
    // // printf("is PST: %s\n", (move & MFLAG_PS) ? "YES":"NO");

    // printf("Algebraic from: %s\n", PrintSq(from));
    // printf("Algebraic to: %s\n", PrintSq(to));
    // printf("Algebraic move: %s\n", PrintMove(move));