/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 15/2/2023	               */
/* WORKSHEET NAME: Knight tour		      */
/* REVIEWER: Eliran		                 */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */
#include <time.h>	/* clock() */
#include <stdlib.h> /* rand() */

#include "knight_tour.h" /* function declerations and tyepdefs */

void Test(void);

int main(void)
{
	Test();
	
	return 0;
}

void Test(void)
{
	size_t board[64] = {0};
	size_t start = 0;
	size_t i = 0;
	clock_t begin = 0;
	clock_t end = 0;
	int status = 0;
	
	srand(time(NULL));
	
	start = rand() % 64;
	
	begin = clock();
	(0 == KnightTour(board, start)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	end = clock();
	printf("time taken: %.2f \n",  (double)(end - begin) / CLOCKS_PER_SEC);
	
	for (i = 1; i <= 64; ++i)
	{
		printf(" %ld, ", board[i - 1]);
		
		if (0 == (i % 8))
		{
			printf("\n");
		}
	}
	printf("\n");
	
	for (i = 0; (i < 63) && (!status); ++i)
	{
		status = KnightTour(board, i);
	}
	
	printf("start from all positions test:	");
	(0 == status) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");

}

