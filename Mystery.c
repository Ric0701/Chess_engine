//https://www.youtube.com/watch?v=4ozHuSRDyfE&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg&index=82
//Time: 0:00
//Chapter: 82

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
#define Huge "R6r/8/8/2K5/5k2/8/8/r6R w - - 0 1" //Depth 6

#define Mate3byBlack "5rk1/1p4pp/2p5/p2p4/3Pn3/1Pq5/PK6/2B5 w - - 0 32"
#define M2 "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w Q - 0 1"
#define M5 "6k1/3b3r/1p1p4/p1n2p2/1PPNpP1q/P3Q1p1/1R1RB1P1/5K2 b - - 0-1"
#define random "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"
#define bugtest "3rr3/pp4k1/2p2bQ1/3n3p/3p4/3B4/1qPB1PPP/RR4K1 b - - 0 1"

int main() {
    AllInit();

    S_BOARD pos[1];
	memset(pos, 0, sizeof(S_BOARD)); //Grok
    S_SEARCHINFO info[1];
    InitPvTable(pos -> PvTable);

    printf("Welcome to %s! Type '%s' for console mode -> \n", NAME, NAME);

    char line[256];
	while (TRUE) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "uci",3)) {
			UCI_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		} else if (!strncmp(line, "xboard",6))	{
			XBoard_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		} else if (!strncmp(line, NAME, 7))	{
			Console_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		} else if(!strncmp(line, "quit", 4))	{
			break;
		}
	}

    free(pos -> PvTable -> pTable);

    return 0;
}