/*
This File handles all the move rules such as how knight moves.
List of Handled pieces:
1. Pawns (move forward 1 or 2 squares, Diagonal Capture, En Passant, Promotions)
2. Knight (L-Shape)
3. Bishop (Long Range Diagonal sliding)
4. Rook (Long Range Vertical & Horizontal sliding)
5. Queen (Bishop + Rook move logic)
6. King (One Square at a time)
*/

#include "defs.h"

#define MOVE(f, t, ca, pro, fl) ( (f) | ((t) << 7) | ( (ca) << 14) | ( (pro) << 20) | (fl))
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFFBOARD)

//Sliding Pieces Logic
const int LoopSlidePce[8] = {
    wB, wR, wQ, 0, bB, bR, bQ, 0
};

const int LoopSlideIndex[2] = {0, 4};

//Non-Sliding Pieces Logic
const int LoopNonSlidePce[6] = {
    wN, wK, 0, bN, bK, 0
};

const int LoopNonSlideIndex[2] = {0, 3};

const int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

const int NumDir[13] = {
 0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8
};

const int VictimScore[13] = { 0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600 };
static int MvvLvaScores[13][13];

int InitMvvLva() {
    int Attacker;
    int Victim;

    for (Attacker = wP; Attacker <= bK; ++Attacker) {
        for (Victim = wP; Victim <= bK; ++Victim) {
            MvvLvaScores[Victim][Attacker] = VictimScore[Victim] + 6 - (VictimScore[Attacker] / 100);
        }
    }
}

int MoveExists(S_BOARD *pos, const int move) {
    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);

    int MoveNum = 0;
    for (MoveNum = 0; MoveNum < list->count; ++MoveNum) {
        if (!MakeMove(pos, list -> moves[MoveNum].move)) {
            continue;
        }
        TakeMove(pos);
        if (list -> moves[MoveNum].move == move) {
            return TRUE;
        }
    }
    return FALSE;
}

//Standard Move
static void AddQuietMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
    ASSERT(SqOnBoard(FROMSQ(move)));
    ASSERT(SqOnBoard(TOSQ(move)));
    ASSERT(CheckBoard(pos));
    
    list -> moves[list -> count].move = move;

    if (pos -> searchKillers[0][pos -> ply] == move) {
        list -> moves[list -> count].score = 90;
    } else if (pos -> searchKillers[1][pos -> ply] == move) {
        list -> moves[list -> count].score = 80;
    } else {
        list -> moves[list -> count].score = pos -> searchHistory[pos -> pieces[FROMSQ(move)]][TOSQ(move)];
    }
    list -> count++;
}

static void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
    ASSERT(SqOnBoard(FROMSQ(move)));
    ASSERT(SqOnBoard(TOSQ(move)));
    ASSERT(CheckBoard(pos));
    ASSERT(PieceValid(CAPTURED(move)));
    
    list -> moves[list -> count].move = move;
    list -> moves[list -> count].score = MvvLvaScores[CAPTURED(move)][pos -> pieces[FROMSQ(move)]] + 100; //Change the value "100" if neeeded
    list -> count++;
}

static void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
    ASSERT(SqOnBoard(FROMSQ(move)));
    ASSERT(SqOnBoard(TOSQ(move)));
    
    list -> moves[list -> count].move = move;
    list -> moves[list -> count].score = 105 + 100;
    list -> count++;
}

static void AddWhitePawnCapMove(const S_BOARD *pos, const int from , const int to, const int cap, S_MOVELIST *list) {
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));
    ASSERT(CheckBoard(pos));
    
    if (RanksBrd[from] == RANK_7) {
        AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
    } else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

static void AddWhitePawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list ) {
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));

	if(RanksBrd[from] == RANK_7) {
		AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
	} else {
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
	}
}

static void AddBlackPawnCapMove(const S_BOARD *pos, const int from , const int to, const int cap, S_MOVELIST *list) {
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));
    
    if (RanksBrd[from] == RANK_2) {
        AddCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
    } else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

