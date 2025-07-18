#include "defs.h"

char *PrintSq(const int sq) {
    static char SqStr[3];

    int file = FilesBrd[sq];
    int rank = RanksBrd[sq];

    sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));

    return SqStr;
}

char *PrintMove(const int move) {
    static char MvStr[6];
    
    int ff = FilesBrd[FROMSQ(move)];    // File of the "from" square
    int rf = RanksBrd[FROMSQ(move)];    // Rank of the "from" square
    int ft = FilesBrd[TOSQ(move)];      // File of the "to" square
    int rt = RanksBrd[TOSQ(move)];      // Rank of the "to" square

    int promoted = PROMOTED(move);

    if (promoted) {
        char pchar = 'q';
        if (IsKn(promoted)) {
            pchar = 'n';
        } else if (IsRQ(promoted) && !IsBQ(promoted)) {
            pchar = 'r';
        } else if (!IsRQ(promoted) && IsBQ(promoted)) {
            pchar = 'b';
        }
        sprintf(MvStr, "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
    } else {
        sprintf(MvStr, "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
    }

    // printf("DEBUG move: %d from: %d to: %d\n", move, FROMSQ(move), TOSQ(move));
    // printf("DEBUG ff=%d rf=%d ft=%d rt=%d\n", ff, rf, ft, rt);

    return MvStr;
}

void PrintMoveList(const S_MOVELIST *list) {
    int index = 0;
    int score = 0;
    int move = 0;
    printf("Move List: \n");

    for (index = 0; index < list -> count; ++index) {
        move = list -> moves[index].move;
        score = list -> moves[index].score;

        printf("Move: %d > %s (Score: %d)\n", index+1, PrintMove(move), score);
    }
    printf("Move List Total %d Moves: \n\n", list -> count);
}