//https://www.youtube.com/watch?v=PGPdT9zz-xg&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg&index=21

//Vice Engine Source Code: https://github.com/bluefeversoft/vice/tree/main/Vice11/src
#include "defs.h"

#define FEN1 "r5k1/2pq2p1/ppn4p/2p1p3/2P5/2NPP1P1/PP4KP/1R3Q2 b - - 0 21"
#define FEN2 "4q1k1/2p3p1/pp5p/2p1n3/2P1P3/2N1P1P1/PP2Q2P/5K2 b - - 0 26"
#define FEN3 "8/6p1/pp5p/2p1kP2/4P1P1/5K2/P6P/8 w - - 0 41"
#define FEN4 "r3qrk1/ppp5/3p2n1/3Pp1Q1/4n3/2PN4/P1P3PP/R4RK1 w - - 0 21"

int main() {
    AllInit();

    S_BOARD board[1];

    // Parse_FEN(START_FEN, board);
    // PrintBoard(board);
    // Parse_FEN(FEN1, board);
    // PrintBoard(board);
    // Parse_FEN(FEN2, board);
    // PrintBoard(board);
    Parse_FEN(FEN4, board);

    PrintBoard(board);

    ASSERT(CheckBoard(board));

    printf("\nForced assesrts to damage: \n");

    board -> posKey ^= SideKey;
    ASSERT(CheckBoard(board));

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