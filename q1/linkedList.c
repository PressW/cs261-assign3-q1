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

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/
int isEmptyList(struct linkedList *lst) {

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
	assert (lst != 0);
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

    //enforce preconditions
    assert(lst != 0);
    
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
  
    //enforce preconditions
    assert(lst != 0);
    
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
	
    //enforce preconditions
    assert(lst != 0);
    assert(!isEmptyList(lst));
    
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
    //enforce preconditions
    assert(lst != 0);
    assert(!isEmptyList(lst));
    
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

    if (!isEmptyList(lst))
        _removeLink(lst, (lst->firstLink)->next);
    
    else {
        printf("Tried to remove link from empty list! That's embarrasing... \n");
        printf("I didn't kill the program on purpose. Now you get to go on a debugging adventure ;)\n");
    }
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/
void removeBackList(struct linkedList *lst) {
    
    if (!isEmptyList(lst))
        _removeLink(lst, (lst->lastLink)->prev);
    
    else {
        printf("Tried to remove link from empty list! That's embarrasing... \n");
        printf("Whatever happens next, you are not expecting it.\n");
    }
	
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

    //enforce preconditions
    assert(lst != 0);
    assert(!isEmptyList(lst));
    
    struct DLink *current = lst->firstLink;
    
    while (current->next != lst->lastLink) {
        current = current->next;
        
        if (current->value == e)
            return 1;
    }
    
    printf("Could not remove %d from list, as it is not in the list.", e);
    
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
void removeList (struct linkedList *lst, TYPE e) { // --------------FIX

    //enforce preconditions
    assert(lst != 0);
    assert(lst->size != 0);
    
    struct DLink *current = lst->firstLink;
    
    while (current->next != lst->lastLink) {    //dont want the sentinels
        
        current = current->next;
        
        if (current->value == e) {
            _removeLink(lst, current);
            break;
        }
        
    }
}