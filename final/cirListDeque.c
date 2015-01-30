/* cirListDeque.c
 * cirListDeque implementation file.
 
 Authors:       Bret Lorimore & Preston Wipf
 Date:          January 30, 2015
 Description:   Implementation for a circular linked list deque data structure
                structure uses one sentinel
                ->  added one custom internal function _gracefulExit for printing
                    error messages and exiting the program
 **** */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);
void _gracefulExit(char *message, int errorCode);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
    //pre-conditions
    assert(q != 0);
    
    struct DLink *sentinel = malloc(sizeof(struct DLink));
    assert(sentinel != 0);
    
    sentinel->value = 0;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    
    q->size = 0;
    q->Sentinel = sentinel;
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
    struct DLink *newLink = malloc(sizeof(struct DLink));
    assert(newLink != 0);
    
    newLink->value = val;
    newLink->next = 0;
    newLink->prev = 0;
    
	return newLink;

}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
    //pre-conditions
    assert(q != 0);
    assert(lnk != 0);
    
    struct DLink *newLink = _createLink(v);
    
    //new link pointers
    newLink->next = lnk->next;
    newLink->prev = lnk;
    
    //surrounding pointers
    lnk->next = newLink;
    (newLink->next)->prev = newLink;
    
    q->size++;
}

/* Prints custom error message and exits w/ custom error code
 
	param: 	message     c str - error message
	param: 	errorCode	integer error code
	pre:	message is not null
	post:	program has exited
*/
void _gracefulExit(char *message, int errorCode) {
    
    //pre-conditions
    assert(message != 0);
    
    printf("Error: %s\nGoodbye.\n", message);
    exit(errorCode);
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to addBackCirListDeque", 1);
    
    //else
    _addLinkAfter(q, (q->Sentinel)->prev, val);

}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to addFrontCirListDeque", 2);
    
    //else
    _addLinkAfter(q, q->Sentinel, val);

}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to frontCirListDeque", 3);

    if (q->size < 1)
        _gracefulExit("Passed empty cirListDeque to frontCirListDeque", 4);
    
	return ((q->Sentinel)->next)->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to backCirListDeque", 5);
    
    if (q->size < 1)
        _gracefulExit("Passed empty cirListDeque to backCirListDeque", 6);
    
    return ((q->Sentinel)->prev)->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
    //pre-conditions
    assert(q != 0);
    assert(q->size > 0);
    assert(lnk != q->Sentinel);
    
    //surounding pointers
    (lnk->prev)->next = lnk->next;
    (lnk->next)->prev = lnk->prev;
    
    q->size--;
    
    free(lnk);
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {

    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to removeFrontCirListDeque", 7);
    
    if (q->size < 1)
        _gracefulExit("Passed empty cirListDeque to removeFrontCirListDeque", 8);
    
    _removeLink(q, (q->Sentinel)->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to removeBackCirListDeque", 9);
    
    if (q->size < 1)
        _gracefulExit("Passed empty cirListDeque to removeBackCirListDeque", 10);
    
    _removeLink(q, (q->Sentinel)->prev);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
    struct DLink *current = (q->Sentinel)->next, *prev;
    
    while (current != q->Sentinel) {
        prev = current;
        //printf("%.02f, ", prev->value);   //DEBUG
        current = current->next;
        free(prev);
    }
    free(q->Sentinel);
}

/* 	Deallocate all the links and the deque itself. 

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	the memory used by v->data is freed
*/
void deleteCirListDeque(struct cirListDeque *q) {
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to deleteCirListDeque", 11);
	freeCirListDeque(q);
	free(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
    
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to isEmptyCirListDeque", 12);
    
    return (q->size > 0) ? 0 : 1;
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to printCirListDeque", 13);
    
    if (q->size < 1)
        _gracefulExit("Passed empty cirListDeque to printCirListDeque", 14);
    
    printf("List size: %d\n", q->size);
    
    if (q->size > 0) {
        
        printf("List contents:\n");
        
        struct DLink *current = q->Sentinel;
        int i = 0;
        
        while (current->next != q->Sentinel) {
            current = current->next;
            printf("List[%d]: %.02f\n", i, current->value);
            i++;
        }
    }
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
    //pre-conditions
    if (q == 0)
        _gracefulExit("Passed null cirListDeque ptr to reverseCirListDeque", 15);
    
    if (q->size < 1)
        _gracefulExit("Passed empty cirListDeque to reverseCirListDeque", 16);

    struct DLink *current = q->Sentinel, *temp;
    
    //have to do the swap once to get off the sentinel
    //before we enter the loop otherwise we have an infinite loop
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    
    while (current->prev != q->Sentinel) {

        current = current->prev;
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
    }
}
