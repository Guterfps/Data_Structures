/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 15/2/2023	               */
/* WORKSHEET NAME: Knight tour		      */
/* REVIEWER: Eliran		                 */
/*--------------------------------------*/

#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include <stddef.h> /* size_t */

/*-----------------------------------------------------------------------------
Knight's tour: A knight's tour is a sequence of moves of a knight on a 
chessboard such that the knight visits every square exactly once. If the 
knight ends on a square that is one knight's move from the beginning square 
(so that it could tour the board again immediately, following the same path), 
the tour is closed (or re-entrant); otherwise, it is open.

parameters: path - buffer to hold the path result of the knight(length of 64).
			start_position - the index position on the board the knight will
							start from(0 - 63).
return value: 0 on successfull path, -1 if finding the path took more than
			  5 minutes (300 seconds).

-----------------------------------------------------------------------------*/

int KnightTour(size_t *path, size_t start_position);

#endif /*__KNIGHT_TOUR_H__*/

