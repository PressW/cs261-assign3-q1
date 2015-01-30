/* testCirListDeque.c
 * cirListDeque testing file.
 
 Authors:       Bret Lorimore & Preston Wipf
 Date:          January 30, 2015
 Description:   Tests cirListDeque functionality
                used assertTrue function from assignment 2 skeleton code
**** */

#include "cirListDeque.h"
#include <stdio.h>
#include <stdlib.h>

/*	Testing function, takes predicate, and message and prints the message
    and if the test passed or failed, ie if the predicate expression evaluated
    to true or false. NOT WRITTEN BY ME - TAKEN FROM ASSIGNMENT 2 SKELETON CODE
	param: 	char *message message to be printed out
    param: 	int predicate, boolean encoded as int
	pre:	*message is not null
 	pre:	predicate is a boolean encoded int
	post:	none
*/
void assertTrue(int predicate, char *message)
{
    printf("%s: ", message);
    if (predicate)
        printf("PASSED\n");
    else
        printf("FAILED\n");
}

int main(int argc, char* argv[]) {
    
    printf("Creating circular list deque...\n");
    struct cirListDeque *q = createCirListDeque();
    
    assertTrue(isEmptyCirListDeque(q), "isEmptyCirListDeque == true");
    
    printf("\nTesting addFrontCirListDeque(), frontCirListDeque(), backCirListDeque().\n");
    printf("Adding integers 0 - 999 to front of list,\n");
    printf("(ie addFrontCirListDeque(q, 0), addFrontCirListDeque(q, 1), ...)\n");
    for (int i = 0; i < 1000; i++) {
        addFrontCirListDeque(q, i);
    }
    assertTrue(!isEmptyCirListDeque(q), "isEmptyCirListDeque == false");
    assertTrue(frontCirListDeque(q) == 999, "frontCirListDeque(q) == 999");
    assertTrue(backCirListDeque(q) == 0, "backCirListDeque(q) == 0");

    printf("Now adding integers (-1) - (-500) to front of linked list,\n");
    printf("(ie addFront(q, -1), addFrontCirListDeque(q, -2), ...)\n");
    for (int i = -1; i > -501; i--) {
        addFrontCirListDeque(q, i);
    }
    assertTrue(frontCirListDeque(q) == -500, "frontCirListDeque(q) == -500");
    
    
    
    printf("\nTesting removebackCirListDeque(), frontCirListDeque(), backCirListDeque(), isEmptyCirListDeque().\n");
    printf("Removing 500 elements from back of list.\n");
    for (int i = 0; i < 500; i++) {
        removeBackCirListDeque(q);
    }
    printf("The list now should have 1000 elts with -500 @ front and 500 @ back\n");
    assertTrue(backCirListDeque(q) == 500, "backCirListDeque(q) == 500");
    assertTrue(frontCirListDeque(q) == -500, "frontCirListDeque(q) == -500");
    printf("Now removing the remaining 1000 elements from back of list.\n");
    for (int i = 0; i < 1000; i++) {
        removeBackCirListDeque(q);
    }
    assertTrue(isEmptyCirListDeque(q), "isEmptyCirListDeque == true");
    
    
    
    printf("\nTesting addbackCirListDeque(), frontCirListDeque(), backCirListDeque().\n");
    printf("Adding 500 integers to back of list, (499 - 0).\n");
    printf("(ie addbackCirListDeque(q, 499), addbackCirListDeque(q, 498), ...)\n");
    for (int i = 499; i >= 0; i--) {
        addBackCirListDeque(q, i);
    }
    printf("The list now should have 500 elts with 499 @ front and 0 @ back\n");
    assertTrue(backCirListDeque(q) == 0, "backCirListDeque(q) == 0");
    assertTrue(frontCirListDeque(q) == 499, "frontCirListDeque(q) == 499");
    
    printf("Now adding integers 500 - 1000 to back of linked list,\n");
    for (int i = 500; i < 1000; i++) {
        addBackCirListDeque(q, i);
    }
    printf("The list now should have 1000 elts with 499 @ front and 999 @ back\n");
    assertTrue(backCirListDeque(q) == 999, "backCirListDeque(q) == 999");
    
    
    
    printf("\nTesting removefrontCirListDeque(), frontCirListDeque(), backCirListDeque(), isEmptyCirListDeque().\n");
    printf("Removing 500 elements from front of list.\n");
    for (int i = 0; i < 500; i++) {
        removeFrontCirListDeque(q);
    }
    printf("The list now should have 500 elts with 500 @ front and 999 @ back\n");
    assertTrue(backCirListDeque(q) == 999, "backCirListDeque(q) == 999");
    assertTrue(frontCirListDeque(q) == 500, "frontCirListDeque(q) == 500");
    printf("Now removing the remaining 500 elements from front of list.\n");
    for (int i = 0; i < 500; i++) {
        removeFrontCirListDeque(q);
    }
    assertTrue(isEmptyCirListDeque(q), "isEmptyCirListDeque == true");
    
    

    printf("\nNow testing reverseCirListDeque() and printCirListDeque()\n");
    printf("Adding 1, 2, 3, 4, and 5 to the currently empty list ");
    printf("using addFrontCirListDeque()...\n");
    addFrontCirListDeque(q, 1);
    addFrontCirListDeque(q, 2);
    addFrontCirListDeque(q, 3);
    addFrontCirListDeque(q, 4);
    addFrontCirListDeque(q, 5);
    printf("\nNow calling printCirListDeque()...\n");
    printCirListDeque(q);

    printf("\nReversing list order, calling reverseCirListDeque(). The updated List:\n");
    reverseCirListDeque(q);
    printCirListDeque(q);
    
    printf("\nRemoving all but one element using removeBackCirListDeque(). The updated List:\n");
    for (int i = 0; i < 4; i++) {
        removeBackCirListDeque(q);
    }
    printCirListDeque(q);
    printf("\nNow calling reverseCirListDeque() on a one elt list. The updated List:\n");
    reverseCirListDeque(q);
    printCirListDeque(q);

    deleteCirListDeque(q);
    
	return 0;
}


