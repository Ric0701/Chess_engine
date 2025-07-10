//https://www.youtube.com/watch?v=Bi61lMwhksw&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg&index=7
#include "defs.h"

int main() {
    AllInit();

    
    return 0;
}


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

    //Display Board position (For viewing chess board position for 10x12 and 8x8)
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