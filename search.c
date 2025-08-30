//Fix this: https://chatgpt.com/s/t_6895ddf9e3fc81919d1fd855b9e4202e

#include "defs.h"

int rootDepth;

static void CheckUp(S_SEARCHINFO *info) {
    // Timer check up
    // or other influence from Chess GUI

    if (info -> timeSet == TRUE && GetTimeMs() > info -> stopTime) {
        info -> stopped = TRUE;
    }

    ReadInput(info);
}

static void PickNextMove(int moveNum, S_MOVELIST *list) {
    S_MOVE temp;
    int index = 0;
    int bestScore = 0;
    int bestNum = moveNum;

    for (index = moveNum; index < list -> count; ++index) {
        if (list -> moves[index].score > bestScore) {
            bestScore = list -> moves[index].score;
            bestNum = index;
        }
    }
    temp = list -> moves[moveNum];
    list -> moves[moveNum] = list -> moves[bestNum];
    list -> moves[bestNum] = temp;
}

static int IsRepetition(const S_BOARD *pos) {
    int index = 0;

    for (index = pos -> hisPly - pos -> fiftyMove; index < pos -> hisPly - 1; ++index) {
        ASSERT (index >= 0 && index < MAXGAMEMOVES);

        if (pos -> posKey == pos -> history[index].posKey) {
            return TRUE;
        }
    }
    return FALSE;
}

static void ClearForSearch(S_BOARD *pos, S_SEARCHINFO *info) {
    int index = 0;
    int index2 = 0;

    for (index = 0; index < 13; ++index) {
        for (index2 = 0; index2 < BRD_SQ_NUM; ++index2) {
            pos -> searchHistory[index][index2] = 0;
        }
    }

    for (index = 0; index < 2; ++index) {
        for (index2 = 0; index2 < MAXDEPTH; ++index2) {
            pos -> searchKillers[index][index2] = 0;
        }
    }

    ClearPvTable(pos -> PvTable);
    pos -> ply = 0;

    info -> stopped = 0;
    info -> nodes = 0;
    info -> fh = 0;
    info -> fhf = 0;
}

static int QuietHorizon(int alpha, int beta, S_BOARD *pos, S_SEARCHINFO *info) {
    
    ASSERT(CheckBoard(pos));

    if ((info -> nodes & 2047) == 0) {
        CheckUp(info);
    }

    info -> nodes++;

    if (IsRepetition(pos) || pos -> fiftyMove >= 100) {
        return 0;
    }

    if (pos -> ply > MAXDEPTH - 1) { //Change from 3 to 1
        return EvalPosition(pos);
    }

    int Score = EvalPosition(pos);

    if (Score >= beta) {
        return beta;
    }

    if (Score > alpha) {
        alpha = Score;
    }

    S_MOVELIST list[1];
    GenerateAllCaps(pos, list);

    int MoveNum = 0;
    int Legal = 0;
    // int OldAlpha = alpha;
    // int BestMove = NO_MOVE;
    Score = -INFINITE;
    // int PvMove = ProbePvTable(pos);

    for (MoveNum = 0; MoveNum < list -> count; ++MoveNum) {
        PickNextMove(MoveNum, list);

        if (!MakeMove(pos, list -> moves[MoveNum].move)) {
            continue;
        }

        Legal++;
        Score = -QuietHorizon(-beta, -alpha, pos, info);
        TakeMove(pos);

        if (info -> stopped == TRUE) {
            return 0;
        }

        if (Score > alpha) {
            if (Score >= beta) {
                if (Legal == 1) {
                    info -> fhf++;
                }
                info -> fh++;

                return beta;
            }
            alpha = Score;
            // BestMove = list -> moves[MoveNum].move;
        }
    }

    // if (alpha != OldAlpha) {
    //     StorePvMove(pos, BestMove);
    // }

    return alpha;
}

