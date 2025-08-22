#include "defs.h"

int SqOnBoard(const int sq) {
    return FilesBrd[sq] == OFFBOARD ? 0 : 1;
}

int SideValid(const int side) {
    return (side == WHITE || side == BLACK) ? 1: 0;
}

int FileRankValid(const int fr) {
    return (fr >= 0 && fr <= 7) ? 1 : 0;
}

int PieceValidEmpty(const int pce) {
    return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

int PieceValid(const int pce) {
    return (pce >= wP && pce <= bK) ? 1 : 0;
}

void MirrorEvalTest(S_BOARD *pos) {
    FILE *file;
    file = fopen("mirror.epd", "r");
    char lineIn[1024];
    int eval1 = 0, eval2 = 0;
    int positions = 0;
    if (file == NULL) {
        printf("File Not Found\n");
        return;
    } else {
        while (fgets(lineIn, 1024, file) != NULL) {
            Parse_FEN(lineIn, pos);
            positions++;
            eval1 = EvalPosition(pos);
            MirrorBoard(pos);
            eval2 = EvalPosition(pos);

            if (eval1 != eval2) {
                printf("\n\n\n");
                Parse_FEN(lineIn, pos);
                PrintBoard(pos);
                MirrorBoard(pos);
                PrintBoard(pos);
                printf("\n\nMirror Fail:\n%s\n", lineIn);
                getchar();
                return;
            }

            if ((positions % 1000) == 0) {
                printf("Position %d\n", positions);
            }

            memset(&lineIn[0], 0, sizeof(lineIn));
        }
    }
}