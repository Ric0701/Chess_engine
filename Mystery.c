//https://www.youtube.com/watch?v=vF_Td1nABYw&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg&index=13
#include "defs.h"

int main() {
    AllInit();

    int Piece1 = rand();
    int Piece2 = rand();
    int Piece3 = rand();
    int Piece4 = rand();

    printf("Piece 1: %X\n", Piece1);
    printf("Piece 2: %X\n", Piece2);
    printf("Piece 3: %X\n", Piece3);
    printf("Piece 4: %X\n", Piece4);

    int key = Piece1 ^ Piece2 ^ Piece3 ^ Piece4;
    int TempKey = Piece2;
    TempKey ^= Piece3;
    TempKey ^= Piece4;
    TempKey ^= Piece1;

    printf("Key: %X\n", key);
    printf("TempKey: %X\n", TempKey);

    TempKey ^= Piece3;
    printf("(Three out) TempKey: %X\n", TempKey);

    TempKey ^= Piece3;
    printf("(Three in again) TempKey: %X\n", TempKey);

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