static void AddBlackPawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list ) {
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));

	if(RanksBrd[from] == RANK_2) {
		AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
	} else {
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
	}
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
    ASSERT(CheckBoard(pos));

    list -> count = 0;

    int pce = EMPTY;
    int side = pos -> side;
    int sq = 0; int t_sq = 0; //t_sq is target Square
    int pceNum = 0;
    int dir = 0;
    int index = 0;
    int pceIndex = 0;

    if (side == WHITE) {
        for (pceNum = 0; pceNum < pos -> pceNum[wP]; ++pceNum) {
            sq = pos -> pList[wP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Move Forward - White
            if (pos -> pieces[sq + 10] == EMPTY) {
                AddWhitePawnMove(pos, sq, sq+10, list);
                if (RanksBrd[sq] == RANK_2 && pos -> pieces[sq + 20] == EMPTY) {
                    AddQuietMove(pos, MOVE(sq, (sq+20), EMPTY, EMPTY, MFLAG_PS), list);
                }
            }
            
            //Capture Permission - White
            if (!SQOFFBOARD(sq + 9) && PieceCol[pos -> pieces[sq + 9]] == BLACK) {
                AddWhitePawnCapMove(pos, sq, sq+9, pos->pieces[sq+9], list);
            }
            if (!SQOFFBOARD(sq + 11) && PieceCol[pos -> pieces[sq + 11]] == BLACK) {
                AddWhitePawnCapMove(pos, sq, sq+11, pos->pieces[sq+11], list);
            }

            //En Passant Permission - White
            if (pos -> enPas != NO_SQ) {
                if (sq + 9 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq+9, EMPTY, EMPTY, MFLAG_EP), list);
                }
                if (sq + 11 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq+11, EMPTY, EMPTY, MFLAG_EP), list);
                }
            }
        }

        //Castling Permission - White
        if (pos -> castlePerm & WKCA) {
            if (pos -> pieces[F1] == EMPTY && pos -> pieces[G1] == EMPTY) {
                if (!SqAttacked(E1, BLACK, pos) && !SqAttacked(F1, BLACK, pos)) {
                    AddQuietMove(pos, MOVE(E1, G1, EMPTY, EMPTY, MFLAG_CA), list);
                }
            }
        }

        if (pos -> castlePerm & WQCA) {
            if (pos -> pieces[B1] == EMPTY && pos -> pieces[C1] == EMPTY && pos -> pieces[D1] == EMPTY) {
                if (!SqAttacked(D1, BLACK, pos) && !SqAttacked(E1, BLACK, pos)) {
                    AddQuietMove(pos, MOVE(E1, C1, EMPTY, EMPTY, MFLAG_CA), list);
                }
            }
        }

    } else { 
        for (pceNum = 0; pceNum < pos -> pceNum[bP]; ++pceNum) {
            sq = pos -> pList[bP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Move Forward - Black
            if (pos -> pieces[sq - 10] == EMPTY) {
                AddBlackPawnMove(pos, sq, sq-10, list);
                if (RanksBrd[sq] == RANK_7 && pos -> pieces[sq - 20] == EMPTY) {
                    AddQuietMove(pos, MOVE(sq, (sq-20), EMPTY, EMPTY, MFLAG_PS), list);
                }
            }

            //Capture Permission - Black
            if (!SQOFFBOARD(sq - 9) && PieceCol[pos -> pieces[sq - 9]] == WHITE) {
                AddBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq-9], list);
            }
            if (!SQOFFBOARD(sq - 11) && PieceCol[pos -> pieces[sq - 11]] == WHITE) {
                AddBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq-11], list);
            }

            //En Passant Permission - Black
            if (pos -> enPas != NO_SQ) {
                if (sq - 9 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq-9, EMPTY, EMPTY, MFLAG_EP), list);
                }
                if (sq - 11 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq-11, EMPTY, EMPTY, MFLAG_EP), list);
                }
            }
        }

        //Castling Permission - Black
        if (pos -> castlePerm & BKCA) {
            if (pos -> pieces[F8] == EMPTY && pos -> pieces[G8] == EMPTY) {
                if (!SqAttacked(E8, WHITE, pos) && !SqAttacked(F8, WHITE, pos)) {
                    AddQuietMove(pos, MOVE(E8, G8, EMPTY, EMPTY, MFLAG_CA), list);
                }
            }
        }

        if (pos -> castlePerm & BQCA) {
            if (pos -> pieces[B8] == EMPTY && pos -> pieces[C8] == EMPTY && pos -> pieces[D8] == EMPTY) {
                if (!SqAttacked(D8, WHITE, pos) && !SqAttacked(E8, WHITE, pos)) {
                    AddQuietMove(pos, MOVE(E8, C8, EMPTY, EMPTY, MFLAG_CA), list);
                }
            }
        }
    }

    // Loop for slide pieces
    pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePce[pceIndex++];

    while (pce != 0) {
        ASSERT(PieceValid(pce));

        for (pceNum = 0; pceNum < pos -> pceNum[pce]; ++pceNum) {
            sq = pos -> pList[pce][pceNum];
            ASSERT(SqOnBoard(sq));

            for (index = 0; index < NumDir[pce]; ++index) {
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                while (!SQOFFBOARD(t_sq)) {
                    if (pos -> pieces[t_sq] != EMPTY) {
                        if (PieceCol[pos -> pieces[t_sq]] == side ^ 1) {
                            AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                        }
                        break;
                    }
                    AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
                    t_sq += dir;
                }
            }
        }
        pce = LoopSlidePce[pceIndex++];
    }

    //Loop for non-slide
    pceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePce[pceIndex++];

    while (pce != 0) {
        ASSERT(PieceValid(pce));

        for (pceNum = 0; pceNum < pos -> pceNum[pce]; ++pceNum) {
            sq = pos -> pList[pce][pceNum];
            ASSERT(SqOnBoard(sq));

            for (index = 0; index < NumDir[pce]; ++index) {
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                if (SQOFFBOARD(t_sq)) {
                    continue;
                }

                if (pos -> pieces[t_sq] != EMPTY) {
                    if (PieceCol[pos -> pieces[t_sq]] == side ^ 1) {
                        AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                    }
                    continue;
                }
                AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
            }
        }
        pce = LoopNonSlidePce[pceIndex++];
    }
}


