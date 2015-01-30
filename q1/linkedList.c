/* linkedList.c
 * deque ADT linked list implementation file.
 
 Authors:       Bret Lorimore & Preston Wipf
 Date:          January 30, 2015
 Description:   Implementation for a deque ADT using a doubly linked list
                with front and back sentinels
                ->  added one custom internal function _gracefulExit for printing
                    error messages and exiting the program
**** */

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {

    lst->size = 0;

    struct DLink *firstLinkSentinel = malloc(sizeof(struct DLink));
    struct DLink *lastLinkSentinel = malloc(sizeof(struct DLink));
    assert(lastLinkSentinel != 0 && firstLinkSentinel != 0);    //check allocation
    
    firstLinkSentinel->value = 0;    //doesnt matter
    firstLinkSentinel->next = lastLinkSentinel;
    firstLinkSentinel->prev = 0;
    
    lastLinkSentinel->value = 0;    //doesnt matter
    lastLinkSentinel->next = 0;
    lastLinkSentinel->prev = firstLinkSentinel;
    
    
    lst->firstLink = firstLinkSentinel;
    lst->lastLink = lastLinkSentinel;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
    //enforce pre-conditions
    assert(l != 0);
    assert(lst != 0);
    
    //cannot add link before head sentinel
    assert(lst->firstLink != l);
    
    struct DLink *newLink = malloc(sizeof(struct DLink));
    assert(newLink != 0);
    
    //init new link
    newLink->value = v;
    newLink->next = l;
    newLink->prev = l->prev;
    
    //adjust surrounding links
    (newLink->prev)->next = newLink;
    l->prev = newLink;
    
    lst->size++;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/
void _removeLink(struct linkedList *lst, struct DLink *l)
{
    //enforce pre-conditions
    assert(l != 0);
    assert(lst != 0);
    
    //cant remove sentinels
    assert(lst->firstLink != l && lst->lastLink != l);

    //link surrounding pointers
    (l->prev)->next = l->next;
    (l->next)->prev = l->prev;
    
    free(l);
    lst->size--;
}

/*  _containsListRecursive
 
    Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0
 
	param: l pointer to the first link in the list
	param: e the value we are looking for
	pre: l is not null
 	pre: l is NOT the firstLink sentinel
	post: none
*/
int _containsListRecursive(struct DLink *l, TYPE e) {
    
    //enforce preconditions
    assert(l != 0);
    
    if (l->value == e && l->next != 0) //dont want the value if we are at the sentinel
        return 1;
    
    else if (l->next == 0)
        return 0;
    
    else
        return _containsListRecursive(l->next, e);
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

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/
int isEmptyList(struct linkedList *lst) {

    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to isEmptyLinkedList", 1);
    
    int empty = (lst->size == 0) ? 1 : 0;
    
	return empty;
}

/* De-allocate all links of the list

	param: 	lst		pointer to the linked list
	pre:	none
	post:	All links (including the two sentinels) are de-allocated
*/
void freeLinkedList(struct linkedList *lst)
{
	while(!isEmptyList(lst)) {
		/* remove the link right after the first sentinel */
		_removeLink(lst, lst->firstLink->next);
	}		
	/* remove the first and last sentinels */
	free(lst->firstLink);
	free(lst->lastLink);	
}

/* 	Deallocate all the links and the linked list itself. 

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	the memory used by v->data is freed
*/
void deleteLinkedList(struct linkedList *lst)
{
    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to deleteEmptyLinkedList", 2);
    
	freeLinkedList(lst);
	free(lst);
}


/* Function to print list
 Pre: lst is not null
*/
void _printList(struct linkedList* lst) { // --------------DEBUG

    assert(lst != 0);
    
    printf("List size: %d\n", lst->size);
    
    if (lst->size > 0) {

        printf("List contents:\n");
        
        struct DLink *current = lst->firstLink;
        int i = 0;
        
        while (current->next != lst->lastLink) {
            current = current->next;
            printf("List[%d]: %d\n", i, current->value);
            i++;
        }
    }

}

/*  Function to print list
 calls internal function _printList()
 Pre: lst is not null
 */
void printList(struct linkedList *lst) {
    _printList(lst);
}

/* ************************************************************************
	Deque Interface Functions
************************************************************************ */

/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/
void addFrontList(struct linkedList *lst, TYPE e)
{

    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to addFrontList", 3);
    
    if (isEmptyList(lst))
        _addLinkBefore(lst, lst->lastLink, e);
    
    else    //lst is not empty
        _addLinkBefore(lst, (lst->firstLink)->next, e);
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/
void addBackList(struct linkedList *lst, TYPE e) {
  
    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to addBackList", 4);
    
    //add same place whether or not list is empty
    _addLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/
TYPE frontList (struct linkedList *lst) {
	
    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to frontList", 5);

    if (isEmptyList(lst))
        _gracefulExit("Passed empty linkedList to frontList", 6);
    
    return ((lst->firstLink)->next)->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/
TYPE backList(struct linkedList *lst)
{
    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to backList", 7);
    
    if (isEmptyList(lst))
        _gracefulExit("Passed empty linkedList to backList", 8);
    
    return ((lst->lastLink)->prev)->value;
}



/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/
void removeFrontList(struct linkedList *lst) {

    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to removeFrontList", 9);
    
    if (isEmptyList(lst))
        _gracefulExit("Passed empty linkedList to removeFrontList", 10);

    _removeLink(lst, (lst->firstLink)->next);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/
void removeBackList(struct linkedList *lst) {
    
    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to removeBackList", 11);
    
    if (isEmptyList(lst))
        _gracefulExit("Passed empty linkedList to removeBackList", 12);
    
    _removeLink(lst, (lst->lastLink)->prev);
}


/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to addList", 13);
    
    addFrontList(lst, v);

}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {

    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to containsList", 14);
    
    if (isEmptyList(lst))
        _gracefulExit("Passed empty linkedList to containsList", 15);
    
    struct DLink *current = lst->firstLink;
    
    while (current->next != lst->lastLink) {
        current = current->next;
        
        if (current->value == e)
            return 1;
    }
    
    return 0;
    
    //return _containsListRecursive((lst->firstLink)->next, e);
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {

    //pre-conditions
    if (lst == 0)
        _gracefulExit("Passed null linkedList ptr to removeList", 16);
    
    if (isEmptyList(lst))
        _gracefulExit("Passed empty linkedList to removeList", 17);
    
    int removed = 0;
    
    struct DLink *current = lst->firstLink;
    
    while (current->next != lst->lastLink) {    //dont want the sentinels
        
        current = current->next;
        
        if (current->value == e) {
            _removeLink(lst, current);
            removed = 1;
            break;
        }
    }
    if (!removed)
        printf("The element: %d that you tried to remove does not exist in the linked list.\n", e);
}