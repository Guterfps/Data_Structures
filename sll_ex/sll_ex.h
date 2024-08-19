/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 11/12/2022               */
/* WORKSHEET NAME: SLL Exercises	      */
/* REVIEWER: Sveta		                 */
/*--------------------------------------*/

#ifndef __SLL_EX__
#define __SLL_EX__

typedef struct node
{
	void *data;
	struct node *next;
} node_t;


node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
node_t *FindIntersection(node_t *head_1, node_t *head_2);

#endif