void GenerateAllCaps(const S_BOARD *pos, S_MOVELIST *list) {
    ASSERT(CheckBoard(pos));

    list -> count = 0;

    int pce = EMPTY;
    int side = pos -> side;
    int sq = 0; int t_sq = 0; //t_sq is target Square
    int pceNum = 0;
    int dir = 0;
    int index = 0;
    int pceIndex = 0;

    if (side == WHITE) {
        for (pceNum = 0; pceNum < pos -> pceNum[wP]; ++pceNum) {
            sq = pos -> pList[wP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Capture Permission - White
            if (!SQOFFBOARD(sq + 9) && PieceCol[pos -> pieces[sq + 9]] == BLACK) {
                AddWhitePawnCapMove(pos, sq, sq+9, pos->pieces[sq+9], list);
            }
            if (!SQOFFBOARD(sq + 11) && PieceCol[pos -> pieces[sq + 11]] == BLACK) {
                AddWhitePawnCapMove(pos, sq, sq+11, pos->pieces[sq+11], list);
            }

            //En Passant Permission - White
            if (pos -> enPas != NO_SQ) {
                if (sq + 9 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq+9, EMPTY, EMPTY, MFLAG_EP), list);
                }
                if (sq + 11 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq+11, EMPTY, EMPTY, MFLAG_EP), list);
                }
            }
        }
    } else { 
        for (pceNum = 0; pceNum < pos -> pceNum[bP]; ++pceNum) {
            sq = pos -> pList[bP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Capture Permission - Black
            if (!SQOFFBOARD(sq - 9) && PieceCol[pos -> pieces[sq - 9]] == WHITE) {
                AddBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq-9], list);
            }
            if (!SQOFFBOARD(sq - 11) && PieceCol[pos -> pieces[sq - 11]] == WHITE) {
                AddBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq-11], list);
            }

            //En Passant Permission - Black
            if (pos -> enPas != NO_SQ) {
                if (sq - 9 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq-9, EMPTY, EMPTY, MFLAG_EP), list);
                }
                if (sq - 11 == pos -> enPas) {
                    AddEnPassantMove(pos, MOVE(sq, sq-11, EMPTY, EMPTY, MFLAG_EP), list);
                }
            }
        }
    }

    // Loop for slide pieces
    pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePce[pceIndex++];

    while (pce != 0) {
        ASSERT(PieceValid(pce));

        for (pceNum = 0; pceNum < pos -> pceNum[pce]; ++pceNum) {
            sq = pos -> pList[pce][pceNum];
            ASSERT(SqOnBoard(sq));

            for (index = 0; index < NumDir[pce]; ++index) {
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                while (!SQOFFBOARD(t_sq)) {
                    if (pos -> pieces[t_sq] != EMPTY) {
                        if (PieceCol[pos -> pieces[t_sq]] == side ^ 1) {
                            AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                        }
                        break;
                    }
                    t_sq += dir;
                }
            }
        }

        pce = LoopSlidePce[pceIndex++];
    }

    //Loop for non-slide
    pceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePce[pceIndex++];

    while (pce != 0) {
        ASSERT(PieceValid(pce));

        for (pceNum = 0; pceNum < pos -> pceNum[pce]; ++pceNum) {
            sq = pos -> pList[pce][pceNum];
            ASSERT(SqOnBoard(sq));

            for (index = 0; index < NumDir[pce]; ++index) {
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                if (SQOFFBOARD(t_sq)) {
                    continue;
                }

                if (pos -> pieces[t_sq] != EMPTY) {
                    if (PieceCol[pos -> pieces[t_sq]] == side ^ 1) {
                        AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                    }
                    continue;
                }
            }
        }

        pce = LoopNonSlidePce[pceIndex++];
    }
}

