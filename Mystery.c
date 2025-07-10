//https://www.youtube.com/watch?v=Bi61lMwhksw&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg&index=7
#include "cstdio.h"
#include "defs.h"

int main() {
    AllInit();


    //Debugging (For viewing chess board position for 10x12 and 8x8)
    int index = 0;

    for (index = 0; index < BRD_SQ_NUM; ++index) {
        if (index % 10 == 0) printf("\n");
        printf("%5d", Sq120ToSq64[index]);
    }

    printf("\n");
    printf("\n");

    for (index = 0; index < 64; ++index) {
        if (index % 8 == 0) printf("\n");
        printf("%5d", Sq64ToSq120[index]);
    }

    printf("\n");

    return 0;
}