static int AlphaBeta(int alpha, int beta, int depth, S_BOARD *pos, S_SEARCHINFO *info, int DoNull) {
    // printf("AlphaBeta depth:%d alpha:%d beta:%d\n", depth, alpha, beta);
    //Fix this: https://chatgpt.com/s/t_6897084fb7ac819183bd9d24c3bf25e4
    
    ASSERT(CheckBoard(pos));

    if (depth <= 0) {
        // return QuietHorizon(alpha, beta, pos, info);
        return EvalPosition(pos);
    }

    if ((info -> nodes & 2047) == 0) {
        CheckUp(info);
    }
    
    info -> nodes++;

    if ((IsRepetition(pos) || pos -> fiftyMove >= 100) && pos->ply) {
        return 0;
    }

    if (pos -> ply > MAXDEPTH - 1) {
        return EvalPosition(pos);
    }

    int InCheck = SqAttacked(pos->KingSq[pos->side], pos->side^1, pos);

    if(InCheck == TRUE) {
		depth++;
	}

    int Score = -INFINITE;
    int PvMove = ProbePvTable(pos);

    // if( DoNull && !InCheck && pos->ply && (pos->bigPce[pos->side] > 0) && depth >= 4) {
	// 	MakeNullMove(pos);
	// 	Score = -AlphaBeta( -beta, -beta + 1, depth-4, pos, info, FALSE);
	// 	TakeNullMove(pos);
	// 	if(info->stopped == TRUE) {
	// 		return 0;
	// 	}

	// 	if (Score >= beta && abs(Score) < ISMATE) {
	// 		info->nullCut++;
	// 		return beta;
	// 	}
	// }

    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);

    int MoveNum = 0;
    int Legal = 0;
    int OldAlpha = alpha;
    int BestMove = NO_MOVE;

    int BestScore = -INFINITE;

    Score = -INFINITE;

    if (PvMove != NO_MOVE) {
        for (MoveNum = 0; MoveNum < list -> count; ++MoveNum) {
            if (list -> moves[MoveNum].move == PvMove) {
                list -> moves[MoveNum].score = 50; // Can change if needed
                break;
            }
        }
    }

    for (MoveNum = 0; MoveNum < list -> count; ++MoveNum) {
        PickNextMove(MoveNum, list);
        if (!MakeMove(pos, list -> moves[MoveNum].move)) {
            continue;
        }

        Legal++;
        Score = -AlphaBeta(-beta, -alpha, depth-1, pos, info, TRUE);
        TakeMove(pos);

        if (info -> stopped == TRUE) {
            return 0;
        }

        if (Score > BestScore) {
            BestScore = Score;
            BestMove = list -> moves[MoveNum].move;
            if (Score > alpha) {
                if (Score >= beta) {
                    if (Legal == 1) {
                        info -> fhf++;
                    }
                    info -> fh++;

                    if (!(list -> moves[MoveNum].move & MFLAG_CAP)) {
                        pos -> searchKillers[1][pos -> ply] = pos -> searchKillers[0][pos -> ply];
                        pos -> searchKillers[0][pos -> ply] = list -> moves[MoveNum].move;
                    }

                    return beta;
                }
                alpha = Score;
                BestMove = list -> moves[MoveNum].move;

                if (!(list -> moves[MoveNum].move & MFLAG_CAP)) {
                    pos -> searchHistory[pos -> pieces[FROMSQ(BestMove)]][TOSQ(BestMove)] += depth;
                } 

            }
        }
    }

    if (Legal == 0) {
        if (InCheck) {
            return -INFINITE + pos -> ply; //SUS
        } else {
            return 0;
        }
    }

    if (alpha != OldAlpha) {
        // printf("StorePvMove Best Move:%s Score:%d\n", PrintMove(BestMove), BestScore);
        StorePvMove(pos, BestMove);
        int testGetMove = ProbePvTable(pos);
        if (testGetMove != BestMove) {
            printf("Error in PvTable\n");
        }
    }

    return alpha;
}

void SearchPosition(S_BOARD *pos, S_SEARCHINFO *info) {
    int bestMove = NO_MOVE;
    int bestScore = -INFINITE;
    int currentDepth = 0;
    int pvMoves = 0;
    int pvNum = 0;
    ClearForSearch(pos, info);

    //Iterative deepening
    if (bestMove == NO_MOVE) {
        for (currentDepth = 1; currentDepth <= info -> depth; ++currentDepth) {
            
            rootDepth = currentDepth;
            bestScore = AlphaBeta(-INFINITE, INFINITE, currentDepth, pos, info, TRUE);
            
            if (info -> stopped == TRUE) {
                break;
            }
            
            pvMoves = GetPvLine(currentDepth, pos);
            bestMove = pos -> PvArray[0];

            if (info -> GAME_MODE == UCIMODE) {
                printf("info score cp %d depth %d nodes %ld time %d ", 
                    bestScore, currentDepth, info->nodes, GetTimeMs()-info->startTime);
            } else if (info -> GAME_MODE == XBOARDMODE && info -> POST_THINKING == TRUE) {
                printf("%d %d %d %ld ",
                    currentDepth, bestScore, (GetTimeMs()-info->startTime)/10, info->nodes);
            } else if (info -> POST_THINKING == TRUE) {
                printf("score:%d depth:%d nodes:%ld time:%d(ms) ",
                    bestScore, currentDepth, info->nodes, GetTimeMs()-info->startTime);
            }
            if (info -> GAME_MODE == UCIMODE || info -> POST_THINKING == TRUE) {
                pvMoves = GetPvLine(currentDepth, pos);
                printf("pv");
                for (pvNum = 0; pvNum < pvMoves; ++pvNum) {
                        printf(" %s", PrintMove(pos -> PvArray[pvNum]));
                }
                printf("\n");
            }
        }
    }

    //Best Move
    if (info -> GAME_MODE == UCIMODE) {
        printf("bestmove %s\n", PrintMove(bestMove));
    } else if (info -> GAME_MODE == XBOARDMODE) {
        printf("move %s\n", PrintMove(bestMove));
        MakeMove(pos, bestMove);
    } else {
        printf("\n\n***!! %s makes move %s !!***\n\n", NAME, PrintMove(bestMove));
        MakeMove(pos, bestMove);
        PrintBoard(pos);
    }
}