// //Check for illegal moves
// int isKingInCheck(S_BOARD *board) {
//     int kingSquare = board -> KingSq[board -> side];
//     int opponentSide = (board -> side == WHITE) ? BLACK : WHITE;

//     int directions[] = {-9, -11, 9, 11};
//     for (int i = 0; i < 4; i++) {
//         int attackSquare = kingSquare + directions[i];
//         if (!SQOFFBOARD(attackSquare) && board -> pieces[attackSquare] == opponentSide + wP) {
//             return TRUE;
//         }
//     }

//     int knightOffsets[] = {-21, -19, 19, 21, -12, -8, 8, 12};
//     for (int i = 0; i < 4; i++) {
//         int attackSquare = kingSquare + knightOffsets[i];
//         if (!SQOFFBOARD(attackSquare) && board -> pieces[attackSquare] == opponentSide + wN) {
//             return TRUE;
//         }
//     }

//     int pieceOffSets[] = {-1, 1, 10, -10, -9, 9, -11, 11};
//     for (int i = 0; i < 8; i++) {
//         int direction = pieceOffSets[i];
//         int sq = kingSquare;
//         while (!SQOFFBOARD(sq)) {
//             sq += direction;
//             if (board -> pieces[sq] == opponentSide + wQ || board->pieces[sq] == opponentSide + wR || board -> pieces[sq] == opponentSide + wB) {
//                 return TRUE;
//             }
//             if (board -> pieces[sq] != EMPTY) break;
//         }
//     }

//     int kingOffsets[] = {-1, 1, 10, -10, -9, 9, -11, 11};
//     for (int i = 0; i < 8; i++) {
//         int attackSquare = kingSquare + kingOffsets[i];
//         if (!SQOFFBOARD(attackSquare) && board -> pieces[attackSquare] == opponentSide + wK) {
//             return TRUE;
//         }
//     }

//     return FALSE;
// }