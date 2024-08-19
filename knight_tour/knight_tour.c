/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 15/2/2023	               */
/* WORKSHEET NAME: Knight tour		      */
/* REVIEWER: Eliran		                 */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <time.h>	/* clock() */
#include <stdlib.h> /* qsort */

#include "bit_array.h"	/* bit_array header */
#include "knight_tour.h" /* function declerations and tyepdefs */

#define MAX_MOVES (8)
#define NUM_OF_POSITIONS (64)
#define LINE_LEN (8)
#define ROW_LEN (8)
#define COL_LEN (8)
#define TIME_OUT ((double)300)

enum status
{
	FAIL = -1,
	SUCCESS = 0
};

typedef struct pos
{
	size_t indx;
	int *moves;
	bit_array_t board;
} pos_t;

/* lut functions */
static size_t MatrixIndxToArrayIndx(size_t row, size_t col);
static void PossibleMoves(size_t pos, int *moves);
static void InitLut(int lut[NUM_OF_POSITIONS][MAX_MOVES]);

/* path finding functions */
static int FindPath(size_t *path, size_t pos, 
					int lut[NUM_OF_POSITIONS][MAX_MOVES],
					bit_array_t board, size_t step_num, clock_t begin);
static int CheckMove(size_t next_pos, bit_array_t board);
static int CmpDgree(const void *pos1, const void *pos2);
static size_t CountValidSteps(pos_t *pos);
static void InitSortedMoves(size_t pos, pos_t *s_moves, 
							int lut[NUM_OF_POSITIONS][MAX_MOVES], 
							bit_array_t board);
static int PathOptions(size_t *path, pos_t *s_moves, 
						int lut[NUM_OF_POSITIONS][MAX_MOVES],
						bit_array_t board, size_t step_num, clock_t begin);

int KnightTour(size_t *path, size_t start_position)
{
	int lut[NUM_OF_POSITIONS][MAX_MOVES] = {0};
	bit_array_t chess_board = 0;
	clock_t begin = clock();
	
	assert(NULL != path);
	assert(NUM_OF_POSITIONS > start_position);
	
	InitLut(lut);
	chess_board = BitArrSetOn(chess_board, start_position);
	
	return (FindPath(path, start_position, lut, chess_board, 1, begin));
}

static int FindPath(size_t *path, size_t pos, 
					int lut[NUM_OF_POSITIONS][MAX_MOVES],
					bit_array_t board, size_t step_num, clock_t begin)
{
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	pos_t s_moves[MAX_MOVES] = {0};
	
	assert(NULL != path);
	assert(NULL != lut);
	
	if (NUM_OF_POSITIONS == step_num)
	{
		return SUCCESS;
	}
	
	if (TIME_OUT < time_spent)
	{
		return FAIL;
	}
	
	InitSortedMoves(pos, s_moves, lut, board);
	
	return (PathOptions(path, s_moves, lut, board, step_num, begin));
}

static int PathOptions(size_t *path, pos_t *s_moves, 
						int lut[NUM_OF_POSITIONS][MAX_MOVES],
						bit_array_t board, size_t step_num, clock_t begin)
{
	size_t i = 0;
	
	assert(NULL != s_moves);
	assert(NULL != lut);
	assert(NULL != s_moves);
	
	for (; i < MAX_MOVES; ++i)
	{
		size_t next_pos = s_moves[i].indx;
		
		if (CheckMove(next_pos, board))
		{
			path[next_pos] = step_num;
			board = BitArrSetOn(board, next_pos);
			if (SUCCESS == FindPath(path, next_pos, lut, board, 
									step_num + 1 ,begin))
			{
				return SUCCESS;
			}
			else
			{
				board = BitArrSetOff(board, next_pos);
				path[next_pos] = 0;
			}
		}
	}
	
	return FAIL;
}

static void InitSortedMoves(size_t pos, pos_t *s_moves, 
							int lut[NUM_OF_POSITIONS][MAX_MOVES], 
							bit_array_t board)
{
	size_t i = 0;
	
	assert(NULL != s_moves);
	assert(NULL != lut);
	
	for (; i < MAX_MOVES; ++i)
	{
		s_moves[i].indx = lut[pos][i];
		s_moves[i].moves = lut[s_moves[i].indx];
		s_moves[i].board = board;
	}
	qsort(s_moves, MAX_MOVES, sizeof(pos_t), &CmpDgree);
}

static int CheckMove(size_t next_pos, bit_array_t board)
{
	return ((NUM_OF_POSITIONS > next_pos) && 
			(bit_off == BitArrGetVal(board, next_pos)));
}

static void InitLut(int lut[NUM_OF_POSITIONS][MAX_MOVES])
{
	size_t i = 0;
	
	assert(NULL != lut);
	
	for (; i < NUM_OF_POSITIONS; ++i)
	{
		PossibleMoves(i, lut[i]);
	}
}


static size_t MatrixIndxToArrayIndx(size_t row, size_t col)
{
	return (row * LINE_LEN + col);
}

static void PossibleMoves(size_t pos, int *moves)
{
	size_t row = pos / LINE_LEN;
	size_t col = pos % LINE_LEN;
	int horizontal[MAX_MOVES] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[MAX_MOVES] = {1, 2, 2, 1, -1, -2, -2, -1};
	size_t i = 0;
	
	assert(NULL != moves);
	
	for (; i < MAX_MOVES; ++i)
	{
		size_t next_move_h = row + horizontal[i];
		size_t next_move_v = col + vertical[i];
		
		if ((next_move_h < ROW_LEN) && (next_move_v < COL_LEN))
		{
			moves[i] = MatrixIndxToArrayIndx(next_move_h, next_move_v);
		}
		else
		{
			moves[i] = -1;
		}
	}
}

static size_t CountValidSteps(pos_t *pos)
{
	size_t count = 0;
	size_t i = 0;
	
	assert(NULL != pos);
	
	for (; i < MAX_MOVES; ++i)
	{
		count += (CheckMove(pos->moves[i], pos->board)) ? 1 : 0;
	}
	
	return count;
}

static int CmpDgree(const void *pos1, const void *pos2)
{
	assert(NULL != pos1);
	assert(NULL != pos1);
	
	return (CountValidSteps((pos_t *)pos1) - CountValidSteps((pos_t *)pos2));
}


